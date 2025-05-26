#ifndef TRIEOFTRIES_H
#define TRIEOFTRIES_H

#include <vector>
#include <string>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <deque>
#include <stack>
#include <sstream>
#include <ostream>

// value_printer: prints T if streamable, else triggers static_assert
template<typename T, typename = void>
struct value_printer {
    static std::string print(const T&) {
        static_assert(sizeof(T)==0,
            "Value type is not streamable; please provide a specialization of value_printer or pass a custom printer.");
        return {};
    }
    std::string operator()(const T& v) const { return print(v); }
};

template<typename T>
struct value_printer<
    T,
    std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>
> {
    static std::string print(const T& v) {
        std::ostringstream os;
        os << v;
        return os.str();
    }
    std::string operator()(const T& v) const { return print(v); }
};

// Default character mapping: full 256-byte range
struct DefaultCharMap {
    static constexpr std::size_t size = 256;
    std::size_t operator()(char c) const noexcept { return static_cast<unsigned char>(c); }
    char operator()(std::size_t idx) const noexcept { return static_cast<char>(idx); }
};

// Alphanumeric mapping: 0-9, A-Z, a-z => 62 symbols
struct AlnumCharMap {
    static constexpr std::size_t size = 62;
    std::size_t operator()(char c) const {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'Z') return 10 + (c - 'A');
        if (c >= 'a' && c <= 'z') return 36 + (c - 'a');
        throw std::out_of_range("Unsupported character");
    }
    char operator()(std::size_t idx) const {
        if (idx < 10) return char('0' + idx);
        if (idx < 36) return char('A' + (idx - 10));
        if (idx < 62) return char('a' + (idx - 36));
        throw std::out_of_range("Index out of range");
    }
};

// TrieOfTries: configurable branching via CharMap
template< typename ValType, class CharMap = DefaultCharMap >
class TrieOfTries {
public:
    using key_type   = std::vector<std::string>;
    using size_type  = std::size_t;
    using value_type = std::pair<key_type, ValType>;

private:
    struct Node {
        Node* children[CharMap::size];
        Node* next_level;
        bool  has_value;
        ValType value;
        Node() : next_level(nullptr), has_value(false) {
            std::memset(children, 0, sizeof(children));
        }
        bool empty() const {
            if (has_value || next_level) return false;
            for (auto ptr : children)
                if (ptr) return false;
            return true;
        }
    };

    Node* root_;
    size_type count_;
    CharMap cmap_;

    void delete_trie(Node* n) {
        if (!n) return;
        for (size_type i = 0; i < CharMap::size; ++i)
            delete_trie(n->children[i]);
        delete_trie(n->next_level);
        delete n;
    }

    Node* locate_node(const key_type& keys) const {
        Node* cur = root_;
        for (size_type lvl = 0; lvl < keys.size(); ++lvl) {
            for (char ch : keys[lvl]) {
                size_type idx = cmap_(ch);
                cur = cur->children[idx];
                if (!cur) return nullptr;
            }
            if (lvl + 1 < keys.size()) {
                cur = cur->next_level;
                if (!cur) return nullptr;
            }
        }
        return cur;
    }

    bool erase_rec(Node*& n, const key_type& ks, size_type lvl) {
        if (!n) return false;
        const std::string& s = ks[lvl];
        if (!s.empty()) {
            char ch = s[0];
            size_type idx = cmap_(ch);
            bool removed = false;
            if (s.size() > 1) {
                std::string rest = s.substr(1);
                key_type temp = ks;
                temp[lvl] = rest;
                removed = erase_rec(n->children[idx], temp, lvl);
            } else {
                if (lvl + 1 < ks.size()) {
                    removed = erase_rec(n->children[idx]->next_level, ks, lvl + 1);
                } else {
                    if (!n->children[idx] || !n->children[idx]->has_value) return false;
                    n->children[idx]->has_value = false;
                    removed = n->children[idx]->empty();
                }
            }
            if (removed) {
                delete n->children[idx];
                n->children[idx] = nullptr;
            }
        }
        if (n->empty()) { delete n; n = nullptr; return true; }
        return false;
    }

    using Segment = std::pair<Node*, std::string>;
    static void discover(Node* node, std::string& buf,
                         std::vector<Segment>& segs, const CharMap& cmap) {
        if (!node) return;
        for (size_type i = 0; i < CharMap::size; ++i) {
            Node* child = node->children[i];
            if (child) {
                buf.push_back(cmap(i));
                if (child->has_value || child->next_level)
                    segs.emplace_back(child, buf);
                discover(child, buf, segs, cmap);
                buf.pop_back();
            }
        }
    }

public:
    TrieOfTries() : root_(new Node), count_(0), cmap_() {}
    ~TrieOfTries() { delete_trie(root_); }
    void clean() { delete_trie(root_); root_ = new Node; count_ = 0; }

    bool insert(const key_type& keys, const ValType& val) {
        Node* cur = root_;
        for (size_type lvl = 0; lvl < keys.size(); ++lvl) {
            for (char ch : keys[lvl]) {
                size_type idx = cmap_(ch);
                if (!cur->children[idx]) cur->children[idx] = new Node;
                cur = cur->children[idx];
            }
            if (lvl + 1 < keys.size()) {
                if (!cur->next_level) cur->next_level = new Node;
                cur = cur->next_level;
            }
        }
        if (cur->has_value) return false;
        cur->has_value = true;
        cur->value = val;
        ++count_;
        return true;
    }

    ValType* find(const key_type& keys) const {
        Node* n = locate_node(keys);
        return (n && n->has_value) ? &n->value : nullptr;
    }

    bool erase(const key_type& keys) {
        if (erase_rec(root_, keys, 0)) { --count_; return true; }
        return false;
    }

    bool contains(const key_type& keys) const { return find(keys) != nullptr; }
    ValType& at(const key_type& keys) const {
        if (auto p = find(keys)) return *p;
        throw std::out_of_range("Key sequence not found");
    }
    size_type size()  const noexcept { return count_; }
    bool empty()      const noexcept { return count_ == 0; }

    // DFS Iterator
    class dfs_iterator {
        struct LevelEntry {
            Node* level_root;
            key_type keys_so_far;
            std::vector<Segment> segments;
            size_type next_idx;
        };
        const TrieOfTries* parent_;
        std::vector<LevelEntry> stack_;
        value_type current_;
        bool end_;

        void init(Node* start, const key_type& prefix) {
            stack_.clear();
            std::string buf;
            std::vector<Segment> segs;
            discover(start, buf, segs, parent_->cmap_);
            stack_.push_back({start, prefix, segs, 0});
        }

        void advance() {
            end_ = true;
            while (!stack_.empty()) {
                auto &le = stack_.back();
                if (le.next_idx < le.segments.size()) {
                    auto [node, seg] = le.segments[le.next_idx++];
                    key_type new_keys = le.keys_so_far;
                    new_keys.push_back(seg);
                    if (node->next_level) {
                        std::string buf;
                        std::vector<Segment> child_segs;
                        discover(node->next_level, buf, child_segs, parent_->cmap_);
                        stack_.push_back({node->next_level, new_keys, child_segs, 0});
                    }
                    if (node->has_value) {
                        current_ = {new_keys, node->value};
                        end_ = false;
                        return;
                    }
                } else {
                    stack_.pop_back();
                }
            }
        }

    public:
        dfs_iterator(const TrieOfTries* parent, Node* start, const key_type& prefix)
            : parent_(parent), end_(false) { init(start, prefix); advance(); }
        dfs_iterator(const TrieOfTries* parent)
            : parent_(parent), end_(false) { init(parent->root_, {}); advance(); }
        dfs_iterator() : parent_(nullptr), end_(true) {}

        dfs_iterator& operator++() { advance(); return *this; }
        const key_type& key()   const { return current_.first; }
        ValType&        value() const { return const_cast<ValType&>(current_.second); }
        value_type      operator*() const { return current_; }
        bool operator==(const dfs_iterator& o) const { return end_ == o.end_; }
        bool operator!=(const dfs_iterator& o) const { return !(*this == o); }
    };

    dfs_iterator dfs_begin()           const { return dfs_iterator(this, root_, {}); }
    dfs_iterator dfs_end()             const { return dfs_iterator();         }
    dfs_iterator dfs_begin(const key_type& keys) const {
        if (keys.empty()) return dfs_begin();
        Node* n = locate_node(keys);
        return (n && n->next_level)
            ? dfs_iterator(this, n->next_level, keys)
            : dfs_end();
    }

    // BFS Iterator
    class bfs_iterator {
        struct LevelEntry {
            Node* level_root;
            key_type keys_so_far;
            std::vector<Segment> segments;
            size_type next_idx;
        };
        const TrieOfTries* parent_;
        std::deque<LevelEntry> queue_;
        value_type current_;
        bool end_;

        void init(Node* start, const key_type& prefix) {
            queue_.clear();
            std::string buf;
            std::vector<Segment> segs;
            discover(start, buf, segs, parent_->cmap_);
            queue_.push_back({start, prefix, segs, 0});
        }

        void advance() {
            end_ = true;
            while (!queue_.empty()) {
                auto &le = queue_.front();
                if (le.next_idx < le.segments.size()) {
                    auto [node, seg] = le.segments[le.next_idx++];
                    key_type new_keys = le.keys_so_far;
                    new_keys.push_back(seg);
                    if (node->next_level) {
                        std::string buf;
                        std::vector<Segment> child_segs;
                        discover(node->next_level, buf, child_segs, parent_->cmap_);
                        queue_.push_back({node->next_level, new_keys, child_segs, 0});
                    }
                    if (node->has_value) {
                        current_ = {new_keys, node->value};
                        end_ = false;
                        return;
                    }
                } else {
                    queue_.pop_front();
                }
            }
        }

    public:
        bfs_iterator(const TrieOfTries* parent, Node* start, const key_type& prefix)
            : parent_(parent), end_(false) { init(start, prefix); advance(); }
        bfs_iterator(const TrieOfTries* parent)
            : parent_(parent), end_(false) { init(parent->root_, {}); advance(); }
        bfs_iterator() : parent_(nullptr), end_(true) {}

        bfs_iterator& operator++() { advance(); return *this; }
        const key_type& key()   const { return current_.first; }
        ValType&        value() const { return const_cast<ValType&>(current_.second); }
        value_type      operator*() const { return current_; }
        bool operator==(const bfs_iterator& o) const { return end_ == o.end_; }
        bool operator!=(const bfs_iterator& o) const { return !(*this == o); }
    };

    bfs_iterator bfs_begin()           const { return bfs_iterator(this, root_, {}); }
    bfs_iterator bfs_end()             const { return bfs_iterator();         }
    bfs_iterator bfs_begin(const key_type& keys) const {
        if (keys.empty()) return bfs_begin();
        Node* n = locate_node(keys);
        return (n && n->next_level)
            ? bfs_iterator(this, n->next_level, keys)
            : bfs_end();
    }

    // toStrBFS with customizable printer
    template<typename Printer = value_printer<ValType>>
    std::string toStrBFS(const key_type& prefix,
                         Printer printer = Printer()) const {
        std::ostringstream oss;
        oss << "BFS on [";
        bool first = true;
        for (auto& k : prefix) {
            if (!first) oss << ",";
            first = false;
            oss << k;
        }
        oss << "]:\n";
        for (auto it = bfs_begin(prefix); it != bfs_end(); ++it) {
            oss << "[";
            first = true;
            for (auto& k : it.key()) {
                if (!first) oss << ",";
                first = false;
                oss << k;
            }
            oss << "]:";
            oss << printer(it.value()) << "\n";
        }
        return oss.str();
    }

    // toStrDFS with customizable printer
    template<typename Printer = value_printer<ValType>>
    std::string toStrDFS(const key_type& prefix,
                         Printer printer = Printer()) const {
        std::ostringstream oss;
        oss << "DFS on [";
        bool first = true;
        for (auto& k : prefix) {
            if (!first) oss << ",";
            first = false;
            oss << k;
        }
        oss << "]:\n";
        for (auto it = dfs_begin(prefix); it != dfs_end(); ++it) {
            oss << "[";
            first = true;
            for (auto& k : it.key()) {
                if (!first) oss << ",";
                first = false;
                oss << k;
            }
            oss << "]:";
            oss << printer(it.value()) << "\n";
        }
        return oss.str();
    }
};



inline int TrieOfTries_Test()
{
    TrieOfTries<std::string, AlnumCharMap> t;
    t.insert({"a"},"a");
    t.insert({"a","a"}, "a,a");
    t.insert({"a","a","a"}, "a,a,a");
    t.insert({"a","a","b"}, "a,a,b");
    t.insert({"ab"}, "ab");
    t.insert({"abc"}, "abc");
    t.insert({"a","b"}, "a,b");
    t.insert({"a","c"}, "a,c");
    t.insert({"b"}, "b");
    t.insert({"ba"}, "ba");
    t.insert({"b", "a"}, "b,a");
    t.insert({"c"}, "c");
    t.insert({"c","b"}, "c,b");
    t.insert({"ab","a"}, "ab,a");
    t.insert({"ab","b"}, "ab,b");
    t.insert({"ab","c"}, "ab,c");
    t.insert({"ab", "a", "a"}, "ab,a,a");
    t.insert({"ab","a","b"}, "ab,a,b");

    std::cout << t.toStrBFS({}) << std::endl;
    std::cout << t.toStrBFS({"ab"}) << std::endl;
    std::cout << t.toStrDFS({}) << std::endl;
    std::cout << t.toStrDFS({"ab"}) << std::endl;

    return 0;
}


#endif
