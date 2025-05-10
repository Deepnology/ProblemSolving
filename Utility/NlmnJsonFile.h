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

    m().push_back({"e",{"f",""}});
    m().push_back({"d",{{"?",""}}});
    m().push_back({"c",{{"",""}}});
    m().push_back({"b",{""}});
    m(std::vector<std::string>{}).push_back({"a",nullptr});
    m(std::vector<std::variant<std::string,int>>{}).push_back({"1",{}});
    m(std::vector<std::variant<std::string,int>>{"e",1}) = nlohmann::json::array();

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
