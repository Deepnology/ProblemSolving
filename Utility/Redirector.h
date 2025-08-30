#ifndef _REDIRECTOR_H_
#define _REDIRECTOR_H_

// std_redirector.hpp
// C++17 header-only utility for redirecting std streams and Qt logging.
// - std::cout/cerr/wcout/wcerr: multi-destination fan-out (file/null), remove/replace
// - Qt qDebug/qInfo/qWarning/qCritical/qFatal: per-level multi-routes, remove/replace
// - Safe log rotation via swap_to_file() for std
// - UTF-8 encoding for wide text
// - Path normalization so different spellings of the same file share one sink

#include <iostream>
#include <streambuf>
#include <mutex>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <filesystem>
#include <cwctype>

#if defined(_WIN32) || defined(_WIN64)
static const std::filesystem::path kNullDevice = L"NUL";
#else
static const std::filesystem::path kNullDevice = "/dev/null";
#endif

// ---------- Stream mask for std:: streams ----------
using StreamMask = unsigned;
constexpr StreamMask CoutBit  = 1u << 0;
constexpr StreamMask CerrBit  = 1u << 1;
constexpr StreamMask WcoutBit = 1u << 2;
constexpr StreamMask WcerrBit = 1u << 3;
constexpr StreamMask AllBits  = CoutBit | CerrBit | WcoutBit | WcerrBit;

enum class RedirectMode { Original, File, Null }; // Original is for removal/restore; not a route

// ---------- Path normalization (shared sink for different spellings) ----------
static inline std::wstring norm_key(const std::filesystem::path& p) {
    namespace fs = std::filesystem;
    std::error_code ec;
    fs::path q = fs::weakly_canonical(p, ec);
    if (ec || q.empty()) { q = fs::absolute(p, ec); if (ec || q.empty()) q = p; }
    std::wstring k = q.make_preferred().native();
#if defined(_WIN32) || defined(_WIN64)
    std::transform(k.begin(), k.end(), k.begin(), [](wchar_t c){ return std::towlower(c); });
#endif
    return k;
}

// ---------- SharedSink (FILE* with mutex) ----------
class SharedSink {
public:
    explicit SharedSink(const std::filesystem::path& path, bool truncate) : path_(path) {
        open_(truncate);
        if (!file_) throw std::runtime_error("Failed to open sink");
    }
    void write(const char* data, size_t n) {
        std::scoped_lock lk(mu_);
        if (!file_) return;
        (void)std::fwrite(data, 1, n, file_.get());
    }
    void flush() {
        std::scoped_lock lk(mu_);
        if (file_) std::fflush(file_.get());
    }
    void reopen(bool truncate) {
        std::scoped_lock lk(mu_);
        file_.reset();
        open_(truncate);
        if (!file_) throw std::runtime_error("SharedSink::reopen failed");
    }
    const std::filesystem::path& path() const noexcept { return path_; }
private:
    struct Closer { void operator()(FILE* f) const { if (f) std::fclose(f); } };
    void open_(bool truncate) {
#if defined(_WIN32) || defined(_WIN64)
        const wchar_t* mode = truncate ? L"wb" : L"ab";
        file_.reset(_wfopen(path_.c_str(), mode));
#else
        const char* mode = truncate ? "wb" : "ab";
        std::string p = path_.string();
        file_.reset(std::fopen(p.c_str(), mode));
#endif
    }
    std::mutex mu_;
    std::unique_ptr<FILE, Closer> file_{nullptr};
    std::filesystem::path path_;
};

// ---------- Tiny UTF-8 encoder ----------
static inline void encode_utf8(char32_t cp, char out[4], int& len) {
    if (cp <= 0x7F)       { out[0]=char(cp); len=1; }
    else if (cp <= 0x7FF) { out[0]=char(0xC0|(cp>>6)); out[1]=char(0x80|(cp&0x3F)); len=2; }
    else if (cp <= 0xFFFF){ out[0]=char(0xE0|(cp>>12)); out[1]=char(0x80|((cp>>6)&0x3F)); out[2]=char(0x80|(cp&0x3F)); len=3; }
    else                  { out[0]=char(0xF0|(cp>>18)); out[1]=char(0x80|((cp>>12)&0x3F)); out[2]=char(0x80|((cp>>6)&0x3F)); out[3]=char(0x80|((cp&0x3F)); len=4; }
}

// ---------- Multi-sink streambufs (fan-out) ----------
class MultiNarrowBuf : public std::streambuf {
public:
    using traits_type = std::streambuf::traits_type;
    using int_type    = traits_type::int_type;
    using char_type   = char;
    explicit MultiNarrowBuf(std::vector<std::shared_ptr<SharedSink>> sinks)
        : sinks_(std::move(sinks)) {}
    void set_sinks(std::vector<std::shared_ptr<SharedSink>> sinks) { sinks_ = std::move(sinks); }
protected:
    int_type overflow(int_type ch = traits_type::eof()) override {
        if (traits_type::eq_int_type(ch, traits_type::eof()))
            return traits_type::not_eof(ch);
        char_type c = traits_type::to_char_type(ch);
        for (auto& s : sinks_) s->write(&c, 1);
        return ch;
    }
    std::streamsize xsputn(const char_type* s, std::streamsize n) override {
        const char* p = reinterpret_cast<const char*>(s);
        size_t sz = static_cast<size_t>(n);
        for (auto& sink : sinks_) sink->write(p, sz);
        return n;
    }
    int sync() override { for (auto& s : sinks_) s->flush(); return 0; }
private:
    std::vector<std::shared_ptr<SharedSink>> sinks_;
};

class MultiWideBuf : public std::wstreambuf {
public:
    using traits_type = std::wstreambuf::traits_type;
    using int_type    = traits_type::int_type;
    using char_type   = wchar_t;
    explicit MultiWideBuf(std::vector<std::shared_ptr<SharedSink>> sinks)
        : sinks_(std::move(sinks)) {}
    void set_sinks(std::vector<std::shared_ptr<SharedSink>> sinks) { sinks_ = std::move(sinks); }
protected:
    int_type overflow(int_type ch = traits_type::eof()) override {
        if (traits_type::eq_int_type(ch, traits_type::eof()))
            return traits_type::not_eof(ch);
        put_one(traits_type::to_char_type(ch));
        return ch;
    }
    std::streamsize xsputn(const char_type* s, std::streamsize n) override {
        for (std::streamsize i = 0; i < n; ++i) put_one(s[i]);
        return n;
    }
    int sync() override { for (auto& s : sinks_) s->flush(); return 0; }
private:
    void broadcast_utf8(const char* data, int len) { for (auto& s : sinks_) s->write(data, (size_t)len); }
    void put_one(wchar_t w) {
#if WCHAR_MAX == 0xFFFF
        auto is_high = [](char16_t x){ return x >= 0xD800 && x <= 0xDBFF; };
        auto is_low  = [](char16_t x){ return x >= 0xDC00 && x <= 0xDFFF; };
        static thread_local char16_t pending_high = 0;
        char16_t u = static_cast<char16_t>(w);
        char out[4]; int len = 0;
        if (pending_high) {
            if (is_low(u)) {
                char32_t cp = 0x10000 + (((pending_high - 0xD800) << 10) | (u - 0xDC00));
                pending_high = 0; encode_utf8(cp, out, len); broadcast_utf8(out, len); return;
            } else { encode_utf8(0xFFFD, out, len); broadcast_utf8(out, len); pending_high = 0; }
        }
        if (is_high(u)) { pending_high = u; return; }
        if (is_low(u))  { encode_utf8(0xFFFD, out, len); broadcast_utf8(out, len); return; }
        encode_utf8(static_cast<char32_t>(u), out, len); broadcast_utf8(out, len);
#else
        char out[4]; int len = 0; encode_utf8(static_cast<char32_t>(w), out, len); broadcast_utf8(out, len);
#endif
    }
    std::vector<std::shared_ptr<SharedSink>> sinks_;
};

// ---------- StdRedirector ----------
class StdRedirector {
public:
    StdRedirector()
        : old_cout_(std::cout.rdbuf()),
          old_cerr_(std::cerr.rdbuf()),
          old_wcout_(std::wcout.rdbuf()),
          old_wcerr_(std::wcerr.rdbuf()) {}

    // --- Add routes (does NOT include the original console automatically) ---
    bool addStdRoute(StreamMask mask, RedirectMode mode,
                     const std::filesystem::path& filename = {}, bool truncate = false) {
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        if (mode == RedirectMode::Original) return false; // Original isn't a sink
        auto sink = get_or_make_sink_(mode, filename, truncate);
        if (!sink) return false;
        std::cout.flush(); std::cerr.flush(); std::wcout.flush(); std::wcerr.flush();
        if (mask & CoutBit)  add_unique_sink_(cout_sinks_,  sink);
        if (mask & CerrBit)  add_unique_sink_(cerr_sinks_,  sink);
        if (mask & WcoutBit) add_unique_sink_(wcout_sinks_, sink);
        if (mask & WcerrBit) add_unique_sink_(wcerr_sinks_, sink);
        install_or_restore_(mask);
        return true;
    }

    // --- Remove all routes for given streams (restores console if empty) ---
    void removeStdRoutes(StreamMask mask) { clearStdRoutes(mask); }

    // --- Replace = remove then add ---
    bool replaceStdRoute(StreamMask mask, RedirectMode mode,
                         const std::filesystem::path& filename = {}, bool truncate = false) {
        removeStdRoutes(mask);
        if (mode == RedirectMode::Original) return true; // just restored
        return addStdRoute(mask, mode, filename, truncate);
    }

    // Back-compat convenience
    bool redirect(StreamMask mask, RedirectMode mode,
                  const std::filesystem::path& filename = {}, bool truncate = false) {
        return replaceStdRoute(mask, mode, filename, truncate);
    }

    // Safe rotation: replace selected streams’ routes with a single file; optionally truncate
    bool swap_to_file(StreamMask mask, const std::filesystem::path& filename, bool truncate_first) {
        if (filename.empty()) return false;
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        std::cout.flush(); std::cerr.flush(); std::wcout.flush(); std::wcerr.flush();

        const auto key = norm_key(filename);
        std::shared_ptr<SharedSink> sink;
        auto it = file_sinks_.find(key);
        if (it == file_sinks_.end()) {
            try {
                sink = std::make_shared<SharedSink>(filename, /*truncate*/truncate_first);
                file_sinks_.emplace(key, sink);
            } catch (...) { return false; }
        } else {
            sink = it->second;
            if (truncate_first) {
                try { sink->reopen(/*truncate*/true); }
                catch (...) { return false; }
            }
        }
        if (mask & CoutBit)  { cout_sinks_.assign(1, sink); }
        if (mask & CerrBit)  { cerr_sinks_.assign(1, sink); }
        if (mask & WcoutBit) { wcout_sinks_.assign(1, sink); }
        if (mask & WcerrBit) { wcerr_sinks_.assign(1, sink); }
        install_or_restore_(mask);
        return true;
    }

    void clearStdRoutes(StreamMask mask) {
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        if (mask & CoutBit)  cout_sinks_.clear();
        if (mask & CerrBit)  cerr_sinks_.clear();
        if (mask & WcoutBit) wcout_sinks_.clear();
        if (mask & WcerrBit) wcerr_sinks_.clear();
        install_or_restore_(mask);
    }

    void restore(StreamMask mask) { clearStdRoutes(mask); }
    void restore_all() { clearStdRoutes(AllBits); }

#ifdef QT_VERSION
    // ---------- Qt multi-route ----------
#  include <QtCore/QtGlobal>
#  include <QtCore/QDateTime>
#  include <QtCore/QMessageLogContext>
#  include <QtCore/QString>
#  include <QtCore/QByteArray>

    using QtMask = unsigned;
    static constexpr QtMask QtDebugBit    = 1u << 0;
#  if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    static constexpr QtMask QtInfoBit     = 1u << 1;
    static constexpr int    kInfoShift    = 1;
#  else
    static constexpr int    kInfoShift    = 0;
#  endif
    static constexpr QtMask QtWarningBit  = 1u << (1 + kInfoShift);
    static constexpr QtMask QtCriticalBit = 1u << (2 + kInfoShift);
    static constexpr QtMask QtFatalBit    = 1u << (3 + kInfoShift);
    static constexpr QtMask QtAllBits =
#  if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QtDebugBit | QtInfoBit | QtWarningBit | QtCriticalBit | QtFatalBit;
#  else
        QtDebugBit | QtWarningBit | QtCriticalBit | QtFatalBit;
#  endif

    struct QtFormat {
        bool include_time      = false;
        bool include_category  = false;
        bool include_file_line = false;
        bool flush_each_msg    = false;
    };

    // Add a Qt route (does NOT auto-include original stderr). Use setQtForwardToStderr(true) separately.
    bool addQtRoute(RedirectMode mode,
                    const std::filesystem::path& filename,
                    bool truncate,
                    QtMask level_mask,
                    QtFormat fmt = {}) {
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        ensure_qt_installed_();
        auto sink = get_or_make_sink_(mode, filename, truncate);
        if (!sink) return false;
        qt_routes_.push_back(QtRoute{sink, level_mask, fmt});
        return true;
    }

    // Remove all Qt routes that touch these bits
    void removeQtRoutes(QtMask level_mask) {
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        if (!qt_installed_) return;
        qt_routes_.erase(std::remove_if(qt_routes_.begin(), qt_routes_.end(),
            [&](const QtRoute& r){ return (r.mask & level_mask) != 0; }), qt_routes_.end());
        maybe_uninstall_qt_();
    }

    // Replace = remove then add
    bool replaceQtRoute(RedirectMode mode,
                        const std::filesystem::path& filename,
                        bool truncate,
                        QtMask level_mask,
                        QtFormat fmt = {}) {
        removeQtRoutes(level_mask);
        return addQtRoute(mode, filename, truncate, level_mask, fmt);
    }

    // Old convenience (kept): replace and set forwarding
    bool redirectQt(RedirectMode mode,
                    const std::filesystem::path& filename,
                    bool truncate,
                    bool also_to_stderr,
                    QtMask level_mask,
                    QtFormat fmt = {}) {
        setQtForwardToStderr(also_to_stderr);
        return replaceQtRoute(mode, filename, truncate, level_mask, fmt);
    }

    void clearQtRoutes() {
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        restoreQt_();
    }

    void setQtForwardToStderr(bool on) {
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        ensure_qt_installed_();
        qt_forward_prev_ = on;
        maybe_uninstall_qt_();
    }
#endif // QT_CORE_LIB

    ~StdRedirector() {
        restore_all();
#ifdef QT_CORE_LIB
        restoreQt_();
#endif
    }

private:
    // --- sink registry / helpers ---
    std::shared_ptr<SharedSink> get_or_make_sink_(RedirectMode mode,
                                                  const std::filesystem::path& filename,
                                                  bool truncate) {
        if (mode == RedirectMode::Null) {
            if (!null_sink_) {
                try { null_sink_ = std::make_shared<SharedSink>(kNullDevice, false); }
                catch (...) { return nullptr; }
            }
            return null_sink_;
        }
        if (mode == RedirectMode::File) {
            if (filename.empty()) return nullptr;
            const auto key = norm_key(filename);
            auto it = file_sinks_.find(key);
            if (it == file_sinks_.end()) {
                try {
                    auto s = std::make_shared<SharedSink>(filename, truncate);
                    it = file_sinks_.emplace(key, std::move(s)).first;
                } catch (...) { return nullptr; }
            }
            return it->second;
        }
        return nullptr; // Original isn't a sink
    }

    static void add_unique_sink_(std::vector<std::shared_ptr<SharedSink>>& v,
                                 const std::shared_ptr<SharedSink>& s) {
        if (std::find(v.begin(), v.end(), s) == v.end()) v.push_back(s);
    }

    void install_or_restore_(StreamMask which) {
        auto install_narrow = [&](std::vector<std::shared_ptr<SharedSink>>& sinks,
                                  std::unique_ptr<MultiNarrowBuf>& buf,
                                  std::ostream& os,
                                  std::streambuf* oldbuf) {
            if (!sinks.empty()) {
                if (!buf) buf = std::make_unique<MultiNarrowBuf>(sinks);
                else      buf->set_sinks(sinks);
                os.rdbuf(buf.get());
            } else {
                if (oldbuf) os.rdbuf(oldbuf);
                buf.reset();
            }
        };
        auto install_wide = [&](std::vector<std::shared_ptr<SharedSink>>& sinks,
                                std::unique_ptr<MultiWideBuf>& buf,
                                std::wostream& os,
                                std::wstreambuf* oldbuf) {
            if (!sinks.empty()) {
                if (!buf) buf = std::make_unique<MultiWideBuf>(sinks);
                else      buf->set_sinks(sinks);
                os.rdbuf(buf.get());
            } else {
                if (oldbuf) os.rdbuf(oldbuf);
                buf.reset();
            }
        };
        if (which & CoutBit)  install_narrow(cout_sinks_,  cout_buf_,  std::cout,  old_cout_);
        if (which & CerrBit)  install_narrow(cerr_sinks_,  cerr_buf_,  std::cerr,  old_cerr_);
        if (which & WcoutBit) install_wide  (wcout_sinks_, wcout_buf_, std::wcout, old_wcout_);
        if (which & WcerrBit) install_wide  (wcerr_sinks_, wcerr_buf_, std::wcerr, old_wcerr_);
    }

#ifdef QT_VERSION
    // ---------- Qt internals ----------
    struct QtFormat; // declared above
    struct QtRoute {
        std::shared_ptr<SharedSink> sink;
        unsigned                    mask = 0;
        QtFormat                    fmt{};
    };

    inline static std::vector<QtRoute>      qt_routes_;
    inline static QtMessageHandler          qt_prev_ = nullptr;
    inline static bool                      qt_installed_ = false;
    inline static bool                      qt_forward_prev_ = false;

    static unsigned bit_for_type_(QtMsgType type) {
        switch (type) {
            case QtDebugMsg:    return QtDebugBit;
#  if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
            case QtInfoMsg:     return QtInfoBit;
#  endif
            case QtWarningMsg:  return QtWarningBit;
            case QtCriticalMsg: return QtCriticalBit;
            case QtFatalMsg:    return QtFatalBit;
        }
        return 0;
    }

    static void qt_handler_(QtMsgType type, const QMessageLogContext& ctx, const QString& msg) {
        auto routes = qt_routes_;            // snapshot (shared_ptr copies)
        auto prev   = qt_prev_;
        bool fwd    = qt_forward_prev_;

        if (routes.empty() && !fwd) { if (type == QtFatalMsg) abort(); return; }

        const unsigned bit = bit_for_type_(type);
        char typeChar = '?';
        switch (type) {
            case QtDebugMsg:    typeChar = 'D'; break;
#  if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
            case QtInfoMsg:     typeChar = 'I'; break;
#  endif
            case QtWarningMsg:  typeChar = 'W'; break;
            case QtCriticalMsg: typeChar = 'C'; break;
            case QtFatalMsg:    typeChar = 'F'; break;
        }

        for (const auto& r : routes) {
            if ((r.mask & bit) == 0 || !r.sink) continue;

            QByteArray line;
            line.reserve(128 + msg.size()*2);
            line.append('[').append(&typeChar, 1).append("] ");

            if (r.fmt.include_time) {
#    if QT_VERSION >= QT_VERSION_CHECK(5, 8, 0)
                line.append('[')
                    .append(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toUtf8())
                    .append("] ");
#    else
                line.append('[')
                    .append(QDateTime::currentDateTime().toString(Qt::ISODate).toUtf8())
                    .append("] ");
#    endif
            }
            if (r.fmt.include_category) {
                const char* cat = (ctx.category && *ctx.category) ? ctx.category : "-";
                line.append(cat).append(": ");
            }

            line.append(msg.toUtf8());

            if (r.fmt.include_file_line) {
                const char* file = (ctx.file && *ctx.file) ? ctx.file : "-";
                line.append(" (").append(file).append(':').append(QByteArray::number(ctx.line)).append(')');
            }

            line.append('\n');
            r.sink->write(line.constData(), static_cast<size_t>(line.size()));
            if (r.fmt.flush_each_msg || type == QtFatalMsg) r.sink->flush();
        }

        if (fwd && prev) prev(type, ctx, msg);
        if (type == QtFatalMsg) abort();
    }

    void ensure_qt_installed_() {
        if (!qt_installed_) {
            qt_prev_ = qInstallMessageHandler(&StdRedirector::qt_handler_);
            qt_installed_ = true;
        }
    }
    void maybe_uninstall_qt_() {
        if (qt_installed_ && qt_routes_.empty() && !qt_forward_prev_) {
            qInstallMessageHandler(qt_prev_);
            qt_installed_ = false;
            qt_prev_ = nullptr;
        }
    }
    void restoreQt_() {
        if (qt_installed_) {
            qInstallMessageHandler(qt_prev_);
            qt_installed_ = false;
            qt_prev_ = nullptr;
        }
        qt_routes_.clear();
        qt_forward_prev_ = false;
    }
#endif // QT_CORE_LIB

    // --- std originals & state ---
    std::streambuf*  old_cout_;
    std::streambuf*  old_cerr_;
    std::wstreambuf* old_wcout_;
    std::wstreambuf* old_wcerr_;

    std::unique_ptr<MultiNarrowBuf> cout_buf_;
    std::unique_ptr<MultiNarrowBuf> cerr_buf_;
    std::unique_ptr<MultiWideBuf>   wcout_buf_;
    std::unique_ptr<MultiWideBuf>   wcerr_buf_;

    std::vector<std::shared_ptr<SharedSink>> cout_sinks_;
    std::vector<std::shared_ptr<SharedSink>> cerr_sinks_;
    std::vector<std::shared_ptr<SharedSink>> wcout_sinks_;
    std::vector<std::shared_ptr<SharedSink>> wcerr_sinks_;

    // Sink registry
    std::shared_ptr<SharedSink> null_sink_;
    std::unordered_map<std::wstring, std::shared_ptr<SharedSink>> file_sinks_;

    // Config lock
    std::mutex reconfig_mu_;
};


#endif
