/*
 * DEBUG_FILE_SORT_LINE(filename)
 *
 * Header-only macro that sorts lines in a text file by indentation level.
 * Lines sharing the same parent (determined by leading spaces) are sorted
 * lexicographically. Each subtree is sorted independently, preserving the
 * parent-child structure defined by indentation.
 *
 * No line-length limit in either implementation.
 *
 * Compatibility:
 *   - C++  : uses std::string / std::vector / std::sort  (no buffer cap)
 *   - C    : uses fgetc / realloc                        (no buffer cap)
 *
 * Assumptions:
 *   - Indentation is spaces only (each space = 1 unit).
 *   - A line indented deeper than its predecessor is a child of it.
 *   - Empty lines attach to the current parent and are not re-sorted.
 *   - CRLF line endings are accepted; output is always LF.
 *
 * Usage:
 *   DEBUG_FILE_SORT_LINE("myfile.txt");   // sorts file in-place
 */

#ifndef DEBUG_FILE_SORT_LINE_H
#define DEBUG_FILE_SORT_LINE_H

/* =========================================================================
 * C++ implementation
 * ====================================================================== */
#ifdef __cplusplus

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace _dfsl {

struct Node {
    std::string        line;
    int                indent;
    std::vector<Node*> children;

    explicit Node(std::string text)
        : line(std::move(text))
        , indent(_count_indent(line))
    {}

    Node() : indent(-1) {}          /* virtual-root constructor */

    ~Node() { for (Node* c : children) delete c; }

    Node(const Node&)            = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&)                 = default;
    Node& operator=(Node&&)      = default;

private:
    static int _count_indent(const std::string& s) {
        int n = 0;
        for (char c : s) { if (c == ' ') ++n; else break; }
        return n;
    }
};

inline Node* build_tree(const std::vector<std::string>& lines) {
    Node* root = new Node();
    std::vector<Node*> stack;
    stack.push_back(root);

    for (const std::string& text : lines) {
        Node* node = new Node(text);
        if (text.empty()) {
            stack.back()->children.push_back(node);
            continue;
        }
        while (stack.size() > 1 && stack.back()->indent >= node->indent)
            stack.pop_back();
        stack.back()->children.push_back(node);
        stack.push_back(node);
    }
    return root;
}

inline void sort_tree(Node* node) {
    std::sort(node->children.begin(), node->children.end(),
              [](const Node* a, const Node* b) { return a->line < b->line; });
    for (Node* child : node->children) sort_tree(child);
}

inline void write_tree(std::ostream& out, const Node* node, bool skip_self) {
    if (!skip_self) out << node->line << '\n';
    for (const Node* child : node->children) write_tree(out, child, false);
}

inline void sort_file(const std::string& filename) {
    std::ifstream in(filename);
    if (!in)
        throw std::runtime_error(
            "[DEBUG_FILE_SORT_LINE] Cannot open for reading: " + filename);

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(std::move(line));
    }
    in.close();

    if (lines.empty()) return;

    Node* root = build_tree(lines);
    sort_tree(root);

    std::ofstream out(filename, std::ios::trunc);
    if (!out) {
        delete root;
        throw std::runtime_error(
            "[DEBUG_FILE_SORT_LINE] Cannot open for writing: " + filename);
    }
    write_tree(out, root, true);
    delete root;
}

} /* namespace _dfsl */

#define DEBUG_FILE_SORT_LINE(filename) ::_dfsl::sort_file(filename)


/* =========================================================================
 * C implementation
 * ====================================================================== */
#else /* !__cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ----- dynamic string: grows via realloc, no fixed cap ---------------- */

typedef struct {
    char  *data;
    size_t len;
    size_t cap;
} _dfsl_str_t;

static void _dfsl_str_init(_dfsl_str_t *s) {
    s->cap  = 64;
    s->len  = 0;
    s->data = (char *)malloc(s->cap);
    s->data[0] = '\0';
}

static void _dfsl_str_free(_dfsl_str_t *s) { free(s->data); }

/* Read one line from fp into s (strips trailing CR/LF).
 * Returns 1 if a line was read, 0 on EOF. */
static int _dfsl_read_line(FILE *fp, _dfsl_str_t *s) {
    s->len = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (s->len + 2 > s->cap) {
            s->cap *= 2;
            s->data = (char *)realloc(s->data, s->cap);
        }
        if (c == '\n') break;
        if (c == '\r') continue;    /* skip CR, stop at LF */
        s->data[s->len++] = (char)c;
    }
    s->data[s->len] = '\0';
    return s->len > 0 || c == '\n';
}

/* ----- tree node ------------------------------------------------------ */

typedef struct _dfsl_node {
    char               *line;
    int                 indent;
    struct _dfsl_node **children;
    int                 child_count;
    int                 child_cap;
} _dfsl_node_t;

static int _dfsl_count_indent(const char *s) {
    int n = 0;
    while (s[n] == ' ') n++;
    return n;
}

static _dfsl_node_t *_dfsl_node_new(const char *line) {
    _dfsl_node_t *n = (_dfsl_node_t *)calloc(1, sizeof(_dfsl_node_t));
    n->line         = (char *)malloc(strlen(line) + 1);
    strcpy(n->line, line);
    n->indent    = _dfsl_count_indent(line);
    n->child_cap = 4;
    n->children  = (_dfsl_node_t **)malloc(
        (size_t)n->child_cap * sizeof(_dfsl_node_t *));
    return n;
}

static void _dfsl_node_free(_dfsl_node_t *n) {
    for (int i = 0; i < n->child_count; i++) _dfsl_node_free(n->children[i]);
    free(n->children);
    free(n->line);
    free(n);
}

static void _dfsl_node_add_child(_dfsl_node_t *parent, _dfsl_node_t *child) {
    if (parent->child_count == parent->child_cap) {
        parent->child_cap *= 2;
        parent->children = (_dfsl_node_t **)realloc(
            parent->children,
            (size_t)parent->child_cap * sizeof(_dfsl_node_t *));
    }
    parent->children[parent->child_count++] = child;
}

/* ----- build / sort / write ------------------------------------------ */

static _dfsl_node_t *_dfsl_build_tree(char **lines, int count) {
    _dfsl_node_t *root = _dfsl_node_new("");
    root->indent = -1;

    _dfsl_node_t **stack = (_dfsl_node_t **)malloc(
        (size_t)(count + 2) * sizeof(_dfsl_node_t *));
    int top = 0;
    stack[top++] = root;

    for (int i = 0; i < count; i++) {
        _dfsl_node_t *node = _dfsl_node_new(lines[i]);
        if (lines[i][0] == '\0') {
            _dfsl_node_add_child(stack[top - 1], node);
            continue;
        }
        while (top > 1 && stack[top - 1]->indent >= node->indent)
            top--;
        _dfsl_node_add_child(stack[top - 1], node);
        stack[top++] = node;
    }
    free(stack);
    return root;
}

static int _dfsl_cmp(const void *a, const void *b) {
    return strcmp((*(const _dfsl_node_t **)a)->line,
                  (*(const _dfsl_node_t **)b)->line);
}

static void _dfsl_sort_tree(_dfsl_node_t *node) {
    if (node->child_count > 0) {
        qsort(node->children, (size_t)node->child_count,
              sizeof(_dfsl_node_t *), _dfsl_cmp);
        for (int i = 0; i < node->child_count; i++)
            _dfsl_sort_tree(node->children[i]);
    }
}

static void _dfsl_write_tree(FILE *fp, _dfsl_node_t *node, int skip_self) {
    if (!skip_self) fprintf(fp, "%s\n", node->line);
    for (int i = 0; i < node->child_count; i++)
        _dfsl_write_tree(fp, node->children[i], 0);
}

static void _dfsl_sort_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr,
                "[DEBUG_FILE_SORT_LINE] Cannot open for reading: %s\n",
                filename);
        return;
    }

    int    cap   = 256;
    int    count = 0;
    char **lines = (char **)malloc((size_t)cap * sizeof(char *));

    _dfsl_str_t buf;
    _dfsl_str_init(&buf);

    while (_dfsl_read_line(fp, &buf)) {
        if (count == cap) {
            cap *= 2;
            lines = (char **)realloc(lines, (size_t)cap * sizeof(char *));
        }
        lines[count] = (char *)malloc(buf.len + 1);
        memcpy(lines[count], buf.data, buf.len + 1);
        count++;
    }
    fclose(fp);
    _dfsl_str_free(&buf);

    if (count == 0) { free(lines); return; }

    _dfsl_node_t *root = _dfsl_build_tree(lines, count);
    _dfsl_sort_tree(root);

    fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr,
                "[DEBUG_FILE_SORT_LINE] Cannot open for writing: %s\n",
                filename);
    } else {
        _dfsl_write_tree(fp, root, 1);
        fclose(fp);
    }

    _dfsl_node_free(root);
    for (int i = 0; i < count; i++) free(lines[i]);
    free(lines);
}

#define DEBUG_FILE_SORT_LINE(filename) _dfsl_sort_file(filename)

#endif /* __cplusplus */
#endif /* DEBUG_FILE_SORT_LINE_H */
