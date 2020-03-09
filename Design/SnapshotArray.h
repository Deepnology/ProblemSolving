#ifndef _SNAPSHOT_ARRAY_H
#define _SNAPSHOT_ARRAY_H
#include "Debug.h"
/*
Leetcode: Snapshot Array
Implement a SnapshotArray that supports the following interface:
SnapshotArray(int length) initializes an array-like data structure with the given length.  Initially, each element equals 0.
void set(index, val) sets the element at the given index to be equal to val.
int snap() takes a snapshot of the array and returns the snap_id: the total number of times we called snap() minus 1.
int get(index, snap_id) returns the value at the given index, at the time we took the snapshot with the given snap_id
Example 1:
Input: ["SnapshotArray","set","snap","set","get"]
[[3],[0,5],[],[0,6],[0,0]]
Output: [null,null,0,null,5]
Explanation:
SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
snapshotArr.set(0,5);  // Set array[0] = 5
snapshotArr.snap();  // Take a snapshot, return snap_id = 0
snapshotArr.set(0,6);
snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5
 */
class SnapshotArray
{
    std::vector<std::map<int,int>> v;//<map<snapId,val>>
    int snapIdx;
public:
    SnapshotArray(int length)
    {
        v.resize(length, {{0,0}});
        snapIdx = 0;
    }

    void set(int index, int val)
    {
        v[index][snapIdx] = val;
    }

    int snap()
    {
        return snapIdx++;
    }

    int get(int index, int snap_id)
    {
        auto itr = v[index].lower_bound(snap_id);
        if (itr == v[index].end() || itr->first != snap_id)
            return std::prev(itr)->second;
        else//itr->first==snap_id
            return itr->second;
    }
};
#endif
