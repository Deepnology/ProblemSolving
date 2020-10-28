#ifndef _CONSISTENT_HASHING_H
#define _CONSISTENT_HASHING_H
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
/*
http://www.acodersjourney.com/2017/10/system-design-interview-consistent-hashing/
http://www.tom-e-white.com/2007/11/consistent-hashing.html
https://www.codeproject.com/Articles/56138/Consistent-hashing

Implement a simple hash map template class that supports uniform distribution (load balance), efficient resizing buckets and rehashing (consistent hashing).
*/
template<class K, class V, class H = std::hash<K>> //<Key, Val, HashFunc>
class ConsistentHashing
{
    size_t m_sizeNodes;
    std::map<size_t, std::list<std::pair<K, V>>*> m_sortedHashRing;
    const size_t m_sizeReplicas;
    const std::hash<std::string> m_hash;
    const H m_keyHash;
    size_t m_sizeKeys;
    double m_loadFactor;

    std::unordered_map<K, V, H> m_testingMap;
public:
    ConsistentHashing(size_t sizeNodes = 10, size_t sizeReplicas = 10, double loadFactor = 0.75f) :
            m_sizeNodes(0), m_sortedHashRing(), m_sizeReplicas(sizeReplicas), m_hash(), m_keyHash(), m_sizeKeys(0), m_loadFactor(0.75f)
    {
        for (size_t i = 0; i < sizeNodes; ++i)
            AddNode(i);
    }
    ~ConsistentHashing()
    {
        for (size_t i = 0; i < m_sizeNodes; ++i)
            RemoveNode(i);
    }
private:
    std::vector<std::pair<K, V>> AddNode(size_t nodeIdx)
    {
        std::vector<std::pair<K, V>> res;
        std::list<std::pair<K, V>> * bucket = new std::list<std::pair<K, V>>();
        for (size_t i = 0; i < m_sizeReplicas; ++i) //add m_sizeReplicas virtual nodes
        {
            size_t curHash = m_hash(std::to_string(nodeIdx) + "," + std::to_string(i)); //need a separator to avoid duplicated composite number which causes same hash
            std::pair<typename std::map<size_t, std::list<std::pair<K, V>> *>::iterator, bool> curItr
                    = m_sortedHashRing.insert({curHash, bucket}); //all virtual nodes point to a same bucket
            auto nxtItr = m_sortedHashRing.upper_bound(curHash); //delete and return all the keys that need to be re-hashed
            if (nxtItr == m_sortedHashRing.end())
                nxtItr = m_sortedHashRing.begin();
            std::list<std::pair<K, V>> * nxtBucket = nxtItr->second;
            for (auto itr = nxtBucket->begin(); itr != nxtBucket->end(); )
            {
                size_t nxtHash = m_keyHash(itr->first);
                if (m_sortedHashRing.lower_bound(nxtHash) == curItr.first //1. nxtHash hits the current node
                    || m_sortedHashRing.lower_bound(nxtHash) == m_sortedHashRing.end()) //2. curHash is m_sortedHashRing.begin()
                {
                    res.push_back({itr->first, itr->second});
                    itr = nxtBucket->erase(itr);
                }
                else
                    ++itr;
            }
            m_sortedHashRing.erase(curItr.first); //erase curHash to make sure later upperBound(curHash) won't hit a newly added hash
        }
        for (size_t i = 0; i < m_sizeReplicas; ++i) //add m_sizeReplicas virtual nodes
        {
            size_t curHash = m_hash(std::to_string(nodeIdx) + "," + std::to_string(i)); //need a separator to avoid duplicated composite number which causes same hash
            std::pair<typename std::map<size_t, std::list<std::pair<K, V>> *>::iterator, bool> curItr
                    = m_sortedHashRing.insert({curHash, bucket}); //all virtual nodes point to a same bucket
        }
        ++m_sizeNodes;
        return res; //return <key, val> pairs that need to be re-hashed
    }
    std::vector<std::pair<K, V>> RemoveNode(size_t nodeIdx)
    {
        std::vector<std::pair<K, V>> res;
        for (size_t i = 0; i < m_sizeReplicas; ++i)
        {
            size_t curHash = m_hash(std::to_string(nodeIdx) + "," + std::to_string(i));
            auto curItr = m_sortedHashRing.lower_bound(curHash);
            if (curItr != m_sortedHashRing.end() && curItr->first == curHash)
            {
                if (i == 0) //remove all nodes for once
                {
                    std::list<std::pair<K, V>> * bucket = curItr->second;
                    for (auto itr = bucket->begin(); itr != bucket->end(); )
                    {
                        res.push_back({itr->first, itr->second});
                        itr = bucket->erase(itr);
                    }
                    delete bucket; bucket = NULL;
                }
                m_sortedHashRing.erase(curItr);
            }
            else
                std::cout << "Warning: not found virtual node [nodeIdx,replicaIdx,hash]: [" << nodeIdx << "," << i << "," << curHash << "]" << std::endl;
        }
        --m_sizeNodes;
        return res; //return <key, val> pairs that need to be re-hashed
    }
public:
    void ResizeNode(size_t n)
    {
        if (n == m_sizeNodes) return;
        std::vector<std::pair<K, V>> res;
        if (n > m_sizeNodes)
        {
            for (size_t i = m_sizeNodes; i < n; ++i)
            {
                std::vector<std::pair<K, V>> keyVal = AddNode(i);
                res.insert(res.end(), keyVal.begin(), keyVal.end());
            }
        }
        else //n < m_size
        {
            for (size_t i = m_sizeNodes - 1; i >= n; --i)
            {
                std::vector<std::pair<K, V>> keyVal = RemoveNode(i);
                res.insert(res.end(), keyVal.begin(), keyVal.end());
            }
        }
        for (auto & p : res)
            put(p.first, p.second);//re-hash <key, val> pairs
    }

    bool Put(const K & key, const V & val)
    {
        if (m_sizeNodes == 0)
            ResizeNode(2);
        else if (((double)(m_sizeKeys + 1)/(double)m_sizeNodes) > m_loadFactor)
            ResizeNode(m_sizeNodes*2);
        return put(key, val);
    }
private:
    bool put(const K & key, const V & val)
    {
        m_testingMap[key] = val;

        size_t curHash = m_keyHash(key);
        auto curItr = m_sortedHashRing.lower_bound(curHash);
        if (curItr == m_sortedHashRing.end())
            curItr = m_sortedHashRing.begin();
        curHash = curItr->first;
        std::list<std::pair<K, V>> * bucket = curItr->second;
        for (auto itr = bucket->begin(); itr != bucket->end(); ++itr)
        {
            if (itr->first == key)
            {
                itr->second = val;
                return false;
            }
        }
        bucket->push_front({key, val});
        ++m_sizeKeys;
        return true;
    }
public:
    std::pair<V, bool> Get(const K & key) const
    {
        if (m_sizeNodes == 0)
            return {V(), false};
        size_t curHash = m_keyHash(key);
        auto curItr = m_sortedHashRing.lower_bound(curHash);
        if (curItr == m_sortedHashRing.end())
            curItr = m_sortedHashRing.begin();
        std::list<std::pair<K, V>> * bucket = curItr->second;
        for (auto itr = bucket->begin(); itr != bucket->end(); ++itr)
        {
            if (itr->first == key)
                return {itr->second, true};
        }
        return {V(), false};
    }
    void Remove(const K & key)
    {
        m_testingMap.erase(key);

        if (m_sizeNodes == 0)
            return;
        size_t curHash = m_keyHash(key);
        auto curItr = m_sortedHashRing.lower_bound(curHash);
        if (curItr == m_sortedHashRing.end())
            curItr = m_sortedHashRing.begin();
        std::list<std::pair<K, V>> * bucket = curItr->second;
        for (auto itr = bucket->begin(); itr != bucket->end(); )
        {
            if (itr->first == key)
            {
                itr = bucket->erase(itr);
                --m_sizeKeys;
            }
            else
                ++itr;
        }
    }

    void SetLoadFactor(double f)
    {
        if (f > 0 && f <= 1.0f) m_loadFactor = f;
    }
    double GetLoadFactor() const
    {
        return m_loadFactor;
    }
    size_t GetNodeSize() const
    {
        return m_sizeNodes;
    }
    size_t GetKeySize() const
    {
        return m_sizeKeys;
    }

    void Print()
    {
        std::ostringstream oss;
        for (auto & p : m_testingMap)
        {
            oss << "{" << p.first << ":" << p.second << ",";
            auto res = Get(p.first);
            if (res.second)
                oss << res.first;
            else
                oss << "NotFound(" << m_keyHash(p.first) << ")";
            oss << "}, ";
        }
        oss << std::endl << std::endl;
        for (int i = 0; i < m_sizeNodes; ++i)
        {
            oss << "Row#" << i << ": ";
            size_t curHash = m_hash(std::to_string(i) + ",0");
            std::list<std::pair<K, V>> * bucket = m_sortedHashRing[curHash];
            for (auto itr = bucket->begin(); itr != bucket->end(); ++itr)
            {
                oss << "{" << itr->first << "," << itr->second << "}";
                if (std::next(itr) != bucket->end()) oss << ", ";
            }
            oss << std::endl;
        }
        std::cout << oss.str() << std::endl;
    }
};

class SimpleConsistentHashing //use <string, int> for simplicity
{
    struct ListNode
    {
        std::string key;
        int val;
        ListNode * next;
        ListNode(const std::string & key_, int val_) : key(key_), val(val_), next(NULL) {}
    };
    size_t m_sizeNodes; //number of dummy nodes (buckets), where dummy nodes have indices in [0:m_sizeNodes-1]
    std::map<size_t, ListNode *> m_sortedHashRing; //sorted hash ring
    const size_t m_sizeReplicas; //number of virtual hash nodes for each dummy node
    const std::hash<std::string> m_strHashFunc;

    size_t m_sizeKeys; //number of keys
    double m_loadFactor;

    std::unordered_map<std::string, int, std::hash<std::string>> m_testingMap;
public:
    SimpleConsistentHashing(size_t sizeNodes, size_t sizeReplicas) : m_sizeNodes(0), m_sizeReplicas(sizeReplicas), m_sizeKeys(0), m_loadFactor(0.75f)
    {
        for (size_t i = 0; i < sizeNodes; ++i)
            AddDummyNode(i);
    }
    ~SimpleConsistentHashing()
    {
        for (size_t i = 0; i < m_sizeNodes; ++i)
            RemoveDummyNode(i);
    }
    std::vector<std::pair<std::string, int>> AddDummyNode(size_t nodeIdx)
    {
        std::vector<std::pair<std::string, int>> res;
        ListNode * dummy = new ListNode("dummy", 0);
        for (size_t i = 0; i < m_sizeReplicas; ++i) //add m_sizeReplicas virtual nodes
        {
            size_t curHash = m_strHashFunc(std::to_string(nodeIdx) + "," + std::to_string(i)); //need a separator to avoid duplicated composite number which causes same hash
            std::pair<std::map<size_t, ListNode *>::iterator, bool> curItr
                    = m_sortedHashRing.insert({curHash, dummy}); //all virtual nodes point to a same dummy node
            auto nxtItr = m_sortedHashRing.upper_bound(curHash); //delete and return all the keys that need to be re-hashed
            if (nxtItr == m_sortedHashRing.end())
                nxtItr = m_sortedHashRing.begin();
            ListNode * nxtDummy = nxtItr->second;
            if (nxtDummy)
            {
                //remove non-front nodes whose keys are matched
                ListNode * cur = nxtDummy;
                while (cur && cur->next)
                {
                    size_t nxtHash = m_strHashFunc(cur->next->key);
                    if (m_sortedHashRing.lower_bound(nxtHash) == curItr.first //1.
                        || m_sortedHashRing.lower_bound(nxtHash) == m_sortedHashRing.end()) //2. curHash is m_sortedHashRing.begin()
                    {
                        res.push_back({cur->next->key, cur->next->val});
                        ListNode * del = cur->next;
                        cur->next = cur->next->next;
                        delete del;
                        del = NULL;
                    }
                    else
                        cur = cur->next;
                }
            }
            m_sortedHashRing.erase(curItr.first); //erase curHash to make sure later upperBound(curHash) won't hit a newly added hash
        }
        for (size_t i = 0; i < m_sizeReplicas; ++i) //add m_sizeReplicas virtual nodes
        {
            size_t curHash = m_strHashFunc(std::to_string(nodeIdx) + "," + std::to_string(i));
            std::pair<std::map<size_t, ListNode *>::iterator, bool> curItr
                    = m_sortedHashRing.insert({curHash, dummy}); //all virtual nodes point to a same dummy node
        }
        ++m_sizeNodes;
        return res; //return <key, val> pairs that need to re-hashing
    }
    std::vector<std::pair<std::string, int>> RemoveDummyNode(size_t nodeIdx)
    {
        std::vector<std::pair<std::string, int>> res;
        for (size_t i = 0; i < m_sizeReplicas; ++i)
        {
            size_t curHash = m_strHashFunc(std::to_string(nodeIdx) + "," + std::to_string(i));
            auto itr = m_sortedHashRing.lower_bound(curHash);
            if (itr != m_sortedHashRing.end() && itr->first == curHash)
            {
                if (i == 0) //remove all nodes for once
                {
                    //remove non-front nodes whose keys are matched
                    ListNode * dummy = itr->second;
                    ListNode * cur = dummy;
                    while (cur && cur->next)
                    {
                        res.push_back({cur->next->key, cur->next->val});
                        ListNode * del = cur->next;
                        cur->next = cur->next->next;
                        delete del;
                        del = NULL;
                    }
                    delete dummy;
                    dummy = NULL;
                }
                m_sortedHashRing.erase(itr);
            }
            else
                std::cout << "Warning: not found virtual node [nodeIdx,replicaIdx,hash]: [" << nodeIdx << "," << i << "," << curHash << "]" << std::endl;
        }
        --m_sizeNodes;
        return res; //return <key, val> pairs that need to re-hashing
    }
    void ResizeDummyNode(size_t n)
    {
        if (n == m_sizeNodes) return;
        std::vector<std::pair<std::string, int>> res;
        if (n > m_sizeNodes)
        {
            for (size_t i = m_sizeNodes; i < n; ++i)
            {
                std::vector<std::pair<std::string, int>> keyVal = AddDummyNode(i);
                res.insert(res.end(), keyVal.begin(), keyVal.end());
            }
        }
        else //n < m_size
        {
            for (size_t i = m_sizeNodes - 1; i >= n; --i)
            {
                std::vector<std::pair<std::string, int>> keyVal = RemoveDummyNode(i);
                res.insert(res.end(), keyVal.begin(), keyVal.end());
            }
        }
        //std::cout << Debug::ToStr1D<std::string, int>()(res) << std::endl;
        for (auto & p : res)
            put(p.first, p.second);//re-hashing <key, val> pairs
    }


    bool Put(const std::string & key, int val)
    {
        if (m_sizeNodes == 0)
            ResizeDummyNode(2);
        else if (((double)(m_sizeKeys + 1)/(double)m_sizeNodes) > m_loadFactor)
            ResizeDummyNode(m_sizeNodes*2);

        return put(key, val);
    }
private:
    bool put(const std::string & key, int val)
    {
        m_testingMap[key] = val;

        size_t curHash = m_strHashFunc(key);
        auto itr = m_sortedHashRing.lower_bound(curHash);
        if (itr == m_sortedHashRing.end())
            itr = m_sortedHashRing.begin();
        curHash = itr->first;
        ListNode * dummy = itr->second;
        ListNode * cur = dummy->next;
        while (cur)
        {
            if (cur->key == key)
            {
                cur->val = val;
                return false;
            }
            cur = cur->next;
        }
        //now cur == NULL, add new node to beginning of bucket
        cur = new ListNode(key, val);
        cur->next = dummy->next;
        dummy->next = cur;
        ++m_sizeKeys;
        return true;
    }
public:
    std::pair<int, bool> Get(const std::string & key)
    {
        if (m_sizeNodes == 0)
            return {0, false};
        size_t curHash = m_strHashFunc(key);
        auto itr = m_sortedHashRing.lower_bound(curHash);
        if (itr == m_sortedHashRing.end())
            itr = m_sortedHashRing.begin();
        curHash = itr->first;
        ListNode * dummy = itr->second;
        ListNode * cur = dummy->next;
        while (cur)
        {
            if (cur->key == key)
                return {cur->val, true};
            cur = cur->next;
        }
        return {0, false};
    }
    void Remove(const std::string & key)
    {
        m_testingMap.erase(key);

        if (m_sizeNodes == 0)
            return;
        size_t curHash = m_strHashFunc(key);
        auto itr = m_sortedHashRing.lower_bound(curHash);
        if (itr == m_sortedHashRing.end())
            itr = m_sortedHashRing.begin();
        curHash = itr->first;
        ListNode * dummy = itr->second;
        //remove non-front nodes whose keys are equal
        ListNode * cur = dummy;
        while (cur && cur->next)
        {
            if (cur->next->key.compare(key) == 0)
            {
                ListNode * del = cur->next;
                cur->next = cur->next->next;
                delete del;
                --m_sizeKeys;
            }
            else
                cur = cur->next;
        }
    }

    void Print()
    {
        std::ostringstream oss;
        for (auto & p : m_testingMap)
        {
            oss << "[" << p.first << ":" << p.second << ",";
            auto res = Get(p.first);
            if (res.second)
                oss << res.first;
            else
                oss << "NotFound(" << m_strHashFunc(p.first) << ")";
            oss << "], ";
        }
        oss << std::endl << std::endl;
        for (int i = 0; i < m_sizeNodes; ++i)
        {
            oss << "Row#" << i << ": ";
            size_t curHash = m_strHashFunc(std::to_string(i) + ",0");
            ListNode * dummy = m_sortedHashRing[curHash];
            if (dummy)
            {
                ListNode * cur = dummy->next;
                while (cur)
                {
                    oss << "[" << cur->key << "," << cur->val << "]";
                    if (cur->next) oss << ", ";
                    cur = cur->next;
                }
            }
            oss << std::endl;
        }

        /*
        for (auto & p : m_sortedHashRing)
        {
            oss << p.first << ": ";
            ListNode * dummy = p.second;
            if (dummy)
            {
                ListNode * cur = dummy->next;
                while (cur)
                {
                    oss << "[" << cur->key << "," << cur->val << "]";
                    if (cur->next) oss << ", ";
                    cur = cur->next;
                }
            }
            oss << std::endl;
        }
        */

        std::cout << oss.str() << std::endl;
    }
};


void ConsistentHashingTest1()
{
    SimpleConsistentHashing ch(3, 16);
    ch.Put("a", 1);
    ch.Put("b", 2);
    ch.Put("c", 3);
    ch.Put("d", 4);
    ch.Put("e", 5);
    ch.Put("f", 6);
    ch.Print();
    ch.Put("a", 11);
    ch.Put("b", 22);
    ch.Put("c", 33);
    ch.Print();
    ch.Remove("f");
    ch.Remove("a");
    ch.Remove("c");
    ch.Print();
    ch.ResizeDummyNode(6);
    ch.Print();
    ch.Put("z", 26);
    ch.Put("y", 25);
    ch.Put("x", 24);
    ch.Put("w", 23);
    ch.Put("v", 22);
    ch.Put("u", 21);
    ch.Print();
    ch.ResizeDummyNode(2);
    ch.Print();
    ch.ResizeDummyNode(4);
    ch.Print();
    ch.ResizeDummyNode(1);
    ch.Print();
    ch.Remove("x");
    ch.Remove("y");
    ch.Remove("z");
    ch.Put("i", 9);
    ch.Put("j", 10);
    ch.Put("k", 11);
    ch.ResizeDummyNode(7);
    ch.Print();
    ch.Put("i", 99);
    ch.Put("j", 100);
    ch.Put("k", 111);
    ch.Put("m", 13);
    ch.Put("n", 14);
    ch.Put("o", 15);
    ch.Print();
    ch.ResizeDummyNode(10);
    ch.Print();
}
void ConsistentHashingTest2()
{
    ConsistentHashing<std::string, int, std::hash<std::string>> ch(3, 16);
    ch.Put("a", 1);
    ch.Put("b", 2);
    ch.Put("c", 3);
    ch.Put("d", 4);
    ch.Put("e", 5);
    ch.Put("f", 6);
    ch.Print();
    ch.Put("a", 11);
    ch.Put("b", 22);
    ch.Put("c", 33);
    ch.Print();
    ch.Remove("f");
    ch.Remove("a");
    ch.Remove("c");
    ch.Print();
    ch.ResizeNode(6);
    ch.Print();
    ch.Put("z", 26);
    ch.Put("y", 25);
    ch.Put("x", 24);
    ch.Put("w", 23);
    ch.Put("v", 22);
    ch.Put("u", 21);
    ch.Print();
    ch.ResizeNode(2);
    ch.Print();
    ch.ResizeNode(4);
    ch.Print();
    ch.ResizeNode(1);
    ch.Print();
    ch.Remove("x");
    ch.Remove("y");
    ch.Remove("z");
    ch.Put("i", 9);
    ch.Put("j", 10);
    ch.Put("k", 11);
    ch.ResizeNode(7);
    ch.Print();
    ch.Put("i", 99);
    ch.Put("j", 100);
    ch.Put("k", 111);
    ch.Put("m", 13);
    ch.Put("n", 14);
    ch.Put("o", 15);
    ch.Print();
    ch.ResizeNode(10);
    ch.Print();
}
void ConsistentHashingTest3()
{
    ConsistentHashing<int, std::string, std::hash<int>> ch(3, 16);
    ch.Put(1, "a");
    ch.Put(2, "b");
    ch.Put(3, "c");
    ch.Put(4, "d");
    ch.Put(5, "e");
    ch.Put(6, "f");
    ch.Print();
    ch.Put(11, "a");
    ch.Put(12, "b");
    ch.Put(13, "c");
    ch.Print();
    ch.Remove(6);
    ch.Remove(1);
    ch.Remove(3);
    ch.Print();
    ch.ResizeNode(6);
    ch.Print();
    ch.Put(26, "z");
    ch.Put(25, "y");
    ch.Put(24, "x");
    ch.Put(23, "w");
    ch.Put(22, "v");
    ch.Put(21, "u");
    ch.Print();
    ch.ResizeNode(2);
    ch.Print();
    ch.ResizeNode(4);
    ch.Print();
    ch.ResizeNode(1);
    ch.Print();
    ch.Remove(24);
    ch.Remove(25);
    ch.Remove(26);
    ch.Put(9, "i");
    ch.Put(10, "j");
    ch.Put(11, "k");
    ch.ResizeNode(7);
    ch.Print();
    ch.Put(99, "i");
    ch.Put(100, "j");
    ch.Put(111, "k");
    ch.Put(13, "m");
    ch.Put(14, "n");
    ch.Put(15, "o");
    ch.Print();
    ch.ResizeNode(10);
    ch.Print();
}

struct myKey
{
    std::string a;
    int b;
    double c;
    myKey(const std::string &_a, int _b, double _c) : a(_a), b(_b), c(_c) {}
    myKey() : a(), b(0), c(0) {}
    bool operator==(const myKey & rhs) const
    {
        return a == rhs.a && b == rhs.b && c == rhs.c;
    }
};
struct myVal
{
    std::string a;
    int b;
    double c;
    myVal(const std::string &_a, int _b, double _c) : a(_a), b(_b), c(_c) {}
    myVal() : a(), b(0), c(0) {}
};
std::ostream & operator<<(std::ostream & os, const myKey & k)
{
    return os << "(" << k.a << "," << k.b << "," << k.c << ")";
}
std::ostream & operator<<(std::ostream & os, const myVal & v)
{
    return os << "[" << v.a << "," << v.b << "," << v.c << "]";
}
namespace std
{
    template<>
    struct std::hash<myKey>
    {
        size_t operator()(const myKey &k) const
        {
            size_t res = 17;
            res = res * 31 + std::hash<::std::string>()(k.a);
            res = res * 31 + std::hash<int>()(k.b);
            res = res * 31 + std::hash<double>()(k.c);
            return res;
        }
    };
}
void ConsistentHashingTest4()
{
    ConsistentHashing<myKey, myVal> ch(3, 16);
    ch.Put(myKey("a",1,1.0f), myVal("a",1,1.0f));
    ch.Put(myKey("b",2,2.0f), myVal("b",2,2.0f));
    ch.Put(myKey("c",3,3.0f), myVal("c",3,3.0f));
    ch.Put(myKey("d",4,4.0f), myVal("d",4,4.0f));
    ch.Put(myKey("e",5,5.0f), myVal("e",5,5.0f));
    ch.Put(myKey("f",6,6.0f), myVal("f",6,6.0f));
    ch.Print();
    ch.Put(myKey("a",1,1.0f), myVal("aa",11,11.0f));
    ch.Put(myKey("b",2,2.0f), myVal("bb",22,22.0f));
    ch.Put(myKey("c",3,3.0f), myVal("cc",33,33.0f));
    ch.Print();
    ch.Remove(myKey("f",6,6.0f));
    ch.Remove(myKey("a",1,1.0f));
    ch.Remove(myKey("c",3,3.0f));
    ch.Print();
    ch.ResizeNode(6);
    ch.Print();
    ch.Put(myKey("z",26,26.0f), myVal("z",26,26.0f));
    ch.Put(myKey("y",25,25.0f), myVal("y",25,25.0f));
    ch.Put(myKey("x",24,24.0f), myVal("x",24,24.0f));
    ch.Put(myKey("w",23,23.0f), myVal("w",23,23.0f));
    ch.Put(myKey("v",22,22.0f), myVal("v",22,22.0f));
    ch.Put(myKey("u",21,21.0f), myVal("u",21,21.0f));
    ch.Print();
    ch.ResizeNode(2);
    ch.Print();
    ch.ResizeNode(4);
    ch.Print();
    ch.ResizeNode(1);
    ch.Print();
    ch.Remove(myKey("x",24,24.0f));
    ch.Remove(myKey("y",25,25.0f));
    ch.Remove(myKey("z",26,26.0f));
    ch.Put(myKey("i",9,9.0f), myVal("i",9,9.0f));
    ch.Put(myKey("j",10,10.0f), myVal("j",10,10.0f));
    ch.Put(myKey("k",11,11.0f), myVal("k",11,11.0f));
    ch.Print();
    ch.ResizeNode(7);
    ch.Print();
    ch.Put(myKey("i",9,9.0f), myVal("ii",99,99.0f));
    ch.Put(myKey("j",10,10.0f), myVal("jj",100,100.0f));
    ch.Put(myKey("k",11,11.0f), myVal("kk",111,111.0f));
    ch.Put(myKey("m",13,13.0f), myVal("m",13,13.0f));
    ch.Put(myKey("n",14,14.0f), myVal("n",14,14.0f));
    ch.Put(myKey("o",15,15.0f), myVal("o",15,15.0f));
    ch.Print();
    ch.ResizeNode(10);
    ch.Print();
}
#endif
