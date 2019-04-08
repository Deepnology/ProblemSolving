#ifndef _TIME_BASED_KEY_VAL_STORE_H
#define _TIME_BASED_KEY_VAL_STORE_H
#include "Debug.h"
/*
Leetcode: Time Based Key-value Store
Create a timebased key-value store class TimeMap, that supports two operations.
1. set(string key, string value, int timestamp)
Stores the key and value, along with the given timestamp.
2. get(string key, int timestamp)
Returns a value such that set(key, value, timestamp_prev) was called previously, with timestamp_prev <= timestamp.
If there are multiple such values, it returns the one with the largest timestamp_prev.
If there are no values, it returns the empty string ("").
Example 1:
Input: inputs = ["TimeMap","set","get","get","set","get","get"], inputs = [[],["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]]
Output: [null,null,"bar","bar",null,"bar2","bar2"]
Explanation:
TimeMap kv;
kv.set("foo", "bar", 1); // store the key "foo" and value "bar" along with timestamp = 1
kv.get("foo", 1);  // output "bar"
kv.get("foo", 3); // output "bar" since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 ie "bar"
kv.set("foo", "bar2", 4);
kv.get("foo", 4); // output "bar2"
kv.get("foo", 5); //output "bar2"
Example 2:
Input: inputs = ["TimeMap","set","set","get","get","get","get","get"], inputs = [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]
Output: [null,null,null,"","high","high","low","low"]
 */
class TimeBasedKeyValStore
{
    //we can use Trie
    std::unordered_map<std::string,std::map<int,std::string>> keyTimeVal;//<key<Time,Val>>
    //where Time is sorted in incr order
public:
    TimeBasedKeyValStore(){}
    ~TimeBasedKeyValStore(){}

    void Set(std::string key, std::string value, int timestamp)
    {
        keyTimeVal[key][timestamp] = value;

        std::cout << "Set [" << key << "," << timestamp << "," << value << "]" << std::endl;
        Print(keyTimeVal);
    }
    std::string Get(std::string key, int timestamp)
    {
        auto itr = keyTimeVal.find(key);
        if (itr == keyTimeVal.end()) return "";
        auto itr2 = itr->second.upper_bound(timestamp);
        if (itr2 == itr->second.begin()) return "";

        std::cout << "Get [" << key << "," << timestamp << "]: " << std::prev(itr2)->second << std::endl;
        Print(keyTimeVal);

        return std::prev(itr2)->second;
    }

    void Print(const std::unordered_map<std::string,std::map<int,std::string>> & m)
    {
        std::ostringstream oss;
        int count = 0;
        for (typename std::unordered_map<std::string, std::map<int,std::string>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
        {
            oss << "Row#" << count++ << "	= " << i->first << ": ";
            int M = i->second.size();
            int cnt = 0;
            for (typename std::map<int,std::string>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
            {
                oss << "[" << j->first << "," << j->second << "]";
                if (++cnt != M)
                    oss << ", ";
            }
            oss << std::endl;
        }
        std::cout << oss.str() << std::endl;
    }
};
/*
Set [foo,1,bar]
Row#0	= foo: [1,bar]

Get [foo,1]: bar
Row#0	= foo: [1,bar]

Get [foo,3]: bar
Row#0	= foo: [1,bar]

Set [foo,4,bar2]
Row#0	= foo: [1,bar], [4,bar2]

Get [foo,4]: bar2
Row#0	= foo: [1,bar], [4,bar2]

Get [foo,5]: bar2
Row#0	= foo: [1,bar], [4,bar2]
 */
#endif
