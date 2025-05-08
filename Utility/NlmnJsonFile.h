#ifndef NLMN_JSON_FILE_H
#define NLMN_JSON_FILE_H

#include <fstream>
#include <iostream>
#include <iomanip>
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

    nlohmann::json& operator()()
    {
        return json_;
    }

    const nlohmann::json& operator()() const
    {
        return json_;
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
    m.sort();
    std::cout << m << std::endl;
    std::cout << m()["key3"]["key31"][2] << std::endl;
}

#endif
