#ifndef DESIGN_SHARED_BIKE_H
#define DESIGN_SHARED_BIKE_H
#include "Debug.h"
#include "KdTree.h"
/*
Design Uber
http://www.1point3acres.com/bbs/thread-273331-1-1.html
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=290195&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
http://www.geeksforgeeks.org/k-dimensional-tree-set-3-delete/
*/
namespace DesignSharedBike
{
	class Rider
	{
	public:
	};
	class Bike
	{
	public:
	};
	class CentralDispatch
	{
		std::unordered_map<Bike*, Rider*> m_bikeToRider;//for bikes that are used
		std::unordered_map<Bike*, std::string> m_bikeToXY;//for bikes that are parked
		std::unordered_map<Rider*, Bike*> m_riderToBike;//used bikes
		std::unordered_map<std::string, std::unordered_set<Bike*>> m_XYtoBikes;//parked bikes
		KdTree m_bikes;//parked bikes w/ 2D location info (parked bikes might have duplicated locations)
		int m_bikeCount;
	public:
		explicit CentralDispatch(int bCount): m_bikeToRider(), m_bikeToXY(), m_riderToBike(), m_XYtoBikes(), m_bikes(2), m_bikeCount(bCount) 
		{
			for (int i = 0; i < m_bikeCount; ++i)
			{
				Bike * b = new Bike;
				m_bikes.Insert({ 0,0 });
				m_XYtoBikes[std::string("0,0")].insert(b);
				m_bikeToXY[b] = std::string("0,0");
			}
		}

		std::pair<Bike*, std::vector<int>> Dispatch(Rider * r, std::vector<int> & location)
		{
			if (r == NULL || m_bikeToXY.empty() || m_riderToBike.count(r))
				return{ NULL,{0,0} };
			std::vector<int> nearest = m_bikes.FindNearest(location);
			Bike * bike = *m_XYtoBikes[ToStr(nearest)].begin();
			m_XYtoBikes[ToStr(nearest)].erase(bike);
			if (m_XYtoBikes[ToStr(nearest)].empty())
				m_XYtoBikes.erase(ToStr(nearest));
			m_bikes.Remove(nearest);
			m_bikeToXY.erase(bike);

			m_bikeToRider[bike] = r;
			m_riderToBike[r] = bike;
			return{ bike, nearest };
		}
		void Park(Rider * r, Bike * b, std::vector<int> & location)
		{
			if (r == NULL || b == NULL)
				return;
			m_bikeToRider.erase(b);
			m_riderToBike.erase(r);

			m_bikes.Insert(location);
			m_bikeToXY[b] = ToStr(location);
			m_XYtoBikes[ToStr(location)].insert(b);
		}

	private:
		std::string ToStr(const std::vector<int> & location)
		{
			return std::to_string(location[0]) + "," + std::to_string(location[1]);
		}
		std::vector<int> ToVec(const std::string & location)
		{
			int N = location.size();
			int begin = 0;
			int i = 0;
			std::vector<int> res;
			while (i < N)
			{
				if (location[i] == ',')
				{
					res.push_back(stoi(location.substr(begin, i - begin)));
					begin = i + 1;
				}
				else if (i == N - 1)
					res.push_back(stoi(location.substr(begin, i - begin + 1)));
				++i;
			}
			return res;
		}
	};
}

#endif
