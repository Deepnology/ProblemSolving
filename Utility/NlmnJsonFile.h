#ifndef NLMN_JSON_FILE_H
#define NLMN_JSON_FILE_H

#include <fstream>
#include <iostream>
#include <type_traits>
#include "nlohmann/json.hpp"

class NlmnJsonFile
{
public:
    explicit NlmnJsonFile(const std::string& filePath) : filePath_(filePath)
    {
        std::ifstream file(filePath_);
        if (file.is_open())
        {
            try
            {
                file >> json_;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error parsing JSON from file: " << e.what() << std::endl;
                throw;
            }
        }
        else
        {
            std::cerr << "File not found. Creating a new JSON file." << std::endl;
            json_ = nlohmann::json::object();
        }
    }

    ~NlmnJsonFile()
    {
        try
        {
            std::ofstream file(filePath_);
            if (file.is_open())
            {
                file << std::setw(4) << json_ << std::endl;
            }
            else
            {
                std::cerr << "Unable to open file for writing: " << filePath_ << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error writing JSON to file: " << e.what() << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const NlmnJsonFile& mgr)
    {
        os << std::setw(4) << mgr.json_;
        return os;
    }

    template<std::ranges::range KeyIterable>
    nlohmann::json& operator()(const KeyIterable& keys)
    {
        if (auto p = getPtr(keys)) return *p;
        throw std::out_of_range("JSON path not found");
    }

    template<std::ranges::range KeyIterable>
    const nlohmann::json& operator()(const KeyIterable& keys) const
    {
        if (auto p = getPtr(keys)) return *p;
        throw std::out_of_range("JSON path not found");
    }

    nlohmann::json& operator()()
    {
        return json_;
    }

    const nlohmann::json& operator()() const
    {
        return json_;
    }

    template<std::ranges::range KeyIterable>
    nlohmann::json* getPtr(const KeyIterable& keys)
    {
        return const_cast<nlohmann::json*>(
            static_cast<const NlmnJsonFile*>(this)->getPtr(keys)
            );
    }

    template<std::ranges::range KeyIterable>
    const nlohmann::json* getPtr(const KeyIterable& keys) const
    {
        const nlohmann::json* cur = &json_;
        for (auto const& key : keys)
        {
            cur = dispatch_key(cur, key);
            if (!cur) return nullptr;
        }
        return cur;
    }

    nlohmann::json* getPtr()
    {
        return &json_;
    }

    const nlohmann::json* getPtr() const
    {
        return &json_;
    }

    template<std::ranges::range KeyIterable>
    bool contains(const KeyIterable& keys) const
    {
        return getPtr(keys) != nullptr;
    }

    template<std::ranges::range KeyIterable>
    nlohmann::json& set(const KeyIterable& keys,
                        nlohmann::json value)
    {
        // copy keys into a small buffer so we can pop the last element
        std::vector<std::ranges::range_value_t<KeyIterable>> buf{
            keys.begin(), keys.end()
        };

        // if empty: replace the entire document
        if (buf.empty()) {
            json_ = std::move(value);
            return json_;
        }

        // walk (and create) all but the last key
        nlohmann::json* cur = &json_;
        for (size_t i = 0; i + 1 < buf.size(); ++i) {
            cur = navigate_or_create(cur, buf[i]);
        }

        // now assign at the final key
        auto* leaf = navigate_or_create(cur, buf.back());
        *leaf = std::move(value);
        return *leaf;
    }

    /// Remove the node at `keys`.
    /// Returns true if something was erased, false otherwise.
    template<std::ranges::range KeyIterable>
    bool remove(const KeyIterable& keys) {
        // buffer all the keys so we can peel off the last one
        std::vector<std::ranges::range_value_t<KeyIterable>> buf(
            keys.begin(), keys.end()
        );
        if (buf.empty()) {
            json_.clear();
            return true;
        }

        // pop off the last key
        auto last = std::move(buf.back());
        buf.pop_back();

        // find the parent of the thing to delete
        const nlohmann::json* parent_c = getPtr(buf);
        if (!parent_c) return false;            // prefix not present

        // cast away const to mutate
        nlohmann::json* parent = const_cast<nlohmann::json*>(parent_c);

        // dispatch deletion on the final key
        return remove_key(parent, last);
    }

    //to support non-leaf nodes with value or array of values
    static constexpr std::string_view HIDDEN = "__value__";

    /// Insert a value at the node given by `keys` (creating all ancestors) under the
    /// hidden key; returns a pointer to the stored value.
    template<std::ranges::range KeyIterable>
    nlohmann::json* insertSpecial(const KeyIterable& keys,
                                  nlohmann::json value)
    {
        // 1) build the node path
        nlohmann::json* node = &json_;
        for (auto const& k : keys) {
            node = navigate_or_create(node, k);
        }

        // 2) ensure it’s an object so we can stick __value__ inside
        if (!node->is_object()) {
            *node = nlohmann::json::object();
        }

        // 3) insert (or overwrite) the hidden value
        (*node)[HIDDEN] = std::move(value);
        return &(*node)[HIDDEN];
    }

    /// Remove the hidden "__value__" at `keys`.
    /// Returns true if it was present and removed, false otherwise.
    template<std::ranges::range KeyIterable>
    bool removeSpecial(const KeyIterable& keys) {
        // 1) locate the node
        const auto* node_c = getPtr(keys);
        if (!node_c || !node_c->is_object())
            return false;

        // 2) erase __value__ and return success
        auto* node = const_cast<nlohmann::json*>(node_c);
        return node->erase(HIDDEN) > 0;
    }

    /// Look up the hidden value at `keys`; returns nullptr if the path or hidden
    /// key doesn’t exist.
    template<std::ranges::range KeyIterable>
    const nlohmann::json* getSpecial(const KeyIterable& keys) const
    {
        if (auto node = getPtr(keys)) {
            if (!node->is_object()) return nullptr;
            auto it = node->find(HIDDEN);
            if (it != node->end())
                return &*it;
        }
        return nullptr;
    }

    /// mutable‐pointer overload for getSpecial
    template<std::ranges::range KeyIterable>
    nlohmann::json* getSpecial(const KeyIterable& keys)
    {
        return const_cast<nlohmann::json*>(
          static_cast<const NlmnJsonFile*>(this)->getSpecial(keys)
        );
    }

    template<std::ranges::range KeyIterable>
    bool containsSpecial(const KeyIterable& keys) const
    {
        return getSpecial(keys) != nullptr;
    }

    void sort()
    {
        sortRecur(json_);
    }

private:
    void sortRecur(nlohmann::json& j)
    {
        if (j.is_object())
        {
            // Sort the keys in an object
            nlohmann::json sorted_json = nlohmann::json::object();
            std::vector<std::string> keys;
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                keys.push_back(it.key());
            }
            std::sort(keys.begin(), keys.end());

            for (const auto& key : keys)
            {
                sorted_json[key] = j[key];
                sortRecur(sorted_json[key]);
            }
            j = std::move(sorted_json);
        }
        else if (j.is_array())
        {
            // Sort arrays (if applicable, assuming it's sortable data)
            std::sort(j.begin(), j.end());
            for (auto& elem : j)
            {
                sortRecur(elem);
            }
        }
    }

    // helper: pick the right lookup based on the static type of `Key`
    template<typename Key>
    static const nlohmann::json* dispatch_key(const nlohmann::json* cur,
                                              const Key& key)
    {
        if constexpr (is_variant<std::remove_cvref_t<Key>>::value) {
            // unfold the variant, recurse on the held alternative
            return std::visit([cur](auto&& actual) {
                return dispatch_key(cur, actual);
            }, key);
        }
        else if constexpr (std::integral<std::remove_cvref_t<Key>>) {
            // array-index case
            if (!cur->is_array()) return nullptr;
            auto idx = static_cast<std::size_t>(key);
            return idx < cur->size() ? &(*cur)[idx] : nullptr;
        }
        else if constexpr (std::convertible_to<Key, std::string_view>) {
            // object-lookup case
            if (!cur->is_object()) return nullptr;
            std::string_view sv{key};
            auto it = cur->find(sv);
            return it != cur->end() ? &*it : nullptr;
        }
        else {
            static_assert(dependent_false<Key>,
                          "Key type must be integral, string-convertible, or std::variant thereof");
        }
    }

    // dispatch helper for get/set: returns nullptr on get, or &child on create
    template<typename Key>
    static nlohmann::json* navigate_or_create(nlohmann::json* cur,
                                               const Key& key)
    {
        if constexpr (is_variant<std::remove_cvref_t<Key>>::value) {
            // unwrap variant
            return std::visit(
                [cur](auto&& actual){
                    return navigate_or_create(cur, actual);
                },
                key
            );
        }
        else if constexpr (std::integral<std::remove_cvref_t<Key>>) {
            // array‐index case
            if (!cur->is_array())
                *cur = nlohmann::json::array();
            auto idx = static_cast<size_t>(key);
            if (idx >= cur->size())
            {
                // insert (idx+1 - old_size) nulls at the end
                cur->insert(cur->end(),
                            idx + 1 - cur->size(),
                            nullptr);
            }
            return &(*cur)[idx];
        }
        else if constexpr (std::convertible_to<Key, std::string_view>) {
            // object‐lookup case
            if (!cur->is_object())
                *cur = nlohmann::json::object();
            auto sv = std::string_view{key};
            return &(*cur)[sv];           // operator[] will create the key if missing
        }
        else {
            static_assert(dependent_false<Key>,
                          "Key must be integral, string‐convertible, or variant thereof");
        }
    }

    // dispatch-based remover for one key/index
    template<typename Key>
    static bool remove_key(nlohmann::json* parent, const Key& key) {
        if constexpr (is_variant<std::remove_cvref_t<Key>>::value) {
            // unwrap and re-dispatch
            return std::visit(
                [parent](auto&& actual){
                    return remove_key(parent, actual);
                },
                key
            );
        }
        else if constexpr (std::integral<std::remove_cvref_t<Key>>) {
            // array-index case
            if (!parent->is_array()) return false;
            size_t idx = static_cast<size_t>(key);
            if (idx >= parent->size()) return false;
            parent->erase(parent->begin() + idx);
            return true;
        }
        else if constexpr (std::convertible_to<Key, std::string_view>) {
            // object-key case
            if (!parent->is_object()) return false;
            auto sv = std::string_view{key};
            return parent->erase(sv) > 0;
        }
        else {
            static_assert(dependent_false<Key>,
                          "Key must be int, string-like, or variant thereof");
        }
    }

    // trait to detect std::variant<...>
    template<typename T> struct is_variant : std::false_type {};
    template<typename... Ts>
    struct is_variant<std::variant<Ts...>> : std::true_type {};

    template<typename> static constexpr bool dependent_false = false;

private:
    std::string filePath_;
    nlohmann::json json_;
};

inline void NlmnJsonFile_Test()
{
    NlmnJsonFile m("example.json");
    //std::cout << m << std::endl;
    m().clear();
    m()["key1"] = "val1";
    m()["key1"] = "val2";
    m()["key2"] = 2;
    m()["key3"] = {{"key32","val"},{"key31",{3,2,1,2,3}}};
    m()["key0"] = {"d","c",{"a",{"2",nullptr,"1"}},{"b","c"}};
    m()["key0"][2].push_back("b");
    m()["key0"][3].push_back("d");
    m()["key0"][3].push_back({{"1","1"},{"2","2"}});
    m()["key01"] = {{"d",{}},{"c",nullptr},{"a",{"2",nullptr,"1"}},{"b","c"}};
    m()["key3"]["key32"] = 5;//update existing value from array to single value
    m()["key3"]["key1"]["key2"] = {{"a","1"},{"b",{"x","y","z"}},{"c","3"}};
    m()["key3"]["key1"]["key2"]["d"] = nlohmann::json::array();
    m()["key3"]["key1"]["key2"]["d"].push_back({"x",nlohmann::json::array()});
    m()["key3"]["key1"]["key2"]["d"].push_back({"y","2"});
    m()["key3"]["key1"]["key2"]["d"].push_back({"z","3"});
    m()["key3"]["key1"]["key2"]["d"].push_back({{"p","4"},{"",""}});
    m()["key3"]["key1"]["key2"]["d"].push_back({{"q","5"},{"r",8}, nlohmann::json::array(), nlohmann::json::array()});
    m()["key3"]["key33"] = 33;
    m()["key4"]["key1"] = {0,1};
    m()["key4"]["key2"] = {0,0,0};
    //m()["key4"]["key1"]["key2"] = {1,1,1};
    //error: once a prefix node has single value or array of values, it becomes a leaf node and cannot extend the prefix to create trie of trie
    //m()["key4"] = {1,1};
    //error: non-leaf nodes cannot have single value or array of values
    m().push_back({"key4",{"key2",5}});//ignored
    m()["key4"]["key1"].push_back(2);
    m()["key4"]["key2"].push_back(1);
    //m()["key3"]["key32"].push_back(6);
    //error: the existing value is single value, not an array

    m(std::vector<std::variant<std::string,int>>{})["__value__"] = {{"v1","1"},{"v2","2"}};

    m().push_back({"e",{"f",""}});
    m().push_back({"d",{{"?",""}}});
    m().push_back({"c",{{"",""}}});
    m().push_back({"b",{""}});
    m(std::vector<std::string>{}).push_back({"a",nullptr});
    m(std::vector<std::variant<std::string,int>>{}).push_back({"1",{}});
    m(std::vector<std::variant<std::string,int>>{"e",1}) = nlohmann::json::array();

    m(std::vector<std::variant<std::string,int>>{"d"})["__value__"] = {{"v1","1"},{"v2","2"}};

    m.set(std::vector<std::variant<std::string,int>>{"key0",0}, {"d","d"});
    m.set(std::vector<std::variant<std::string,int>>{"key0",1}, {{"c","c"}});
    m.set(std::vector<std::variant<std::string,int>>{"key0",3,0}, {"b"});
    m.set(std::vector<std::variant<std::string,int>>{"key0",3,1}, {{"c","c"}});
    m.set(std::vector<std::variant<std::string,int>>{"key0",5,1}, {{"c","c"}});
    m.set(std::vector<std::variant<std::string,int>>{"key3", "x", "y", "z"}, 3);
    m.set(std::vector<std::variant<std::string,int>>{"key3", "x", "y"}, 2);//removes "z"
    m.remove(std::vector<std::variant<std::string,int>>{"key0", 3, 3, "1"});
    m.remove(std::vector<std::variant<std::string,int>>{"key0", 2, 1, 0});

    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special"}, 1);
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special"}, 2);
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "a", "b", "c"}, 3);
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "a", "b"}, 2);
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "a"}, 1);
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "a", "b", "d"}, 4);
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "a", "b", "e"}, 5);
    m.remove(std::vector<std::variant<std::string,int>>{"Special", "a", "b", "d"});
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "x", "y", "z"}, 9);
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "x", "y"}, {7,8});
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "x"}, {{"k","v"}});
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 5, "a", "b", "c"}, "5");
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 5, "a", "b"}, {3,4});
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 5, "a"}, {2});
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 5, "b"}, 3);
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 2}, "2");
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 7}, "7");
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 6, "x", "y", "z"}, "");
    //m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array"}, "array val");//changes "array" to object
    *m.getSpecial(std::vector<std::variant<std::string,int>>{"Special", "a", "b", "c"}) = "333";
    *m.getSpecial(std::vector<std::variant<std::string,int>>{"Special", "a"}) = "111";
    *m.getSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 2})= {"222"};
    m.getSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 2})->push_back("22");
    m.insertSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 1}, {{"k","v"}});
    m.getSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 1})->push_back({"j","k"});
    (*m.getSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 1}))["j"] = "m";
    m.removeSpecial(std::vector<std::variant<std::string,int>>{});
    m.removeSpecial(std::vector<std::variant<std::string,int>>{"d"});
    m.removeSpecial(std::vector<std::variant<std::string,int>>{"Special", "array", 5, "a", "b"});
    m.remove(std::vector<std::variant<std::string,int>>{"Special", "array", 3});

    std::cout << m << std::endl;

    std::cout << "contains key4,key1: " << m.contains(std::vector<std::string>{ "key4","key1" }) << ":[" 
        << m(std::vector<std::string>{ "key4", "key1" })[0] << ","
        << m(std::vector<std::string>{ "key4", "key1" })[1] << ","
        << m(std::vector<std::string>{ "key4", "key1" })[2] << "]"
        << std::endl;

    std::cout << "contains key3,key33: " << m.contains(std::vector<std::string>{ "key3", "key33" }) << ":"
        << m(std::vector<std::string>{ "key3", "key33" })
        << std::endl;
    
    std::cout << "contains key3,key1,Key2,d,1,0: " << m.contains(std::vector<std::variant<std::string,int>>{ "key3", "key1", "key2", "d", 1, 0 }) << ":"
        << m(std::vector<std::variant<std::string,int>>{ "key3", "key1", "key2", "d", 1, 0 })
        << std::endl;

    std::cout << "contains key3,key1,Key2,d,3,p: " << m.contains(std::vector<std::variant<std::string,int>>{ "key3", "key1", "key2", "d", 3, "p" }) << ":"
        << m(std::vector<std::variant<std::string,int>>{ "key3", "key1", "key2", "d", 3, "p" })
        << std::endl;

    std::cout << "contains key3,key1,Key2,d,0,1: " << m.contains(std::vector<std::variant<std::string,int>>{ "key3", "key1", "key2", "d", 0, 1 }) << std::endl;

    //std::cout << "sort: " << std::endl;
    //m.sort();
    //std::cout << m << std::endl;
}

#endif
