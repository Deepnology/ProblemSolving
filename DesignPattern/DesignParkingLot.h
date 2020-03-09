#ifndef DESIGN_PARKING_LOT_OOP_H
#define DESIGN_PARKING_LOT_OOP_H
#include "Debug.h"
/*
Design a valet parking lot using OOP
http://www.geeksforgeeks.org/design-parking-lot-using-object-oriented-principles/
http://massivetechinterview.blogspot.com/2015/07/cc150v5-84-design-parking-lot.html
1) The parking lot has multiple levels. Each level has multiple rows of spots.
2) The parking lot can park motorcycles, cars, and buses.
3) The parking lot has motorcycle spots, compact spots, and large spots.
4) A motorcycle can park in any spot.
5) A car can park in either a single compact spot or a single large spot.
6) A bus can park in five large spots that are consecutive and within the same row.
   It cannot park in small spots.
*/
namespace DesignParkingLot
{
	class ParkingLot;//forward declaration for Vehicle::Park(ParkingLot*) and Vehicle::UnPark(ParkingLot*)
	enum VehicleType
	{
		MotocycleType = 0,
		CarType = 1,
		BusType = 2,
	};
	//define vehicle hierarchy
	class Vehicle
	{
	protected:
		ParkingLot * m_parkingLot;
	public:
		virtual VehicleType Type() = 0;
		bool Park(ParkingLot*);
		bool UnPark();
		virtual ~Vehicle() = 0;
	};
	class Motocycle : public Vehicle
	{
	public:
		VehicleType Type();
	};
	class Car : public Vehicle
	{
	public:
		VehicleType Type();
	};
	class Bus : public Vehicle
	{
	public:
		VehicleType Type();
	};
	struct Greater //composite idx [level,row,moto/compact/large,idx]
	{
		bool operator()(const std::vector<size_t> & a, const std::vector<size_t> & b)
		{
			return a[0] != b[0] ? a[0] > b[0] : a[1] != b[1] ? a[1] > b[1] : a[3] > b[3];
		}
	};
	struct Row
	{
		Row(int numMotoSpot, int numCompactSpot, int numLargeSpot):
			m_motoSpots(numMotoSpot, NULL), m_compactSpots(numCompactSpot, NULL), m_largeSpots(numLargeSpot, NULL)
		{ }
		std::vector<Vehicle*> m_motoSpots;
		std::vector<Vehicle*> m_compactSpots;
		std::vector<Vehicle*> m_largeSpots;
	};
	class ParkingLot
	{
		//bi-directional mapping: spot to vehicle and vehicle to spot !!
		//use composite idx for multi-level-row spots
		std::vector<std::vector<Row>> m_spots;
		std::unordered_map<Vehicle*, std::vector<size_t>> m_vehicleToSpot;//<Vehicle*,[level,row,size,idx]>
	public:
		ParkingLot(int numLevel, int numRow, int numMotoSpot, int numCompactSpot, int numLargeSpot)
		{
			m_spots.resize(numLevel, std::vector<Row>(numRow, Row(numMotoSpot, numCompactSpot, numLargeSpot)));
		}
		bool Park(Vehicle * v)
		{
			if (v == NULL) return false;
			if (m_vehicleToSpot.find(v) != m_vehicleToSpot.end()) return false;
			VehicleType vt = v->Type();
			if (vt == MotocycleType)
			{
				for (size_t i = 0; i < m_spots.size(); ++i)//level
					for (size_t j = 0; j < m_spots[i].size(); ++j)//row
					{
						//1. try motoSpots
						for (size_t k = 0; k < m_spots[i][j].m_motoSpots.size(); ++k)
							if (m_spots[i][j].m_motoSpots[k] == NULL)
							{
								m_spots[i][j].m_motoSpots[k] = v;
								m_vehicleToSpot[v] = { i,j,0,k };
								return true;
							}
						//2. try compactSpots
						for (size_t k = 0; k < m_spots[i][j].m_compactSpots.size(); ++k)
							if (m_spots[i][j].m_compactSpots[k] == NULL)
							{
								m_spots[i][j].m_compactSpots[k] = v;
								m_vehicleToSpot[v] = { i,j,1,k };
								return true;
							}
						//3. try largeSpots
						for (size_t k = 0; k < m_spots[i][j].m_largeSpots.size(); ++k)
							if (m_spots[i][j].m_largeSpots[k] != NULL && m_spots[i][j].m_largeSpots[k]->Type() == BusType)
								k += 4;
							else if (m_spots[i][j].m_largeSpots[k] == NULL)
							{
								m_spots[i][j].m_largeSpots[k] = v;
								m_vehicleToSpot[v] = { i,j,2,k };
								return true;
							}
					}
				//now found no spots
				return false;
			}
			else if (vt == CarType)
			{
				for (size_t i = 0; i < m_spots.size(); ++i)//level
					for (size_t j = 0; j < m_spots[i].size(); ++j)//row
					{
						//1. try compactSpots
						for (size_t k = 0; k < m_spots[i][j].m_compactSpots.size(); ++k)
							if (m_spots[i][j].m_compactSpots[k] == NULL)
							{
								m_spots[i][j].m_compactSpots[k] = v;
								m_vehicleToSpot[v] = { i,j,1,k };
								return true;
							}
						//2. try largeSpots
						for (size_t k = 0; k < m_spots[i][j].m_largeSpots.size(); ++k)
							if (m_spots[i][j].m_largeSpots[k] != NULL && m_spots[i][j].m_largeSpots[k]->Type() == BusType)
								k += 4;
							else if (m_spots[i][j].m_largeSpots[k] == NULL)
							{
								m_spots[i][j].m_largeSpots[k] = v;
								m_vehicleToSpot[v] = { i,j,2,k };
								return true;
							}
					}
				//now found no spots
				return false;
			}
			else//BusType
			{
				for (size_t i = 0; i < m_spots.size(); ++i)//level
					for (size_t j = 0; j < m_spots[i].size(); ++j)//row
					{
						//try largeSpots
						size_t emptyCount = 0;
						size_t begin;
						for (size_t k = 0; k < m_spots[i][j].m_largeSpots.size(); ++k)
							if (m_spots[i][j].m_largeSpots[k] != NULL && m_spots[i][j].m_largeSpots[k]->Type() == BusType)
							{
								k += 4;
								emptyCount = 0;
							}
							else if (m_spots[i][j].m_largeSpots[k] == NULL)
							{
								if (emptyCount == 0) begin = k;
								++emptyCount;
								if (emptyCount == 5)
								{
									m_spots[i][j].m_largeSpots[begin] = v;
									m_vehicleToSpot[v] = { i,j,2,begin };
									return true;
								}
							}
							else
								emptyCount = 0;
					}
				//now found no spots
				return false;
			}
		}
		bool UnPark(Vehicle * v)
		{
			if (v == NULL) return false;
			auto foundItr = m_vehicleToSpot.find(v);
			if (foundItr == m_vehicleToSpot.end()) return false;
			std::vector<size_t> idx = foundItr->second;
			switch (idx[2])
			{
			case 0://motoSpot
				m_spots[idx[0]][idx[1]].m_motoSpots[idx[3]] = NULL;
				break;
			case 1://compactSpot
				m_spots[idx[0]][idx[1]].m_compactSpots[idx[3]] = NULL;
				break;
			case 2://largeSpot
			{
				m_spots[idx[0]][idx[1]].m_largeSpots[idx[3]] = NULL;
				if (v->Type() == BusType)
				{
					for (size_t i = 0; i < 4; ++i)
					{
						++idx[3];
						m_spots[idx[0]][idx[1]].m_largeSpots[idx[3]] = NULL;
					}
				}
			}
				break;
			default:
				break;
			}
			m_vehicleToSpot.erase(foundItr);
			return true;
		}

		//now using minHeaps to fast lookup available parking spots
		//init these minHeaps w/ all empty spots in constructor
	private:
		std::priority_queue<std::vector<size_t>, std::vector<std::vector<size_t>>, Greater> m_motoSoptMinHeap;
		std::priority_queue<std::vector<size_t>, std::vector<std::vector<size_t>>, Greater> m_compactSoptMinHeap;
		std::priority_queue<std::vector<size_t>, std::vector<std::vector<size_t>>, Greater> m_largeSoptMinHeap;
	public:
		bool Park2(Vehicle * v)
		{
			if (v == NULL) return false;
			if (m_vehicleToSpot.find(v) != m_vehicleToSpot.end()) return false;
			VehicleType vt = v->Type();
			if (vt == MotocycleType)
			{
				if (!m_motoSoptMinHeap.empty())
				{
					std::vector<size_t> idx = m_motoSoptMinHeap.top();
					m_motoSoptMinHeap.pop();
					m_spots[idx[0]][idx[1]].m_motoSpots[idx[3]] = v;
					m_vehicleToSpot[v] = idx;
					return true;
				}
				else if (!m_compactSoptMinHeap.empty())
				{
					std::vector<size_t> idx = m_compactSoptMinHeap.top();
					m_compactSoptMinHeap.pop();
					m_spots[idx[0]][idx[1]].m_compactSpots[idx[3]] = v;
					m_vehicleToSpot[v] = idx;
					return true;
				}
				else if (!m_largeSoptMinHeap.empty())
				{
					std::vector<size_t> idx = m_largeSoptMinHeap.top();
					m_largeSoptMinHeap.pop();
					m_spots[idx[0]][idx[1]].m_largeSpots[idx[3]] = v;
					m_vehicleToSpot[v] = idx;
					return true;
				}
				else
					return false;
			}
			else if (vt == CarType)
			{
				if (!m_compactSoptMinHeap.empty())
				{
					std::vector<size_t> idx = m_compactSoptMinHeap.top();
					m_compactSoptMinHeap.pop();
					m_spots[idx[0]][idx[1]].m_compactSpots[idx[3]] = v;
					m_vehicleToSpot[v] = idx;
					return true;
				}
				else if (!m_largeSoptMinHeap.empty())
				{
					std::vector<size_t> idx = m_largeSoptMinHeap.top();
					m_largeSoptMinHeap.pop();
					m_spots[idx[0]][idx[1]].m_largeSpots[idx[3]] = v;
					m_vehicleToSpot[v] = idx;
					return true;
				}
				else
					return false;
			}
			else//BusType
			{
				size_t emptySpotCount = 0;
				std::vector<size_t> begin;
				while (!m_largeSoptMinHeap.empty())
				{
					if (emptySpotCount == 0)
					{
						begin = m_largeSoptMinHeap.top();
						m_largeSoptMinHeap.pop();
						++emptySpotCount;
						continue;
					}
					
					std::vector<size_t> idx = m_largeSoptMinHeap.top();
					m_largeSoptMinHeap.pop();
					if (idx[0] == begin[0] && idx[1] == begin[1] && idx[3] == begin[3] + emptySpotCount)
						++emptySpotCount;
					else
						emptySpotCount = 0;//reset

					if (emptySpotCount == 5)
					{
						m_spots[begin[0]][begin[1]].m_largeSpots[begin[3]] = v;
						m_vehicleToSpot[v] = begin;
						return true;
					}
				}
				return false;
			}
		}
		bool UnPark2(Vehicle * v)
		{
			if (v == NULL) return false;
			auto foundItr = m_vehicleToSpot.find(v);
			if (foundItr == m_vehicleToSpot.end()) return false;
			std::vector<size_t> idx = foundItr->second;
			switch (idx[2])
			{
			case 0://motoSpot
			{
				m_spots[idx[0]][idx[1]].m_motoSpots[idx[3]] = NULL;
				m_motoSoptMinHeap.push(idx);
			}
				break;
			case 1://compactSpot
			{
				m_spots[idx[0]][idx[1]].m_compactSpots[idx[3]] = NULL;
				m_compactSoptMinHeap.push(idx);
			}
				break;
			case 2://largeSpot
			{
				m_spots[idx[0]][idx[1]].m_largeSpots[idx[3]] = NULL;
				m_largeSoptMinHeap.push(idx);
				if (v->Type() == BusType)
				{
					for (size_t i = 0; i < 4; ++i)
					{
						++idx[3];
						m_spots[idx[0]][idx[1]].m_largeSpots[idx[3]] = NULL;
						m_largeSoptMinHeap.push(idx);
					}
				}
			}
				break;
			default:
				break;
			}
			m_vehicleToSpot.erase(foundItr);
			return true;
		}

		
		void Squeeze()
		{
			//1. move motocycles that occupy largeSpots to available motoSpots
			for (size_t i = 0; i < m_spots.size() && !m_motoSoptMinHeap.empty(); ++i)//level
				for (size_t j = 0; j < m_spots[i].size() && !m_motoSoptMinHeap.empty(); ++j)//row
				{
					//largeSpots
					for (size_t k = 0; k < m_spots[i][j].m_largeSpots.size() && !m_motoSoptMinHeap.empty(); ++k)
						if (m_spots[i][j].m_largeSpots[k] != NULL && m_spots[i][j].m_largeSpots[k]->Type() == MotocycleType)
						{
							Vehicle * moto = m_spots[i][j].m_largeSpots[k];
							m_spots[i][j].m_largeSpots[k] = NULL;
							auto idx = m_motoSoptMinHeap.top();
							m_motoSoptMinHeap.pop();
							m_spots[idx[0]][idx[1]].m_motoSpots[idx[3]] = moto;
							m_vehicleToSpot[moto] = idx;
							m_largeSoptMinHeap.push({ i,j,2,k });
						}
				}
			//2. move motocycles that occupy compactSpots to available motoSpots
			for (size_t i = 0; i < m_spots.size() && !m_motoSoptMinHeap.empty(); ++i)//level
				for (size_t j = 0; j < m_spots[i].size() && !m_motoSoptMinHeap.empty(); ++j)//row
				{
					//compactSpots
					for (size_t k = 0; k < m_spots[i][j].m_compactSpots.size() && !m_motoSoptMinHeap.empty(); ++k)
						if (m_spots[i][j].m_compactSpots[k] != NULL && m_spots[i][j].m_compactSpots[k]->Type() == MotocycleType)
						{
							Vehicle * moto = m_spots[i][j].m_compactSpots[k];
							m_spots[i][j].m_compactSpots[k] = NULL;
							auto idx = m_motoSoptMinHeap.top();
							m_motoSoptMinHeap.pop();
							m_spots[idx[0]][idx[1]].m_motoSpots[idx[3]] = moto;
							m_vehicleToSpot[moto] = idx;
							m_compactSoptMinHeap.push({ i,j,1,k });
						}
				}
			//3. move cars that occupy largeSpots to available compactSpots
			for (size_t i = 0; i < m_spots.size() && !m_compactSoptMinHeap.empty(); ++i)//level
				for (size_t j = 0; j < m_spots[i].size() && !m_compactSoptMinHeap.empty(); ++j)//row
				{
					//largeSpots
					for (size_t k = 0; k < m_spots[i][j].m_largeSpots.size() && !m_compactSoptMinHeap.empty(); ++k)
						if (m_spots[i][j].m_largeSpots[k] != NULL && m_spots[i][j].m_largeSpots[k]->Type() == CarType)
						{
							Vehicle * car = m_spots[i][j].m_largeSpots[k];
							m_spots[i][j].m_largeSpots[k] = NULL;
							auto idx = m_compactSoptMinHeap.top();
							m_compactSoptMinHeap.pop();
							m_spots[idx[0]][idx[1]].m_compactSpots[idx[3]] = car;
							m_vehicleToSpot[car] = idx;
							m_largeSoptMinHeap.push({ i,j,2,k });
						}
				}
			//4. move buses that occupy largeSpots to front of each largeSpot array

		}
	};




	bool Vehicle::Park(ParkingLot * pl)
	{
		if (pl == NULL) return false;
		m_parkingLot = pl;
		return m_parkingLot->Park(this);
	}
	bool Vehicle::UnPark()
	{
		if (m_parkingLot == NULL) return false;
		return m_parkingLot->UnPark(this);
	}
	VehicleType Motocycle::Type() { return MotocycleType; }
	VehicleType Car::Type() { return CarType; }
	VehicleType Bus::Type() { return BusType; }
	
};
#endif
