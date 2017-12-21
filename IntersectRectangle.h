#ifndef INTERSECT_RECTANGLE_H
#define INTERSECT_RECTANGLE_H
#include <vector>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: Rectangle Area
Find the total area covered by two rectilinear rectangles in a 2D plane. (the union area of the 2 rectangles)
Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
Assume that the total area is never beyond the maximum possible value of int.
                           Y
                           ^
                           |               (C,D):(3,4)
            +----+----+----+----+----+----+
            |              |              |
            +              +              +
            |              |              |                              (G,H):(9,2)
            +              +----+----+----+----+----+----+----+----+----+
            |              |              |                             |
            +              +              +                             +
            |              |              |                             |
------------+----+----+----+----+----+----+----+----+----+----+----+----+----> X
(A,B):(-3,0)               |                                            |
                           +----+----+----+----+----+----+----+----+----+
						   (E,F):(0,-1)

http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
Elements of programming interview, PrimitiveTypes: Check if rectangles intersect

For the case of using the coordinate where origin (0,0) is at the bottom left corner:

I. The conditions for two rectangles intersect are:
1. horizontal: R1.left <= R2.right && R2.left <= R1.right
              _________
             |         |
R1.left      |      R1.right
   |      R2.left               R2.right
   |_______________________________|

2. vertical: R1.bottom <= R2.top && R2.bottom <= R1.top

II. The intersection area for two rectangles if overlapped:
(BottomLeft.x, BottomLeft.y) = (max(BottomLeft1.x,BottomLeft2.x), max(BottomLeft1.y, BottomLeft2.y))
(TopRight.x, TopRight.y) = (min(TopRight1.x,TopRight2.x), min(TopRight1.y, TopRight2.y))

O(1) time
*/
class IntersectRectangle
{
public:
	IntersectRectangle(){}
	~IntersectRectangle(){}

	/*
	coordinate: origin (0,0) is at the bottom left corner
	(A,B): bottom left corner of rectangle1
	(C,D): top right corner of rectangle1
	(E,F): bottom left corner of rectangle2
	(G,H): top right corner of rectangle2
	*/
	int UnionArea(int A, int B, int C, int D, int E, int F, int G, int H)
	{
		bool isIntersect = (A <= G && E <= C && B <= H && F <= D);

		int x1 = std::max(A, E);//bottom left x
		int y1 = std::max(B, F);//bottom left y
		int x2 = std::min(C, G);//top right x
		int y2 = std::min(D, H);//top right y

		int res = (D - B) * (C - A) + (H - F) * (G - E) - (isIntersect ? (y2 - y1) * (x2 - x1) : 0);

		std::cout << "IntersectRectangle UnionArea for \"" << A << "," << B << "," << C << "," << D << "," << E << "," << F << "," << G << "," << H << "\": " << res << std::endl;
		return res;
	}


	/*
	coordinate: [colX,rowY], where origin (0,0) is at the top left corner
	(x1, y1): top left corner of rectangle1
	(x2, y2): top left corner of rectangle2
	*/
	bool IsIntersect(int x1, int y1, int w1, int h1
		, int x2, int y2, int w2, int h2)
	{
		return x1 <= x2 + w2 && //the outer two points
			x2 <= x1 + w1 && //the inner two points
			y1 <= y2 + h2 && //the outer two points
			y2 <= y1 + h1; //the inner two points
	}

	void Find(int x1, int y1, int w1, int h1
		, int x2, int y2, int w2, int h2)
	{
		std::cout << "IntersectRectangle for \"[" << x1 << "," << y1 << "], width=" << w1 << ", height=" << h1 << "\" and \"[" << x2 << "," << y2 << "], width=" << w2 << ", height=" << h2 << "\": ";
		if (this->IsIntersect(x1, y1, w1, h1, x2, y2, w2, h2))
		{
			int x = std::max(x1, x2);
			int y = std::max(y1, y2);
			int w = std::min(x1 + w1, x2 + w2) - x;
			int h = std::min(y1 + h1, y2 + h2) - y;
			std::cout << "[" << x << "," << y << "], width=" << w << ", height=" << h << "." << std::endl;
		}
		else
		{
			std::cout << "No Intersection." << std::endl;
		}
	}
};
/*
IntersectRectangle UnionArea for "-3,0,3,4,0,-1,9,2": 45
IntersectRectangle for "[1,4], width=8, height=16" and "[5,1], width=16, height=8": [5,4], width=4, height=5.
*/
#endif