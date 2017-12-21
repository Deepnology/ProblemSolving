#ifndef TOWER_OF_HANOI_H
#define TOWER_OF_HANOI_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <array>
#include "Debug.h"
/*
Cracking the coding interview 3.4
Elements of programming interview, Recursion: The Towers of Hanoi problem

The number of moves, T(n), satisfies the following recurrence:
T(n) = T(n-1) + 1 + T(n-1), which solves to T(n) = 2^n - 1.
One way to see this is to "unwrap" the recurrence k time:
T(n) = 2^l T(n-k) + 2^(k-1) + 2^(k-2) + ... + 2 + 1.
Printing a single move takes O(1) time, implying an O(2^n) time complexity.
*/
class TowerOfHanoi
{
	std::stack<int> m_disks;
	int m_index;
public:
	TowerOfHanoi(int i) : m_disks(), m_index(i)
	{}
	~TowerOfHanoi(){}
	int Index() const
	{
		return m_index;
	}
	void Add(int d)
	{
		if (!m_disks.empty() && m_disks.top() <= d)
		{
			std::cout << "TowerOfHanoi Error placing disk " << d << std::endl;
			return;
		}
		else
			m_disks.push(d);
	}
	void MoveTopTo(TowerOfHanoi & t)
	{
		int top = m_disks.top();
		m_disks.pop();
		t.Add(top);
		std::cout << "TowerOfHanoi Move disk " << top << " from " << m_index << " to " << t.Index() << std::endl;
	}
	void MoveDisks(int n, TowerOfHanoi & destination, TowerOfHanoi & buffer)
	{
		if (n > 0)
		{
			this->MoveDisks(n - 1, buffer, destination);
			this->MoveTopTo(destination);
			buffer.MoveDisks(n - 1, destination, *this);
		}
	}
	void Print()
	{
		std::cout << "TowerOfHanoi " << m_index << ": " << Debug::ToStr1D<int>()(m_disks) << std::endl;
	}
};

class TowerOfHanoi2
{
public:
	TowerOfHanoi2(){}
	~TowerOfHanoi2(){}

	void Transfer(int n)
	{
		std::cout << "TowerOfHanoi2 Transfer for \"" << n << "\" disks:" << std::endl;
		std::vector<std::stack<int> > pegs(3, std::stack<int>());
		for (int i = n; i >= 1; --i)
			pegs[0].push(i);
		Debug::Print2D<int>()(pegs, false);
		this->transferRecur(n, pegs, 0, 1, 2);
		Debug::Print2D<int>()(pegs, false);
	}

private:
	void transferRecur(int n, std::vector<std::stack<int> > & pegs, int from, int to, int use)
	{
		if (n > 0)
		{
			this->transferRecur(n - 1, pegs, from, use, to);

			pegs[to].push(pegs[from].top());
			pegs[from].pop();

			std::cout << "TowerOfHanoi2 transfer: disk \"" << pegs[to].top() << "\" from peg \"" << from << "\" to peg \"" << to << "\"" << std::endl;
			Debug::Print2D<int>()(pegs, false);

			this->transferRecur(n - 1, pegs, use, to, from);
		}
	}

	
};
/*
TowerOfHanoi Move disk 0 from 0 to 2
TowerOfHanoi Move disk 1 from 0 to 1
TowerOfHanoi Move disk 0 from 2 to 1
TowerOfHanoi Move disk 2 from 0 to 2
TowerOfHanoi Move disk 0 from 1 to 0
TowerOfHanoi Move disk 1 from 1 to 2
TowerOfHanoi Move disk 0 from 0 to 2
TowerOfHanoi Move disk 3 from 0 to 1
TowerOfHanoi Move disk 0 from 2 to 1
TowerOfHanoi Move disk 1 from 2 to 0
TowerOfHanoi Move disk 0 from 1 to 0
TowerOfHanoi Move disk 2 from 2 to 1
TowerOfHanoi Move disk 0 from 0 to 2
TowerOfHanoi Move disk 1 from 0 to 1
TowerOfHanoi Move disk 0 from 2 to 1
TowerOfHanoi Move disk 4 from 0 to 2
TowerOfHanoi Move disk 0 from 1 to 0
TowerOfHanoi Move disk 1 from 1 to 2
TowerOfHanoi Move disk 0 from 0 to 2
TowerOfHanoi Move disk 2 from 1 to 0
TowerOfHanoi Move disk 0 from 2 to 1
TowerOfHanoi Move disk 1 from 2 to 0
TowerOfHanoi Move disk 0 from 1 to 0
TowerOfHanoi Move disk 3 from 1 to 2
TowerOfHanoi Move disk 0 from 0 to 2
TowerOfHanoi Move disk 1 from 0 to 1
TowerOfHanoi Move disk 0 from 2 to 1
TowerOfHanoi Move disk 2 from 0 to 2
TowerOfHanoi Move disk 0 from 1 to 0
TowerOfHanoi Move disk 1 from 1 to 2
TowerOfHanoi Move disk 0 from 0 to 2
TowerOfHanoi 0:
TowerOfHanoi 1:
TowerOfHanoi 2: 4, 3, 2, 1, 0


TowerOfHanoi2 Transfer for "5" disks:
[rY][cX]
Row#0	= 5, 4, 3, 2, 1
Row#1	=  ,  ,  ,  ,
Row#2	=  ,  ,  ,  ,

TowerOfHanoi2 transfer: disk "1" from peg "0" to peg "1"
[rY][cX]
Row#0	= 5, 4, 3, 2
Row#1	= 1,  ,  ,
Row#2	=  ,  ,  ,

TowerOfHanoi2 transfer: disk "2" from peg "0" to peg "2"
[rY][cX]
Row#0	= 5, 4, 3
Row#1	= 1,  ,
Row#2	= 2,  ,

TowerOfHanoi2 transfer: disk "1" from peg "1" to peg "2"
[rY][cX]
Row#0	= 5, 4, 3
Row#1	=  ,  ,
Row#2	= 2, 1,

TowerOfHanoi2 transfer: disk "3" from peg "0" to peg "1"
[rY][cX]
Row#0	= 5, 4
Row#1	= 3,
Row#2	= 2, 1

TowerOfHanoi2 transfer: disk "1" from peg "2" to peg "0"
[rY][cX]
Row#0	= 5, 4, 1
Row#1	= 3,  ,
Row#2	= 2,  ,

TowerOfHanoi2 transfer: disk "2" from peg "2" to peg "1"
[rY][cX]
Row#0	= 5, 4, 1
Row#1	= 3, 2,
Row#2	=  ,  ,

TowerOfHanoi2 transfer: disk "1" from peg "0" to peg "1"
[rY][cX]
Row#0	= 5, 4,
Row#1	= 3, 2, 1
Row#2	=  ,  ,

TowerOfHanoi2 transfer: disk "4" from peg "0" to peg "2"
[rY][cX]
Row#0	= 5,  ,
Row#1	= 3, 2, 1
Row#2	= 4,  ,

TowerOfHanoi2 transfer: disk "1" from peg "1" to peg "2"
[rY][cX]
Row#0	= 5,
Row#1	= 3, 2
Row#2	= 4, 1

TowerOfHanoi2 transfer: disk "2" from peg "1" to peg "0"
[rY][cX]
Row#0	= 5, 2
Row#1	= 3,
Row#2	= 4, 1

TowerOfHanoi2 transfer: disk "1" from peg "2" to peg "0"
[rY][cX]
Row#0	= 5, 2, 1
Row#1	= 3,  ,
Row#2	= 4,  ,

TowerOfHanoi2 transfer: disk "3" from peg "1" to peg "2"
[rY][cX]
Row#0	= 5, 2, 1
Row#1	=  ,  ,
Row#2	= 4, 3,

TowerOfHanoi2 transfer: disk "1" from peg "0" to peg "1"
[rY][cX]
Row#0	= 5, 2
Row#1	= 1,
Row#2	= 4, 3

TowerOfHanoi2 transfer: disk "2" from peg "0" to peg "2"
[rY][cX]
Row#0	= 5,  ,
Row#1	= 1,  ,
Row#2	= 4, 3, 2

TowerOfHanoi2 transfer: disk "1" from peg "1" to peg "2"
[rY][cX]
Row#0	= 5,  ,  ,
Row#1	=  ,  ,  ,
Row#2	= 4, 3, 2, 1

TowerOfHanoi2 transfer: disk "5" from peg "0" to peg "1"
[rY][cX]
Row#0	=  ,  ,  ,
Row#1	= 5,  ,  ,
Row#2	= 4, 3, 2, 1

TowerOfHanoi2 transfer: disk "1" from peg "2" to peg "0"
[rY][cX]
Row#0	= 1,  ,
Row#1	= 5,  ,
Row#2	= 4, 3, 2

TowerOfHanoi2 transfer: disk "2" from peg "2" to peg "1"
[rY][cX]
Row#0	= 1,
Row#1	= 5, 2
Row#2	= 4, 3

TowerOfHanoi2 transfer: disk "1" from peg "0" to peg "1"
[rY][cX]
Row#0	=  ,  ,
Row#1	= 5, 2, 1
Row#2	= 4, 3,

TowerOfHanoi2 transfer: disk "3" from peg "2" to peg "0"
[rY][cX]
Row#0	= 3,  ,
Row#1	= 5, 2, 1
Row#2	= 4,  ,

TowerOfHanoi2 transfer: disk "1" from peg "1" to peg "2"
[rY][cX]
Row#0	= 3,
Row#1	= 5, 2
Row#2	= 4, 1

TowerOfHanoi2 transfer: disk "2" from peg "1" to peg "0"
[rY][cX]
Row#0	= 3, 2
Row#1	= 5,
Row#2	= 4, 1

TowerOfHanoi2 transfer: disk "1" from peg "2" to peg "0"
[rY][cX]
Row#0	= 3, 2, 1
Row#1	= 5,  ,
Row#2	= 4,  ,

TowerOfHanoi2 transfer: disk "4" from peg "2" to peg "1"
[rY][cX]
Row#0	= 3, 2, 1
Row#1	= 5, 4,
Row#2	=  ,  ,

TowerOfHanoi2 transfer: disk "1" from peg "0" to peg "1"
[rY][cX]
Row#0	= 3, 2,
Row#1	= 5, 4, 1
Row#2	=  ,  ,

TowerOfHanoi2 transfer: disk "2" from peg "0" to peg "2"
[rY][cX]
Row#0	= 3,  ,
Row#1	= 5, 4, 1
Row#2	= 2,  ,

TowerOfHanoi2 transfer: disk "1" from peg "1" to peg "2"
[rY][cX]
Row#0	= 3,
Row#1	= 5, 4
Row#2	= 2, 1

TowerOfHanoi2 transfer: disk "3" from peg "0" to peg "1"
[rY][cX]
Row#0	=  ,  ,
Row#1	= 5, 4, 3
Row#2	= 2, 1,

TowerOfHanoi2 transfer: disk "1" from peg "2" to peg "0"
[rY][cX]
Row#0	= 1,  ,
Row#1	= 5, 4, 3
Row#2	= 2,  ,

TowerOfHanoi2 transfer: disk "2" from peg "2" to peg "1"
[rY][cX]
Row#0	= 1,  ,  ,
Row#1	= 5, 4, 3, 2
Row#2	=  ,  ,  ,

TowerOfHanoi2 transfer: disk "1" from peg "0" to peg "1"
[rY][cX]
Row#0	=  ,  ,  ,  ,
Row#1	= 5, 4, 3, 2, 1
Row#2	=  ,  ,  ,  ,

[rY][cX]
Row#0	=  ,  ,  ,  ,
Row#1	= 5, 4, 3, 2, 1
Row#2	=  ,  ,  ,  ,

*/
#endif