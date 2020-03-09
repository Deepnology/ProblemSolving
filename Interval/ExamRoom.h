#ifndef _EXAM_ROOM_H
#define _EXAM_ROOM_H
/*
Leetcode: Exam Room
In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.
When a student enters the room, they must sit in the seat that maximizes the distance to the closest person.
If there are multiple such seats, they sit in the seat with the lowest number.
(Also, if no one is in the room, then the student sits at seat number 0.)
Return a class ExamRoom(int N) that exposes two functions:
ExamRoom.seat() returning an int representing what seat the student sat in, and
ExamRoom.leave(int p) representing that the student in seat number p now leaves the room.
It is guaranteed that any calls to ExamRoom.leave(p) have a student sitting in seat p.
Example 1:
Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
Output: [null,0,9,4,2,null,5]
Explanation:
ExamRoom(10) -> null
seat() -> 0, no one is in the room, then the student sits at seat number 0.
seat() -> 9, the student sits at the last seat number 9.
seat() -> 4, the student sits at the last seat number 4.
seat() -> 2, the student sits at the last seat number 2.
leave(4) -> null
seat() -> 5, the student​​​​​​​ sits at the last seat number 5.
 */
class ExamRoom
{
    struct Itvl
    {
        int left;
        int right;
        int mid;//left of mid pair for even
        int dist;//distance between (left,mid), exclusive boundaries
        Itvl(int l, int r, int N): left(l), right(r)
        {
            if (left == INT_MIN && right == INT_MAX)//first idx
            {
                mid = 0;
                dist = 0;
            }
            else if (left == INT_MIN)
            {
                mid = 0;
                dist = right - mid;
            }
            else if (right == INT_MAX)
            {
                mid = N-1;
                dist = mid - left;
            }
            else
            {
                mid = (left + right) / 2;
                //dist = std::min(mid-left, right-mid);
                dist = mid - left;
            }
        }
    };
    struct ItvlComp
    {
        bool operator()(const Itvl & a, const Itvl & b) const
        {
            return (a.dist != b.dist) ? a.dist > b.dist : (a.mid != b.mid) ? a.mid < b.mid : (a.left != b.left) ? a.left < b.left : a.right < b.right;
        }
    };
    int N;
    std::set<Itvl, ItvlComp> sorted;//<Itvl>
    std::unordered_map<int, std::pair<std::set<Itvl,ItvlComp>::iterator,std::set<Itvl,ItvlComp>::iterator>> idxMap;//<idx,<leftItvlItr,rightItvlItr>>
public:
    ExamRoom(int N_) : N(N_), sorted(), idxMap()
    {
        sorted.insert(Itvl(INT_MIN, INT_MAX, N));
        std::cout << "ExamRoom: " << N << " [" << GetSortedSeats() << "]" << std::endl;
    }

    int seat()
    {
        int left = sorted.begin()->left;//Itvl with max dist
        int right = sorted.begin()->right;
        int mid = sorted.begin()->mid;
        sorted.erase(sorted.begin());
        auto itr1 = sorted.insert(Itvl(left, mid, N)).first;
        auto itr2 = sorted.insert(Itvl(mid, right, N)).first;
        idxMap[mid] = {itr1,itr2};
        idxMap[left].second = itr1;
        idxMap[right].first = itr2;
        std::cout << "seat: " << mid << " [" << GetSortedSeats() << "]" << std::endl;
        return mid;
    }

    void leave(int p)
    {
        int left = idxMap[p].first->left;//leftItvlItr->left
        int right = idxMap[p].second->right;//rightItvlItr->right
        sorted.erase(idxMap[p].first);//leftItvlItr
        sorted.erase(idxMap[p].second);//rightItvlItr
        idxMap.erase(p);
        auto itr = sorted.insert(Itvl(left, right, N)).first;
        idxMap[left].second = itr;
        idxMap[right].first = itr;
        std::cout << "leave: " << p << " [" << GetSortedSeats() << "]" << std::endl;
    }

private:
    std::string GetSortedSeats()
    {
        std::set<int> s;
        for (auto & p : idxMap)
            s.insert(p.first);
        return Debug::ToStr1D<int>()(s);
    }
};
/*
ExamRoom: 10 []
seat: 0 [-2147483648, 0, 2147483647]
seat: 9 [-2147483648, 0, 9, 2147483647]
seat: 4 [-2147483648, 0, 4, 9, 2147483647]
seat: 2 [-2147483648, 0, 2, 4, 9, 2147483647]
leave: 4 [-2147483648, 0, 2, 9, 2147483647]
seat: 5 [-2147483648, 0, 2, 5, 9, 2147483647]
 */
#endif
