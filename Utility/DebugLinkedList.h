#ifndef DEBUG_LINKED_LIST_H
#define DEBUG_LINKED_LIST_H

#ifdef __cplusplus
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <type_traits>

class DebugLinkedList
{

    enum class TraversalOrder { DFS, BFS };
    template<typename ValueType, TraversalOrder Order = TraversalOrder::DFS>
    class TraverseOrderContainer
    {
    private:
        using container_type = std::conditional_t<
            Order == TraversalOrder::DFS,
            std::stack<ValueType>,
            std::queue<ValueType>
        >;
        container_type m_container;
    public:
        TraverseOrderContainer() = default;
        bool empty() const { return m_container.empty(); }
        void push(const ValueType& val) { m_container.push(val); }
        void push(ValueType&& val) { m_container.push(std::move(val)); }
        ValueType& cur()
        {
            if constexpr (Order == TraversalOrder::DFS)
                return m_container.top();
            else
                return m_container.front();
        }
        const ValueType& cur() const
        {
            if constexpr (Order == TraversalOrder::DFS)
                return m_container.top();
            else
                return m_container.front();
        }
        void pop() { m_container.pop(); }
        size_t size() const { return m_container.size(); }
        constexpr TraversalOrder getOrder() const noexcept { return Order; }
    };


public:
    struct NoComparator {};
    template <typename NodeType, typename ReturnType, typename Comparator = NoComparator>
    static ReturnType TraverseT(
        NodeType* node,
        const std::vector<std::function<NodeType* (NodeType*)>>& getNextArr,
        std::function<ReturnType(NodeType*, int)> invokeNode,
        std::function<void(const ReturnType&, ReturnType&)> visitCur,
        std::function<std::vector<void*>(NodeType*)> getChdListArr,
        const std::vector<std::function<std::function<ReturnType(void*, int)>(NodeType*)>>& invokeChdListArr,
        std::function<void(const ReturnType&, ReturnType&)> visitCurChd,
        int level = 0)
    {
        ReturnType res;
        if (!node) return res;
        std::priority_queue<NodeType*, std::vector<NodeType*>, Comparator> heap;//used only when Comparator != NoComparator
        TraverseOrderContainer<NodeType*> container;//DFS by default
        std::unordered_set<NodeType*> visit;
        NodeType* cur = node;
        container.push(cur);
        visit.insert(cur);

        auto visitCurFunc = [&]() 
            {
                visitCur(invokeNode(cur, level), res);
                std::vector<void*> chdListArr = getChdListArr(cur);
                for (int i = 0; i < chdListArr.size(); ++i)
                {
                    if (void* chdList = chdListArr[i])
                    {
                        if (i < invokeChdListArr.size() && invokeChdListArr[i])
                        {
                            if (std::function<ReturnType(void*, int)> selInvokeF = invokeChdListArr[i](cur))
                                visitCurChd(selInvokeF(chdList, level + 1), res);
                        }
                    }
                }
            };
        while (!container.empty())
        {
            cur = container.cur();
            container.pop();

            //visit cur
            if constexpr (std::is_same_v<Comparator, NoComparator>)
            {
                visitCurFunc();
            }
            else
            {
                heap.push(cur);
            }

            //push nxt
            std::vector<std::function<NodeType* (NodeType*)>> getNextArrCopy = getNextArr;
            if (container.getOrder() == TraversalOrder::DFS)//DFS
                std::reverse(getNextArrCopy.begin(), getNextArrCopy.end());
            for (int i = 0; i < getNextArrCopy.size(); ++i)
            {
                if (std::function<NodeType* (NodeType*)> getNextF = getNextArrCopy[i])
                {
                    if (NodeType* nxt = getNextF(cur); nxt && !visit.count(nxt))
                    {
                        visit.insert(nxt);
                        container.push(nxt);
                    }
                }
            }
        }

        if constexpr (!std::is_same_v<Comparator, NoComparator>)
        {
            while (!heap.empty())
            {
                cur = heap.top();
                heap.pop();

                //visit cur
                visitCurFunc();
            }
        }
        return res;
    }

    template <typename NodeType>
    static std::string GetPrintT(
        NodeType* node,
        const std::vector<std::function<NodeType* (NodeType*)>>& getNextArr,
        std::function<std::string(NodeType*, int)> printNode,
        std::function<std::vector<void*>(NodeType*)> getChdListArr,
        const std::vector<std::function<std::function<std::string(void*, int)>(NodeType*)>>& printChdListArr,
        int level = 0)
    {
        return TraverseT<NodeType, std::string>(
            node,
            getNextArr,
            printNode,
            [](const std::string& curRes, std::string& res)
            {
                res += curRes;
                res += "\n";
            },
            getChdListArr,
            printChdListArr,
            [](const std::string& curRes, std::string& res)
            {
                res += curRes;
            },
            level);
    }


    template <typename NodeType>
    static std::string GetPrintT1(
        NodeType* node,
        const std::vector<std::function<NodeType* (NodeType*)>>& getNextArr,
        std::function<std::string(NodeType*, int)> printNode,
        std::function<std::vector<void*>(NodeType*)> getChdListArr,
        const std::vector<std::function<std::function<std::string(void*, int)>(NodeType*)>>& printChdListFuncArr,
        int level = 0)
    {
        std::ostringstream oss;
        if (!node) return oss.str();
        TraverseOrderContainer<NodeType*> container;//DFS by default
        std::unordered_set<NodeType*> visit;
        NodeType* cur = node;
        container.push(cur);
        visit.insert(cur);
        while (!container.empty())
        {
            cur = container.cur();
            container.pop();

            //visit cur
            oss << printNode(cur, level) << std::endl;
            auto chdListArr = getChdListArr(cur);
            int count = chdListArr.size();
            for (int i = 0; i < count; ++i)
            {
                if (void* chd = chdListArr[i])
                {
                    if (i < printChdListFuncArr.size() && printChdListFuncArr[i])
                    {
                        if (auto selPrintF = printChdListFuncArr[i](cur))
                            oss << selPrintF(chd, level + 1);
                    }
                }
            }

            auto getNextArrCopy = getNextArr;
            if (container.order() == 0)//DFS
                std::reverse(getNextArrCopy.begin(), getNextArrCopy.end());
            for (int i = 0; i < getNextArrCopy.size(); ++i)
            {
                NodeType* nxt = getNextArrCopy[i](cur);
                if (nxt && !visit.count(nxt))
                {
                    visit.insert(nxt);
                    container.push(nxt);
                }
            }
        }
        return oss.str();
    }
};

namespace DebugLinkedListTest
{
    struct T1
    {
        std::string t1Name;
        int t1ValInt;
        T1* t1Next;
    };

    struct T2
    {
        std::string t2Name;
        double t2ValDouble;
        int t2ValInt;
        T2* myT2Next;
        T1* myT1Data;
    };

    struct T3
    {
        std::string t3Name;
        double t3ValDouble;
        long t3ValLong;
        T3* myT3Next;
        T2* t2Data;
        T1* t1Data;
        T3* myT3Down;
    };

    inline void Test()
    {
        T1 t1_1{ "t1_1", 135, nullptr };
        T1 t1_2{ "t1_2", 2352, nullptr };
        T1 t1_3{ "t1_3", 3345, nullptr };
        T1 t1_4{ "t1_4", 424, nullptr };

        t1_1.t1Next = &t1_2;
        t1_2.t1Next = &t1_3;
        t1_3.t1Next = &t1_4;

        T1 t1_5{ "t1_5", 135, nullptr };
        T1 t1_6{ "t1_6", 2352, nullptr };

        t1_5.t1Next = &t1_6;

        T2 t2_1{ "t2_1", 99.00, 999, nullptr, &t1_1 };
        T2 t2_2{ "t2_2", 765.00, 4336, nullptr, &t1_5 };

        t2_1.myT2Next = &t2_2;

        T1 t1_11{ "t1_11", 135, nullptr };
        T1 t1_12{ "t1_12", 2352, nullptr };
        T1 t1_13{ "t1_13", 3345, nullptr };
        T1 t1_14{ "t1_14", 424, nullptr };

        t1_11.t1Next = &t1_12;
        t1_12.t1Next = &t1_13;
        t1_13.t1Next = &t1_14;

        T1 t1_15{ "t1_15", 135, nullptr };
        T1 t1_16{ "t1_16", 2352, nullptr };

        t1_15.t1Next = &t1_16;

        T1 t1_17{ "t1_17", 2352, nullptr };

        T2 t2_3{ "t2_3", 99.00, 999, nullptr, &t1_11 };
        T2 t2_4{ "t2_4", 765.00, 4336, nullptr, &t1_15 };
        T2 t2_5{ "t2_5", 99.00, 999, nullptr, &t1_17 };

        t2_3.myT2Next = &t2_4;
        t2_4.myT2Next = &t2_5;

        T1 t1_21{ "t1_21", 135, nullptr };
        T1 t1_22{ "t1_22", 2352, nullptr };
        T1 t1_23{ "t1_23", 3345, nullptr };
        T1 t1_24{ "t1_24", 424, nullptr };

        t1_21.t1Next = &t1_22;
        t1_22.t1Next = &t1_23;
        t1_23.t1Next = &t1_24;

        T1 t1_25{ "t1_25", 135, nullptr };
        T1 t1_26{ "t1_26", 2352, nullptr };

        t1_25.t1Next = &t1_26;

        T3 t3_1{ "t3_1", 1.234, 12345, nullptr, &t2_1, &t1_21, nullptr };
        T3 t3_2{ "t3_2", 1.234, 12345, nullptr, &t2_3, &t1_25, nullptr };

        t3_1.myT3Next = &t3_2;

        T3 t3_3{ "t3_3", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_4{ "t3_4", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_5{ "t3_5", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_6{ "t3_6", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_7{ "t3_7", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_8{ "t3_8", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_9{ "t3_9", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_10{ "t3_10", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_11{ "t3_11", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_12{ "t3_12", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };
        T3 t3_13{ "t3_13", 1.234, 12345, nullptr, nullptr, nullptr, nullptr };

        t3_3.myT3Next = &t3_4;
        t3_3.myT3Down = &t3_7;
        t3_4.myT3Next = &t3_5;
        t3_4.myT3Down = &t3_1;
        t3_5.myT3Next = &t3_6;
        //t3_6.myT3Down = &t3_2;
        t3_7.myT3Next = &t3_8;
        t3_7.myT3Down = &t3_13;
        t3_8.myT3Next = &t3_9;
        t3_9.myT3Down = &t3_10;
        //t3_2.myT3Next = &t3_6;
        //t3_2.myT3Down = &t3_12;
        t3_1.myT3Down = &t3_11;
        t3_11.myT3Next = &t3_12;
        //t3_12.myT3Next = &t3_10;
        //t3_10.myT3Next = &t3_12;

        /*
        3 - 4 - 5 - 6
        |   |       |
        |   1 - 2 ---
        |   |   |
        |   11- 12---
        |           |
        7 - 8 - 9   |
        |       |   |
        13      10 -|
        */

        std::function<std::string(void*, int)> printT1List = [&](void* node, int level)
            {
                return DebugLinkedList::GetPrintT<T1>(static_cast<T1*>(node),
                    { [](T1* n) { return n->t1Next; } },
                    [](T1* n, int level) { std::string s; while (level-- > 0) s += "    ";  return s + "\"" + n->t1Name + "\", " + std::to_string(n->t1ValInt); },
                    [](T1* n) { return std::vector<void*>{ }; },
                    { },
                    level);
            };
        auto printT2List = [&](void* node, int level)
            {
                return DebugLinkedList::GetPrintT<T2>(static_cast<T2*>(node),
                    { [](T2* n) { return n->myT2Next; } },
                    [](T2* n, int level) { std::string s; while (level-- > 0) s += "    "; return s + "\"" + n->t2Name + "\", " + std::to_string(n->t2ValDouble) + ", " + std::to_string(n->t2ValInt); },
                    [](T2* n) { return std::vector<void*>{ static_cast<void*>(n->myT1Data) }; },
                    { [&](T2* n){ return printT1List; } },
                    level);
            };
        auto printT3List = [&](void* node, int level)
            {
                return DebugLinkedList::GetPrintT<T3>(static_cast<T3*>(node),
                    std::vector<std::function<T3 * (T3*)>>({ [](T3* n) { return n->myT3Next; }, [](T3* n) { return n->myT3Down; } }),
                    [](T3* n, int level) { std::string s; while (level-- > 0) s += "    "; return s + "\"" + n->t3Name + "\", " + std::to_string(n->t3ValDouble) + ", " + std::to_string(n->t3ValLong); },
                    [](T3* n) { return std::vector<void*>{ static_cast<void*>(n->t2Data), static_cast<void*>(n->t1Data) }; },
                    { [&](T3* n) { return printT2List; } , [&](T3* n) { return printT1List; } },
                    level);
            };

        std::cout << printT3List(&t3_3, 0);

    }
}

#endif

#endif

