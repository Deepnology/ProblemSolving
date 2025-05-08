#ifndef NLMN_JSON_FILE_H
#define NLMN_JSON_FILE_H

#include <fstream>
#include <iostream>
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

    template<typename KeyIterable>
    nlohmann::json& operator()(const KeyIterable& keys)
    {
        if (auto p = getPtr(keys)) return *p;
        throw std::out_of_range("JSON path not found");
    }

    template<typename KeyIterable>
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

    template<typename KeyIterable>
    nlohmann::json* getPtr(const KeyIterable& keys)
    {
        return const_cast<nlohmann::json*>(
            static_cast<const NlmnJsonFile*>(this)->getPtr(keys)
            );
    }

    //works for std::vector<std::string>, std::list<std::string>, std::set<std::string>
    template<typename KeyIterable,
        typename = std::enable_if_t<
        !std::is_same_v<NlmnJsonFile, std::decay_t<KeyIterable>>
        >>
    const nlohmann::json* getPtr(const KeyIterable& keys) const
    {
        const nlohmann::json* cur = &json_;
        for (const auto& key : keys)
        {
            if (!cur->is_object())
                return nullptr;
            auto itr = cur->find(key);
            if (itr == cur->end())
                return nullptr;
            cur = &*itr;
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

    template<typename KeyIterable>
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
    m()["key2"] = 2;
    m()["key3"] = {{"key32","val"},{"key31",{3,2,1,2,3}}};
    m()["key0"] = {"d","c",{"a",{"2",nullptr,"1"}},{"b","c"}};
    m()["key0"][2].push_back("b");
    m()["key01"] = {{"d",{}},{"c",nullptr},{"a",{"2",nullptr,"1"}},{"b","c"}};
    m()["key3"]["key32"] = 5;//update existing value from array to single value
    m()["key3"]["key1"]["key2"] = {"a","b"};
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
    m().push_back({"a",nullptr});
    m().push_back({"1",{}});

    std::cout << "contains key4,key1: " << m.contains(std::vector<std::string>{ "key4","key1" }) << ":[" 
        << m(std::vector<std::string>{ "key4", "key1" })[0] << ","
        << m(std::vector<std::string>{ "key4", "key1" })[1] << ","
        << m(std::vector<std::string>{ "key4", "key1" })[2] << "]"
        << std::endl;

    std::cout << "contains key3,key33: " << m.contains(std::vector<std::string>{ "key3", "key33" }) << ":"
        << m(std::vector<std::string>{ "key3", "key33" })
        << std::endl;
    
    m.sort();
    std::cout << m << std::endl;
    std::cout << m()["key3"]["key31"][2] << std::endl;
}

#endif
