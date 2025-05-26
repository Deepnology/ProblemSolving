#ifndef GENERIC_TRIE_H
#define GENERIC_TRIE_H

#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <functional>

//----------------------------------------------------------------------
// Marker type for "one value per node"
struct NoContainer {};

//----------------------------------------------------------------------
// ValueStorage: helper to store values at a node.
// Two specializations exist: one for a single value (using NoContainer)
// and one for a container type.
template<typename ValType, typename ValContainer>
struct ValueStorage;

// Specialization for a single value per node.
template<typename ValType>
struct ValueStorage<ValType, NoContainer> {
    std::optional<ValType> value;

    void insert(const ValType &val) { value = val; }
    std::optional<ValType> find() const { return value; }
    // find_ref returns an optional reference to the stored value.
    std::optional<std::reference_wrapper<ValType>> find_ref() {
        if (value)
            return { std::ref(*value) };
        return std::nullopt;
    }
    bool erase() {
        if (value) { value.reset(); return true; }
        return false;
    }
};

// Specialization for a container.
template<typename ValType, typename Container>
struct ValueStorage {
    Container values;

    void insert(const ValType &val) { values.insert(values.end(), val); }
    Container find() const { return values; }
    // find_ref returns a modifiable reference to the container.
    Container& find_ref() { return values; }
    const Container& find_ref() const { return values; }
    bool erase() {
        if (!values.empty()) { values.clear(); return true; }
        return false;
    }
};

//----------------------------------------------------------------------
// Primary template declaration for GenericTrie.
// The variadic parameter pack holds zero or more key/container pairs.
template<typename ValType, typename ValContainer, typename... Rest>
class GenericTrie;

//----------------------------------------------------------------------
// Leaf node specialization: no extra key/container pairs.
template<typename ValType, typename ValContainer>
class GenericTrie<ValType, ValContainer> {
public:
    ValueStorage<ValType, ValContainer> storage;

    // Insert value at the leaf node.
    // Returns a pair: an empty tuple and a bool indicating insertion occurred.
    std::pair<std::tuple<>, bool> insert(const ValType &val) {
        bool inserted = false;
        if (!storage.find()) {
            storage.insert(val);
            inserted = true;
        }
        return { std::tuple<>{}, inserted };
    }
    // find: returns a copy of the stored value (or container) (const version)
    auto find() const -> decltype(storage.find()) { return storage.find(); }
    // find_ref: returns a modifiable reference (for NoContainer, an optional reference)
    auto find_ref() -> decltype(storage.find_ref()) { return storage.find_ref(); }
    // Erase stored value(s)
    bool erase() { return storage.erase(); }
};

//----------------------------------------------------------------------
// Recursive node specialization: at least one key/container pair.
template<typename ValType, typename ValContainer,
         typename FirstKey, typename FirstChildContainer, typename... Rest>
class GenericTrie<ValType, ValContainer, FirstKey, FirstChildContainer, Rest...> {
public:
    // Build the child trie type recursively.
    using ChildTrie = GenericTrie<ValType, ValContainer, Rest...>;

    ValueStorage<ValType, ValContainer> storage;
    FirstChildContainer children;

    // Partial-key insertion (no keys provided): store the value at this node.
    std::pair<std::tuple<>, bool> insert(const ValType &val) {
        bool inserted = false;
        if (!storage.find()) {
            storage.insert(val);
            inserted = true;
        }
        return { std::tuple<>{}, inserted };
    }

    // Full-key insertion: with at least one key argument.
    template<typename... Keys>
    auto insert(const ValType &val, const FirstKey &first, const Keys&... rest)
        -> std::pair<decltype(std::tuple_cat(std::make_tuple(first),
                                              std::declval<typename decltype(children[first].insert(val, rest...))::first_type>())), bool>
    {
        // Ensure the child node exists (operator[] default-constructs if necessary)
        auto childRes = children[first].insert(val, rest...);
        auto fullTuple = std::tuple_cat(std::make_tuple(first), childRes.first);
        return { fullTuple, childRes.second };
    }

    // Full-key find (const version): traverse children with provided keys.
    template<typename... Keys>
    auto find(const FirstKey &first, const Keys&... rest) const
         -> decltype( children.at(first).find(rest...) )
    {
        auto it = children.find(first);
        if (it != children.end())
            return it->second.find(rest...);
        return decltype(children.at(first).find(rest...)){};
    }
    // Partial-key find: returns the value(s) stored at this node.
    auto find() const -> decltype(storage.find()) { return storage.find(); }

    // Full-key find_ref (non-const version).
    // Note: key parameters are now accepted as const references.
    template<typename... Keys>
    auto find_ref(const FirstKey &first, const Keys&... rest)
         -> decltype( children.at(first).find_ref(rest...) )
    {
        auto it = children.find(first);
        if (it != children.end())
            return it->second.find_ref(rest...);
        return decltype(children.at(first).find_ref(rest...) ){};
    }
    // Partial-key find_ref: returns a modifiable reference to value(s) stored at this node.
    auto find_ref() -> decltype(storage.find_ref()) { return storage.find_ref(); }

    // Erase: when key arguments are provided, delegate to the child.
    template<typename... Keys>
    bool erase(const FirstKey &first, const Keys&... rest) {
        auto it = children.find(first);
        if (it != children.end())
            return it->second.erase(rest...);
        return false;
    }
    // Partial-key erase: erase the value stored at this node.
    bool erase() { return storage.erase(); }
};

//----------------------------------------------------------------------
// Helper function to lookup by a cached key tuple.
template<typename Trie, typename Tuple>
auto find_from_tuple(const Trie& trie, const Tuple& keys) {
    return std::apply([&trie](auto&&... args) { return trie.find(args...); }, keys);
}

template<typename Trie, typename Tuple>
auto find_ref_from_tuple(Trie &trie, const Tuple &keys) {
    return std::apply([&trie](auto&&... args) -> decltype(auto) {
        return trie.find_ref(args...);
    }, keys);
}

//----------------------------------------------------------------------
// Metafunction to build a custom trie type from a sequence of key/container pair types.
// Each pair type must define:
//   - a member type 'key' for the key type at that level.
//   - a member template 'template<typename Child> container' that yields
//     the container type for storing child nodes of type Child.
template<typename ValType, typename ValContainer, typename... Pairs>
struct MakeCustomTrie;

// Base case: no pairs -> leaf.
template<typename ValType, typename ValContainer>
struct MakeCustomTrie<ValType, ValContainer> {
    using type = GenericTrie<ValType, ValContainer>;
};

// One pair provided.
template<typename ValType, typename ValContainer, typename FirstPair>
struct MakeCustomTrie<ValType, ValContainer, FirstPair> {
    using type = GenericTrie<ValType, ValContainer,
        typename FirstPair::key,
        typename FirstPair::template container< GenericTrie<ValType, ValContainer> > >;
};

// Two or more pairs.
template<typename ValType, typename ValContainer, typename FirstPair, typename... RestPairs>
struct MakeCustomTrie<ValType, ValContainer, FirstPair, RestPairs...> {
    using ChildTrie = typename MakeCustomTrie<ValType, ValContainer, RestPairs...>::type;
    using type = GenericTrie<ValType, ValContainer,
        typename FirstPair::key,
        typename FirstPair::template container< ChildTrie > >;
};

template<typename ValType, typename ValContainer, typename... Pairs>
using GenericTrieCustom = typename MakeCustomTrie<ValType, ValContainer, Pairs...>::type;

//----------------------------------------------------------------------
// Example key–container pair structures.
// Users define these to choose their key types and the container type for that level.
struct CharMapPair {
    using key = char;
    template<typename Child>
    using container = std::map<char, Child>;
};

struct IntMapPair {
    using key = int;
    template<typename Child>
    using container = std::map<int, Child>;
};

//----------------------------------------------------------------------
// Example usage.
inline int GenericTrie_Test() {
    // Define a two-level trie storing std::string values (one per node) using:
    //   Level 1: char keys with a std::map (via CharMapPair)
    //   Level 2: int keys with a std::map (via IntMapPair)
    using MyTrie = GenericTrieCustom<std::string, NoContainer, CharMapPair, IntMapPair>;
    MyTrie trie;

    // Full-key insertion: returns a tuple of keys that can be cached.
    auto [fullKey, inserted1] = trie.insert("FullValue_A1", 'a', 1);
    std::cout << "Inserted 'FullValue_A1' with keys: ";
    std::apply([](auto&&... args) { ((std::cout << args << " "), ...); }, fullKey);
    std::cout << "\n";

    // Partial-key insertion at level 1:
    auto [partialKey, inserted2] = trie.insert("PartialValue_B", 'b');
    std::cout << "Inserted 'PartialValue_B' at level 1 with key: ";
    std::apply([](auto&&... args) { ((std::cout << args << " "), ...); }, partialKey);
    std::cout << "\n";

    // Insertion at the root (empty prefix).
    auto [rootKey, insertedRoot] = trie.insert("RootValue");
    std::cout << "Inserted 'RootValue' at the root (empty key tuple).\n";

    // Using the cached fullKey tuple to lookup:
    if (auto res = find_from_tuple(trie, fullKey))
        std::cout << "Found full key ('a', 1): " << *res << "\n";
    else
        std::cout << "Full key ('a', 1) not found.\n";

    // Partial-key lookup at level 1:
    if (auto res = trie.find('b'))
        std::cout << "Found partial key ('b'): " << *res << "\n";
    else
        std::cout << "Partial key ('b') not found.\n";

    // Lookup at the root.
    if (auto res = trie.find())
        std::cout << "Found root value: " << *res << "\n";
    else
        std::cout << "No root value found.\n";

    // Demonstrate find_ref: get a non-const reference to a full-key node.
    // Note: since find_ref now takes its key parameters as const references,
    // we can pass literal values.
    if (auto refOpt = trie.find_ref('a', 1)) {
        // Modify the value in place.
        refOpt->get() = "ModifiedFullValue_A1";
        std::cout << "Modified full key ('a', 1) via find_ref.\n";
    }

    // Confirm modification.
    if (auto res = find_from_tuple(trie, fullKey))
        std::cout << "After modification, full key ('a', 1): " << *res << "\n";

    // Erase value at level-1 node for key 'b'.
    if (trie.erase('b'))
        std::cout << "Erased value at partial key ('b').\n";
    else
        std::cout << "Failed to erase at partial key ('b').\n";

    // Confirm erasure.
    if (auto res = trie.find('b'))
        std::cout << "After erase, found at ('b'): " << *res << "\n";
    else
        std::cout << "After erase, no value at ('b').\n";

    auto [fullKey2, inserted] = trie.insert("MyValue", 'a', 1);
    // Later, lookup via the cached key tuple:
    if (auto refOpt = find_ref_from_tuple(trie, fullKey2)) {
        // Modify the value in place
        refOpt->get() = "ModifiedValue";
        std::cout << "Value modified via find_ref_from_tuple." << std::endl;
    } else {
        std::cout << "Key not found." << std::endl;
    }

    return 0;
}




#endif

/*
//---------------------------------------------------------------------
// A tag type to indicate “no container” (i.e. a node caches a single value)
struct NoContainer {};

//---------------------------------------------------------------------
// ValueStorage: abstracts how a node stores its value.
// If ValContainer is NoContainer then value is stored in an std::optional;
// otherwise, a container (with typical insert/erase/find operations) is used.

template<typename ValType, typename ValContainer>
struct ValueStorage {
    ValContainer values; // e.g. a container type that supports insert, erase, find

    bool insert_value(const ValType &val) {
        auto res = values.insert(val);
        return res.second;
    }
    bool erase_value(const ValType &val) {
        return values.erase(val) > 0;
    }
    // For container–based storage, if non–empty we return the first element.
    std::optional<ValType> find_value() const {
        if (!values.empty())
            return *values.begin();
        return std::nullopt;
    }
};

template<typename ValType>
struct ValueStorage<ValType, NoContainer> {
    std::optional<ValType> value;

    bool insert_value(const ValType &val) {
        if (!value) {
            value = val;
            return true;
        }
        return false;
    }
    bool erase_value(const ValType &val) {
        if (value && *value == val) {
            value.reset();
            return true;
        }
        return false;
    }
    std::optional<ValType> find_value() const {
        return value;
    }
};

//---------------------------------------------------------------------
// Forward declaration of TrieNode
template<typename ValType, typename ValContainer, typename... KeyContainerPairs>
struct TrieNode;

// Base case: no key/container pair; the node simply stores a value.
template<typename ValType, typename ValContainer>
struct TrieNode<ValType, ValContainer> : public ValueStorage<ValType, ValContainer> {
    // Insert: simply cache the value.
    auto insert_impl(const ValType &val) {
        bool inserted = this->insert_value(val);
        return std::make_pair(std::tuple<>{}, inserted);
    }
    auto erase_impl(const ValType &val) {
        bool erased = this->erase_value(val);
        return std::make_pair(std::tuple<>{}, erased);
    }
    // find_impl (base case) returns the stored value (if any)
    auto find_impl() const
      -> std::optional<std::conditional_t<std::is_same_v<ValContainer, NoContainer>,
                                           ValType, ValContainer>>
    {
        return this->find_value();
    }
};

// Recursive case: the node uses one key/container pair to index its children.
template<typename ValType, typename ValContainer, typename FirstKey, typename FirstChildContainer, typename... Rest>
struct TrieNode<ValType, ValContainer, FirstKey, FirstChildContainer, Rest...>
    : public ValueStorage<ValType, ValContainer>
{
    using ChildNode = TrieNode<ValType, ValContainer, Rest...>;
    FirstChildContainer children; // e.g. a std::map<FirstKey, ChildNode>

    template<typename T, typename... Ts>
    auto insert_impl(const ValType &val, T&& key, Ts&&... rest)
      -> std::pair<std::tuple<std::decay_t<T>, std::decay_t<Ts>...>, bool>
    {
        auto it = children.find(key);
        if (it == children.end()) {
            auto res = children.insert(std::make_pair(key, ChildNode()));
            it = res.first;
        }
        auto childRes = it->second.insert_impl(val, std::forward<Ts>(rest)...);
        auto fullTuple = std::tuple_cat(std::make_tuple(key), childRes.first);
        return { fullTuple, childRes.second };
    }

    template<typename T, typename... Ts>
    auto erase_impl(const ValType &val, T&& key, Ts&&... rest)
      -> std::pair<std::tuple<std::decay_t<T>, std::decay_t<Ts>...>, bool>
    {
        auto it = children.find(key);
        if (it == children.end()) {
            return { std::tuple_cat(std::make_tuple(key), std::tuple<std::decay_t<Ts>...>{}), false };
        }
        auto childRes = it->second.erase_impl(val, std::forward<Ts>(rest)...);
        auto fullTuple = std::tuple_cat(std::make_tuple(key), childRes.first);
        return { fullTuple, childRes.second };
    }

    // Recursive find_impl: consumes one key at a time.
    template<typename T, typename... Ts>
    auto find_impl(T&& key, Ts&&... rest) const
      -> std::optional<std::conditional_t<std::is_same_v<ValContainer, NoContainer>,
                                           ValType, ValContainer>>
    {
        auto it = children.find(key);
        if (it == children.end())
            return std::nullopt;
        auto childOpt = it->second.find_impl(std::forward<Ts>(rest)...);
        if (childOpt)
            return *childOpt;
        else
            return std::nullopt;
    }
    // Overload when no further key is provided.
    auto find_impl() const
      -> std::optional<std::conditional_t<std::is_same_v<ValContainer, NoContainer>,
                                           ValType, ValContainer>>
    {
        return this->find_value();
    }
};

//---------------------------------------------------------------------
// The public interface: GenericTrie wraps a root TrieNode.
template<typename ValType, typename ValContainer, typename... KeyContainerPairs>
class GenericTrie {
public:
    using RootNode = TrieNode<ValType, ValContainer, KeyContainerPairs...>;
    RootNode root;

    template<typename... Args>
    auto insert(const ValType& val, Args&&... keys)
      -> std::pair<std::tuple<std::decay_t<Args>...>, bool>
    {
        return root.insert_impl(val, std::forward<Args>(keys)...);
    }

    template<typename... Args>
    bool erase(const ValType& val, Args&&... keys) {
        auto [tuple, erased] = root.erase_impl(val, std::forward<Args>(keys)...);
        return erased;
    }

    template<typename... Args>
    auto find(Args&&... keys) const
      -> std::optional<std::conditional_t<std::is_same_v<ValContainer, NoContainer>,
                                           ValType, ValContainer>>
    {
        return root.find_impl(std::forward<Args>(keys)...);
    }
};



//---------------------------------------------------------------------
// Define node types for a four-level trie.
// Level5 is the leaf node (stores the value).
// Level4: indexed by a double key.
// Level3: indexed by a std::string key.
// Level2: indexed by an int key.
// The root uses a short key.
using Level5 = TrieNode<std::string, NoContainer>;
using Level4 = TrieNode<std::string, NoContainer, double, std::map<double, Level5>>;
using Level3 = TrieNode<std::string, NoContainer, std::string, std::map<std::string, Level4>>;
using Level2 = TrieNode<std::string, NoContainer, int, std::map<int, Level3>>;

using MyTrie = GenericTrie<
    std::string,    // Value type
    NoContainer,    // Single value per node
    short,  std::map<short, Level2>
>;

//---------------------------------------------------------------------
// Extended test examples.
inline int GenericTrie_Test(){
    MyTrie trie;

    // Insert several values at different key paths.
    // Each insert requires four keys: short, int, std::string, double.
    auto [keys1, inserted1] = trie.insert("v1", short(1), int(2), std::string("a"), 2.5);
    auto [keys2, inserted2] = trie.insert("v2", short(1), int(2), std::string("a"), 3.5);
    auto [keys3, inserted3] = trie.insert("v3", short(1), int(2), std::string("b"), 2.5);
    auto [keys4, inserted4] = trie.insert("v4", short(2), int(3), std::string("c"), 5.0);

    std::cout << "Inserted v1? " << inserted1 << "\n";
    std::cout << "Inserted v2? " << inserted2 << "\n";
    std::cout << "Inserted v3? " << inserted3 << "\n";
    std::cout << "Inserted v4? " << inserted4 << "\n\n";

    // Search for inserted values.
    if(auto res = trie.find(short(1), int(2), std::string("a"), 2.5))
        std::cout << "Found at (1,2,\"a\",2.5): " << *res << "\n";
    else
        std::cout << "Not found at (1,2,\"a\",2.5)\n";

    if(auto res = trie.find(short(1), int(2), std::string("a"), 3.5))
        std::cout << "Found at (1,2,\"a\",3.5): " << *res << "\n";
    else
        std::cout << "Not found at (1,2,\"a\",3.5)\n";

    if(auto res = trie.find(short(1), int(2), std::string("b"), 2.5))
        std::cout << "Found at (1,2,\"b\",2.5): " << *res << "\n";
    else
        std::cout << "Not found at (1,2,\"b\",2.5)\n";

    if(auto res = trie.find(short(2), int(3), std::string("c"), 5.0))
        std::cout << "Found at (2,3,\"c\",5.0): " << *res << "\n";
    else
        std::cout << "Not found at (2,3,\"c\",5.0)\n";

    // Try finding a key that doesn't exist.
    if(auto res = trie.find(short(1), int(2), std::string("a"), 9.9))
        std::cout << "Found at (1,2,\"a\",9.9): " << *res << "\n";
    else
        std::cout << "Not found at (1,2,\"a\",9.9)\n";

    std::cout << "\n--- Erase tests ---\n";

    // Erase one of the entries (v2).
    bool erased = trie.erase("v2", short(1), int(2), std::string("a"), 3.5);
    std::cout << "Erased v2? " << erased << "\n";
    if(auto res = trie.find(short(1), int(2), std::string("a"), 3.5))
        std::cout << "Found v2 after erase: " << *res << "\n";
    else
        std::cout << "v2 not found after erase (as expected).\n";

    // Try erasing a value that was never inserted.
    bool erasedWrong = trie.erase("nonexistent", short(1), int(2), std::string("b"), 2.5);
    std::cout << "Attempt to erase nonexistent value? " << erasedWrong << "\n";

    // Erase remaining entries.
    trie.erase("v1", short(1), int(2), std::string("a"), 2.5);
    trie.erase("v3", short(1), int(2), std::string("b"), 2.5);
    trie.erase("v4", short(2), int(3), std::string("c"), 5.0);

    std::cout << "\nAfter erasing all values:\n";
    if(auto res = trie.find(short(1), int(2), std::string("a"), 2.5))
        std::cout << "Found v1 after full erase: " << *res << "\n";
    else
        std::cout << "v1 not found after full erase.\n";

    if(auto res = trie.find(short(1), int(2), std::string("b"), 2.5))
        std::cout << "Found v3 after full erase: " << *res << "\n";
    else
        std::cout << "v3 not found after full erase.\n";

    if(auto res = trie.find(short(2), int(3), std::string("c"), 5.0))
        std::cout << "Found v4 after full erase: " << *res << "\n";
    else
        std::cout << "v4 not found after full erase.\n";

    return 0;
}

*/
