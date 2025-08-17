#ifndef _REDIRECTOR_H_
#define _REDIRECTOR_H_

#include <iostream>
#include <streambuf>
#include <mutex>
#include <memory>
#include <optional>
#include <string>
#include <map>
#include <cstdio>
#include <climits>
#include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
static const std::filesystem::path kNullDevice = L"NUL";
#else
static const std::filesystem::path kNullDevice = "/dev/null";
#endif

// ---------------- Bitmask for choosing C++ streams ----------------
using StreamMask = unsigned;
constexpr StreamMask CoutBit  = 1u << 0;
constexpr StreamMask CerrBit  = 1u << 1;
constexpr StreamMask WcoutBit = 1u << 2;
constexpr StreamMask WcerrBit = 1u << 3;
constexpr StreamMask AllBits  = CoutBit | CerrBit | WcoutBit | WcerrBit;

enum class RedirectMode { Original, File, Null };

// ---------------- Shared sink (FILE*) with a lock ----------------
class SharedSink {
public:
    SharedSink(const std::filesystem::path& path, bool truncate)
        : path_(path)
    {
        open_(truncate);
        if (!file_) throw std::runtime_error("Failed to open sink");
    }

    void write(const char* data, size_t n) {
        std::scoped_lock lk(mu_);
        if (file_) { std::fwrite(data, 1, n, file_.get()); }
    }

    void flush() {
        std::scoped_lock lk(mu_);
        if (file_) { std::fflush(file_.get()); }
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

// ---------- Narrow streambuf -> sink bytes (correct signature) ----------
class NarrowBuf : public std::streambuf {
public:
    using traits_type = std::streambuf::traits_type;
    using int_type    = traits_type::int_type;
    using char_type   = char;

    explicit NarrowBuf(std::shared_ptr<SharedSink> sink) : sink_(std::move(sink)) {}
    std::shared_ptr<SharedSink> sink() const noexcept { return sink_; }

protected:
    int_type overflow(int_type ch = traits_type::eof()) override {
        if (traits_type::eq_int_type(ch, traits_type::eof()))
            return traits_type::not_eof(ch);
        char_type c = traits_type::to_char_type(ch);
        sink_->write(&c, 1);
        return ch;
    }
    std::streamsize xsputn(const char_type* s, std::streamsize n) override {
        sink_->write(reinterpret_cast<const char*>(s), static_cast<size_t>(n));
        return n;
    }
    int sync() override { sink_->flush(); return 0; }

private:
    std::shared_ptr<SharedSink> sink_;
};

// ---------- Tiny UTF-8 encoder ----------
static inline void encode_utf8(char32_t cp, char out[4], int& len) {
    if (cp <= 0x7F)       { out[0]=char(cp); len=1; }
    else if (cp <= 0x7FF) { out[0]=char(0xC0|(cp>>6)); out[1]=char(0x80|(cp&0x3F)); len=2; }
    else if (cp <= 0xFFFF){ out[0]=char(0xE0|(cp>>12)); out[1]=char(0x80|((cp>>6)&0x3F)); out[2]=char(0x80|(cp&0x3F)); len=3; }
    else                  { out[0]=char(0xF0|(cp>>18)); out[1]=char(0x80|((cp>>12)&0x3F)); out[2]=char(0x80|((cp>>6)&0x3F)); out[3]=char(0x80|(cp&0x3F)); len=4; }
}

// ---------- Wide streambuf -> UTF-8 bytes -> sink (correct signature) ----------
class WideBuf : public std::wstreambuf {
public:
    using traits_type = std::wstreambuf::traits_type;
    using int_type    = traits_type::int_type;
    using char_type   = wchar_t;

    explicit WideBuf(std::shared_ptr<SharedSink> sink) : sink_(std::move(sink)) {}
    std::shared_ptr<SharedSink> sink() const noexcept { return sink_; }

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
    int sync() override { sink_->flush(); return 0; }

private:
    void put_one(wchar_t w) {
#if WCHAR_MAX == 0xFFFF
        // Windows (UTF-16 wchar_t) — handle surrogates
        auto is_high = [](char16_t x){ return x >= 0xD800 && x <= 0xDBFF; };
        auto is_low  = [](char16_t x){ return x >= 0xDC00 && x <= 0xDFFF; };

        char16_t u = static_cast<char16_t>(w);
        char out[4]; int len = 0;

        if (pending_high_) {
            if (is_low(u)) {
                char32_t cp = 0x10000 + (((pending_high_ - 0xD800) << 10) | (u - 0xDC00));
                pending_high_ = 0;
                encode_utf8(cp, out, len);
                sink_->write(out, len);
                return;
            } else {
                // orphan high surrogate -> U+FFFD
                encode_utf8(0xFFFD, out, len);
                sink_->write(out, len);
                pending_high_ = 0;
            }
        }
        if (is_high(u)) { pending_high_ = u; return; }
        if (is_low(u))  { char out2[4]; int l=0; encode_utf8(0xFFFD, out2, l); sink_->write(out2, l); return; }
        encode_utf8(static_cast<char32_t>(u), out, len);
        sink_->write(out, len);
#else
        // POSIX (UTF-32 wchar_t)
        char out[4]; int len = 0;
        encode_utf8(static_cast<char32_t>(w), out, len);
        sink_->write(out, len);
#endif
    }

#if WCHAR_MAX == 0xFFFF
    char16_t pending_high_ = 0;
#endif
    std::shared_ptr<SharedSink> sink_;
};

// ---------------- Controller: mix & match + safe swap ----------------
class StdRedirector {
public:
    StdRedirector() :
        old_cout_(std::cout.rdbuf()),
        old_cerr_(std::cerr.rdbuf()),
        old_wcout_(std::wcout.rdbuf()),
        old_wcerr_(std::wcerr.rdbuf()) {}

    // Redirect selected C++ streams to mode.
    bool redirect(StreamMask mask, RedirectMode mode,
                  const std::filesystem::path& filename = {}, bool truncate = false)
    {
        if ((mode == RedirectMode::File) && filename.empty()) return false;

        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);

        std::shared_ptr<SharedSink> sink;
        if (mode == RedirectMode::Null) {
            if (!null_sink_) {
                try { null_sink_ = std::make_shared<SharedSink>(kNullDevice, /*truncate*/false); }
                catch (...) { return false; }
            }
            sink = null_sink_;
        } else if (mode == RedirectMode::File) {
            auto it = file_sinks_.find(filename);
            if (it == file_sinks_.end()) {
                try {
                    auto s = std::make_shared<SharedSink>(filename, truncate);
                    it = file_sinks_.emplace(filename, std::move(s)).first;
                } catch (...) { return false; }
            }
            sink = it->second;
        } else { // Original
            restore_(mask);
            return true;
        }

        apply_(mask, sink);
        return true;
    }

    // Atomically switch selected streams to 'filename', optionally truncating.
    bool swap_to_file(StreamMask mask, const std::filesystem::path& filename, bool truncate_first) {
        if (filename.empty()) return false;

        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        std::cout.flush(); std::cerr.flush(); std::wcout.flush(); std::wcerr.flush();

        std::shared_ptr<SharedSink> sink;
        auto it = file_sinks_.find(filename);
        if (it == file_sinks_.end()) {
            try {
                sink = std::make_shared<SharedSink>(filename, /*truncate*/truncate_first);
            } catch (...) { return false; }
            file_sinks_.emplace(filename, sink);
        } else {
            sink = it->second;
            if (truncate_first) {
                try { sink->reopen(/*truncate*/true); }
                catch (...) { return false; }
            }
        }
        apply_(mask, sink);
        return true;
    }

    void restore(StreamMask mask) {
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);
        restore_(mask);
    }

    void restore_all() { restore(AllBits); }

#ifdef QT_CORE_LIB
    // ---------------- Qt logging: level mask + formatting toggles ----------------
    using QtMask = unsigned;
    static constexpr QtMask QtDebugBit   = 1u << 0;
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    static constexpr QtMask QtInfoBit    = 1u << 1;
    static constexpr int    kInfoShift   = 1;
#else
    static constexpr int    kInfoShift   = 0; // no info in this Qt
#endif
    static constexpr QtMask QtWarningBit = 1u << (1 + kInfoShift);
    static constexpr QtMask QtCriticalBit= 1u << (2 + kInfoShift);
    static constexpr QtMask QtFatalBit   = 1u << (3 + kInfoShift);
    static constexpr QtMask QtAllBits =
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QtDebugBit | QtInfoBit | QtWarningBit | QtCriticalBit | QtFatalBit;
#else
        QtDebugBit | QtWarningBit | QtCriticalBit | QtFatalBit;
#endif

    struct QtFormat {
        bool include_time      = false; // ISO 8601 with ms
        bool include_category  = false; // ctx.category
        bool include_file_line = false; // ctx.file:ctx.line
        // type tag ([D/I/W/C/F]) is kept (not very verbose); add a toggle here if you want to hide it.
    };

    // Redirect Qt logs with level filter & formatting options.
    // If mode==File and filename already has a sink here, it reuses the same handle.
    // If also_to_stderr==true, forward to the previous Qt handler too.
    bool redirectQt(RedirectMode mode,
                    const std::filesystem::path& filename = {},
                    bool truncate = false,
                    bool also_to_stderr = false,
                    QtMask level_mask = QtAllBits,
                    QtFormat fmt = {})
    {
        std::lock_guard<std::mutex> cfg_lock(reconfig_mu_);

        if (mode == RedirectMode::Original) {
            restoreQt_();
            return true;
        }

        std::shared_ptr<SharedSink> sink;
        if (mode == RedirectMode::Null) {
            if (!null_sink_) {
                try { null_sink_ = std::make_shared<SharedSink>(kNullDevice, /*truncate*/false); }
                catch (...) { return false; }
            }
            sink = null_sink_;
        } else { // File
            if (filename.empty()) return false;
            auto it = file_sinks_.find(filename);
            if (it == file_sinks_.end()) {
                try {
                    auto s = std::make_shared<SharedSink>(filename, truncate);
                    it = file_sinks_.emplace(filename, std::move(s)).first;
                } catch (...) { return false; }
            }
            sink = it->second;
        }

        if (!qt_ctx_) qt_ctx_ = std::make_unique<QtCtx>();
        qt_ctx_->sink = sink;
        qt_ctx_->also_to_stderr = also_to_stderr;
        qt_ctx_->level_mask = level_mask;
        qt_ctx_->fmt = fmt;

        if (!qt_ctx_->installed) {
            qt_ctx_->prev = qInstallMessageHandler(&StdRedirector::qt_handler_);
            qt_ctx_->installed = true;
        }
        return true;
    }

    void restoreQt() { std::lock_guard<std::mutex> cfg_lock(reconfig_mu_); restoreQt_(); }
#endif // QT_CORE_LIB

    ~StdRedirector() {
        restore_all();
#ifdef QT_CORE_LIB
        restoreQt_();
#endif
    }

private:
    void apply_(StreamMask mask, const std::shared_ptr<SharedSink>& sink) {
        if (mask & CoutBit)  { cout_buf_  = std::make_unique<NarrowBuf>(sink); std::cout.rdbuf(cout_buf_.get()); }
        if (mask & CerrBit)  { cerr_buf_  = std::make_unique<NarrowBuf>(sink); std::cerr.rdbuf(cerr_buf_.get()); }
        if (mask & WcoutBit) { wcout_buf_ = std::make_unique<WideBuf>(sink);   std::wcout.rdbuf(wcout_buf_.get()); }
        if (mask & WcerrBit) { wcerr_buf_ = std::make_unique<WideBuf>(sink);   std::wcerr.rdbuf(wcerr_buf_.get()); }
    }

    void restore_(StreamMask mask) {
        if (mask & CoutBit)  { if (old_cout_)  std::cout.rdbuf(old_cout_);   cout_buf_.reset(); }
        if (mask & CerrBit)  { if (old_cerr_)  std::cerr.rdbuf(old_cerr_);   cerr_buf_.reset(); }
        if (mask & WcoutBit) { if (old_wcout_) std::wcout.rdbuf(old_wcout_); wcout_buf_.reset(); }
        if (mask & WcerrBit) { if (old_wcerr_) std::wcerr.rdbuf(old_wcerr_); wcerr_buf_.reset(); }
    }

    // originals
    std::streambuf*  old_cout_;
    std::streambuf*  old_cerr_;
    std::wstreambuf* old_wcout_;
    std::wstreambuf* old_wcerr_;

    // active custom buffers (one per stream)
    std::unique_ptr<NarrowBuf> cout_buf_;
    std::unique_ptr<NarrowBuf> cerr_buf_;
    std::unique_ptr<WideBuf>   wcout_buf_;
    std::unique_ptr<WideBuf>   wcerr_buf_;

    // sinks
    std::shared_ptr<SharedSink> null_sink_;
    std::map<std::filesystem::path, std::shared_ptr<SharedSink>> file_sinks_;

    // configuration lock
    std::mutex reconfig_mu_;

#ifdef QT_CORE_LIB
    // ---- Qt handler state ----
    struct QtCtx {
        std::shared_ptr<SharedSink> sink;
        bool                        also_to_stderr = false;
        unsigned                    level_mask     = 0;
        QtFormat                    fmt{};
        QtMessageHandler            prev = nullptr;
        bool                        installed = false;
    };

    inline static std::unique_ptr<QtCtx> qt_ctx_;

    static unsigned bit_for_type_(QtMsgType type) {
        switch (type) {
            case QtDebugMsg:    return QtDebugBit;
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
            case QtInfoMsg:     return QtInfoBit;
#endif
            case QtWarningMsg:  return QtWarningBit;
            case QtCriticalMsg: return QtCriticalBit;
            case QtFatalMsg:    return QtFatalBit;
        }
        return 0;
    }

    static void qt_handler_(QtMsgType type, const QMessageLogContext& ctx, const QString& msg) {
        // Copy ctx ptrs used into locals (handler can run after reconfig)
        std::shared_ptr<SharedSink> sink  = qt_ctx_ ? qt_ctx_->sink : nullptr;
        QtMessageHandler prev             = qt_ctx_ ? qt_ctx_->prev : nullptr;
        bool also_to_stderr               = qt_ctx_ ? qt_ctx_->also_to_stderr : false;
        unsigned level_mask               = qt_ctx_ ? qt_ctx_->level_mask : 0;
        QtFormat fmt                      = qt_ctx_ ? qt_ctx_->fmt : QtFormat{};

        // Filter by level
        unsigned bit = bit_for_type_(type);
        if ((level_mask & bit) == 0) {
            if (also_to_stderr && prev) prev(type, ctx, msg);
            if (type == QtFatalMsg) abort();
            return;
        }

        // Compose line per format
        // Start with type tag: [D/I/W/C/F]
        char typeChar = '?';
        switch (type) {
            case QtDebugMsg:    typeChar = 'D'; break;
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
            case QtInfoMsg:     typeChar = 'I'; break;
#endif
            case QtWarningMsg:  typeChar = 'W'; break;
            case QtCriticalMsg: typeChar = 'C'; break;
            case QtFatalMsg:    typeChar = 'F'; break;
        }

        QByteArray line;
        line.reserve(128 + msg.size()*2);
        line.append('[').append(&typeChar, 1).append("] ");

        if (fmt.include_time) {
            line.append('[')
#if QT_VERSION >= QT_VERSION_CHECK(5, 8, 0)
                .append(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toUtf8())
#else
                .append(QDateTime::currentDateTime().toString(Qt::ISODate).toUtf8())
#endif
                .append("] ");
        }

        if (fmt.include_category) {
            const char* cat = (ctx.category && *ctx.category) ? ctx.category : "-";
            line.append(cat).append(": ");
        }

        line.append(msg.toUtf8());

        if (fmt.include_file_line) {
            const char* file = (ctx.file && *ctx.file) ? ctx.file : "-";
            line.append(" (").append(file).append(':').append(QByteArray::number(ctx.line)).append(')');
        }

        line.append('\n');

        if (sink) {
            sink->write(line.constData(), static_cast<size_t>(line.size()));
            if (type == QtFatalMsg) sink->flush();
        }

        if (also_to_stderr && prev) prev(type, ctx, msg);
        if (type == QtFatalMsg) abort();
    }

    void restoreQt_() {
        if (qt_ctx_ && qt_ctx_->installed) {
            qInstallMessageHandler(qt_ctx_->prev);
            qt_ctx_->installed = false;
            qt_ctx_->sink.reset();
        }
    }
#endif // QT_CORE_LIB
};

#endif
