#ifndef _CONSISTENT_HASHING_H
#define _CONSISTENT_HASHING_H
#include "Debug.h"
/*
http://www.acodersjourney.com/2017/10/system-design-interview-consistent-hashing/
http://www.tom-e-white.com/2007/11/consistent-hashing.html
https://www.codeproject.com/Articles/56138/Consistent-hashing
*/
class ConsistentHashing //use <string, int> for simplicity
{
    struct ListNode
    {
        std::string key;
        int val;
        ListNode * next;
        ListNode(const std::string & key_, int val_) : key(key_), val(val_), next(NULL) {}
    };
    size_t m_sizeNodes; //number of dummy nodes, where dummy nodes have indices in [0:m_size-1]
    std::map<size_t, ListNode *> m_sortedHashRing; //sorted hash ring
    const size_t m_numReplicas; //number of virtual hash nodes for each dummy node
    const std::hash<std::string> m_strHashFunc;

    size_t m_sizeKeys; //number of keys
    double m_loadFactor;

    std::map<std::string, int> m_testingMap;
public:
    ConsistentHashing(size_t sizeNodes, size_t numReplicas) : m_sizeNodes(0), m_numReplicas(numReplicas), m_sizeKeys(0), m_loadFactor(0.75f)
    {
        for (size_t i = 0; i < sizeNodes; ++i)
            AddDummyNode(i);
    }
    ~ConsistentHashing()
    {
        for (size_t i = 0; i < m_sizeNodes; ++i)
            RemoveDummyNode(i);
    }
    std::vector<std::pair<std::string, int>> AddDummyNode(size_t nodeIdx)
    {
        std::vector<std::pair<std::string, int>> res;
        ListNode * dummy = new ListNode("dummy", 0);
        for (size_t i = 0; i < m_numReplicas; ++i) //add m_numReplicas virtual nodes
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
        for (size_t i = 0; i < m_numReplicas; ++i) //add m_numReplicas virtual nodes
        {
            size_t curHash = m_strHashFunc(std::to_string(nodeIdx) + "," + std::to_string(i));
            std::pair<std::map<size_t, ListNode *>::iterator, bool> curItr
                    = m_sortedHashRing.insert({curHash, dummy}); //all virtual nodes point to a same dummy node
        }
        ++m_sizeNodes;
        return res; //return <key, val> that need to re-hashing
    }
    std::vector<std::pair<std::string, int>> RemoveDummyNode(size_t nodeIdx)
    {
        std::vector<std::pair<std::string, int>> res;
        for (size_t i = 0; i < m_numReplicas; ++i)
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
        return res; //return <key, val> that need to re-hashing
    }
    void ResizeDummyNode(size_t n)
    {
        if (n == m_sizeNodes) return;
        std::vector<std::pair<std::string, int>> res;
        if (n > m_sizeNodes)
        {
            for (int i = m_sizeNodes; i < n; ++i)
            {
                std::vector<std::pair<std::string, int>> keyVal = AddDummyNode(i);
                res.insert(res.end(), keyVal.begin(), keyVal.end());
            }
        }
        else //n < m_size
        {
            for (int i = m_sizeNodes - 1; i >= n; --i)
            {
                std::vector<std::pair<std::string, int>> keyVal = RemoveDummyNode(i);
                res.insert(res.end(), keyVal.begin(), keyVal.end());
            }
        }
        //std::cout << Debug::ToStr1D<std::string, int>()(res) << std::endl;
        for (auto & p : res)
            put(p.first, p.second);//re-hashing <key, val>
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
/*
[a:1,1], [b:2,2], [c:3,3], [d:4,4], [e:5,5], [f:6,6],

Row#0:
Row#1:
Row#2: [a,1]
Row#3:
Row#4: [f,6], [e,5]
Row#5:
Row#6: [b,2]
Row#7: [d,4]
Row#8:
Row#9: [c,3]
Row#10:
Row#11:

[a:11,11], [b:22,22], [c:33,33], [d:4,4], [e:5,5], [f:6,6],

Row#0:
Row#1:
Row#2: [a,11]
Row#3:
Row#4: [f,6], [e,5]
Row#5:
Row#6: [b,22]
Row#7:
Row#8:
Row#9:
Row#10:
Row#11:
Row#12:
Row#13:
Row#14:
Row#15:
Row#16: [c,33]
Row#17: [d,4]
Row#18:
Row#19:
Row#20:
Row#21:
Row#22:
Row#23:

[b:22,22], [d:4,4], [e:5,5],

Row#0:
Row#1:
Row#2:
Row#3:
Row#4: [e,5]
Row#5:
Row#6: [b,22]
Row#7:
Row#8:
Row#9:
Row#10:
Row#11:
Row#12:
Row#13:
Row#14:
Row#15:
Row#16:
Row#17: [d,4]
Row#18:
Row#19:
Row#20:
Row#21:
Row#22:
Row#23:

[b:22,22], [d:4,4], [e:5,5],

Row#0:
Row#1:
Row#2:
Row#3: [b,22], [d,4]
Row#4: [e,5]
Row#5:

[b:22,22], [d:4,4], [e:5,5], [u:21,21], [v:22,22], [w:23,23], [x:24,24], [y:25,25], [z:26,26],

Row#0:
Row#1:
Row#2:
Row#3:
Row#4: [z,26], [e,5]
Row#5:
Row#6: [b,22]
Row#7:
Row#8:
Row#9:
Row#10:
Row#11:
Row#12: [u,21], [y,25]
Row#13:
Row#14:
Row#15:
Row#16:
Row#17: [d,4]
Row#18:
Row#19:
Row#20:
Row#21: [v,22]
Row#22:
Row#23:
Row#24:
Row#25:
Row#26:
Row#27:
Row#28:
Row#29:
Row#30:
Row#31:
Row#32:
Row#33:
Row#34:
Row#35:
Row#36: [w,23]
Row#37:
Row#38:
Row#39:
Row#40: [x,24]
Row#41:
Row#42:
Row#43:
Row#44:
Row#45:
Row#46:
Row#47:

[b:22,22], [d:4,4], [e:5,5], [u:21,21], [v:22,22], [w:23,23], [x:24,24], [y:25,25], [z:26,26],

Row#0: [e,5], [b,22], [y,25], [v,22], [x,24]
Row#1: [z,26], [u,21], [d,4], [w,23]

[b:22,22], [d:4,4], [e:5,5], [u:21,21], [v:22,22], [w:23,23], [x:24,24], [y:25,25], [z:26,26],

Row#0: [y,25], [v,22]
Row#1: [w,23]
Row#2: [x,24], [e,5], [z,26], [u,21]
Row#3: [d,4], [b,22]

[b:22,22], [d:4,4], [e:5,5], [u:21,21], [v:22,22], [w:23,23], [x:24,24], [y:25,25], [z:26,26],

Row#0: [w,23], [u,21], [z,26], [e,5], [x,24], [b,22], [d,4], [y,25], [v,22]

[b:22,22], [d:4,4], [e:5,5], [i:9,9], [j:10,10], [k:11,11], [u:21,21], [v:22,22], [w:23,23],

Row#0: [v,22]
Row#1: [w,23], [i,9]
Row#2:
Row#3: [d,4]
Row#4: [e,5]
Row#5: [k,11]
Row#6: [b,22], [u,21], [j,10]

[b:22,22], [d:4,4], [e:5,5], [i:99,99], [j:100,100], [k:111,111], [m:13,13], [n:14,14], [o:15,15], [u:21,21], [v:22,22], [w:23,23],

Row#0:
Row#1:
Row#2:
Row#3:
Row#4: [e,5]
Row#5:
Row#6:
Row#7:
Row#8:
Row#9: [n,14]
Row#10: [k,111]
Row#11:
Row#12: [u,21]
Row#13:
Row#14:
Row#15:
Row#16:
Row#17: [d,4]
Row#18:
Row#19:
Row#20:
Row#21:
Row#22:
Row#23:
Row#24:
Row#25:
Row#26:
Row#27:
Row#28:
Row#29:
Row#30:
Row#31:
Row#32:
Row#33:
Row#34:
Row#35:
Row#36: [w,23]
Row#37:
Row#38:
Row#39:
Row#40:
Row#41:
Row#42:
Row#43:
Row#44:
Row#45:
Row#46:
Row#47:
Row#48:
Row#49:
Row#50:
Row#51: [i,99]
Row#52:
Row#53: [j,100]
Row#54:
Row#55:
Row#56:
Row#57:
Row#58:
Row#59:
Row#60: [m,13]
Row#61:
Row#62:
Row#63:
Row#64:
Row#65: [b,22]
Row#66:
Row#67:
Row#68:
Row#69:
Row#70:
Row#71:
Row#72:
Row#73: [o,15]
Row#74:
Row#75:
Row#76:
Row#77:
Row#78:
Row#79:
Row#80:
Row#81:
Row#82: [v,22]
Row#83:
Row#84:
Row#85:
Row#86:
Row#87:
Row#88:
Row#89:
Row#90:
Row#91:
Row#92:
Row#93:
Row#94:
Row#95:
Row#96:
Row#97:
Row#98:
Row#99:
Row#100:
Row#101:
Row#102:
Row#103:
Row#104:
Row#105:
Row#106:
Row#107:
Row#108:
Row#109:
Row#110:
Row#111:

[b:22,22], [d:4,4], [e:5,5], [i:99,99], [j:100,100], [k:111,111], [m:13,13], [n:14,14], [o:15,15], [u:21,21], [v:22,22], [w:23,23],

Row#0: [v,22]
Row#1: [w,23], [i,99]
Row#2:
Row#3:
Row#4: [e,5]
Row#5:
Row#6: [u,21], [m,13], [b,22], [o,15]
Row#7: [k,111], [d,4]
Row#8:
Row#9: [j,100], [n,14]

 */
#endif
