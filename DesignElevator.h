#ifndef DESIGN_ELEVATOR_H
#define DESIGN_ELEVATOR_H
#include "Debug.h"
/*
https://www.codeproject.com/Articles/703634/SOLID-architecture-principles-using-simple-Csharp
SOLID OOD Principle
S: Single Responsibility Principle
   (Single responsibility for each object)
O: Open Closed Principle
   (Objects are open for extension but closed for modification)
L: Liskov Substitution Principle
   (Base class and derived class follow 'IS A' principle)
I: Interface Segregation Principle
   (Many client-specific interfaces are better than one general-purposed interface.
   It is because one general-purposed interface forces clients to depend on methods they don't use.)
D: Dependency Inversion Principle
   (If a class depends on another class's concretion, it becomes dependency inversion.
   Entities must depend on abstractions not on concretions. Delegate this responsibility to users.)

http://www.hiringlibrary.com/object-oriented-design-interview-for-parking-lot-or-elevator/
https://www.quora.com/What-is-the-best-answer-to-Design-an-elevator-system
A typical lift has buttons (Elevator buttons) inside the cabin to let the user who got the lift to select his/her desired floors.
Similarly, each floor has buttons (Floor buttons) to call the lift to go floors above and a floor below respectively.
The buttons illuminate indicating the request is accepted.
In addition, the button stops illuminating when the lift reaches the requested floor.

Use cases:
User
	-Presses the floor button to call the lift
	-Presses the elevator button to move to the desired floor
Floor button & Elevator button
	-Illuminates when pressed by user
	-Places an elevator request when pressed
Elevator
	-Moves up/down as per instruction
	-Opens/closes the door

*/
namespace DesignElevator
{
	class Person;
	class Building;
	class Elevator
	{
		//bi-directional mapping !!
		std::unordered_map<Person*, int> m_people;//map people in this elevator to target floor
		std::map<int, std::unordered_set<Person*>> m_tgtFloor;//map floor to people
		int m_curFloor;
		bool m_dir;
		Building * m_building;
	public:
		Elevator(): m_people(), m_tgtFloor()
			, m_curFloor(0), m_dir(true)
		{}
		int NextFloor()
		{
			if (m_tgtFloor.empty()) return m_curFloor;
			while (true)
			{
				if (m_dir)//go up
				{
					auto itr = m_tgtFloor.lower_bound(m_curFloor);
					if (itr != m_tgtFloor.end())
						return itr->first;
					//otherwise, go down
					m_dir = !m_dir;
				}
				else//go down
				{
					auto itr = m_tgtFloor.lower_bound(m_curFloor);
					if (itr != m_tgtFloor.end() && itr->first == m_curFloor)
						return itr->first;
					else if (itr != m_tgtFloor.begin())
						return std::prev(itr)->first;
					//otherwise, go up
					m_dir = !m_dir;
				}
			}
			return 0;//won't reach here
		}
		bool Idle()
		{
			return m_tgtFloor.empty();
		}
		//<floor,set of Person*>
		std::pair<int, std::unordered_set<Person*>> Unload()
		{
			CloseDoor();
			int tgtFloor = NextFloor();
			MoveTo(tgtFloor);
			if (m_tgtFloor.count(tgtFloor))
			{
				OpenDoor();
				std::pair<int, std::unordered_set<Person*>> res({ tgtFloor, m_tgtFloor[tgtFloor] });
				m_tgtFloor.erase(tgtFloor);
				for (auto & p : res.second)
					m_people.erase(p);
				return res;
			}
			//empty: unload no-people
			return{ m_curFloor,std::unordered_set<Person*>() };
		}
		void Load(std::unordered_map<Person*, int> & passenger)
		{
			OpenDoor();
			for (auto & p : passenger)
			{
				m_people.insert(p);
				m_tgtFloor[p.second].insert(p.first);
			}
		}

		void MoveTo(int floor)
		{
			m_curFloor = floor;
		}
		void OpenDoor()
		{

		}
		void CloseDoor()
		{

		}
	};
	class Building
	{
		int m_numFloor;
		int m_numElevaotr;
		std::vector<Elevator> m_elevator;
		//bi-directional mapping !!
		std::vector<std::unordered_set<Person*>> m_floorToUsr;//map location to usr
		std::unordered_map<Person*, std::pair<int,int>> m_usrToFloorElevator;//map usr to location<floor,elevator>
		std::vector<std::queue<std::pair<Person*,int>>> m_floorWaitingQueue;
	public:
		Building(int numFloor, int numElevator): m_numFloor(numFloor), m_numElevaotr(numElevator)
			, m_elevator(numElevator, Elevator())
			, m_floorToUsr(numFloor, std::unordered_set<Person*>())
			, m_usrToFloorElevator() {}
			, m_floorWaitingQueue(numFloor, std::queue())
			{}

		void EnterPerson(Person * p)
		{
			m_usrToFloorElevator.insert({ p, {0,-1} });
		}
		void LeavePerson(Person * p)
		{
			if (m_usrToFloorElevator.find(p) == m_usrToFloorElevator.end()) return;
			std::pair<int, int> location = m_usrToFloorElevator[p];
			if (location.first != 0) return;
			//now person is on 0th floor
			m_usrToFloorElevator.erase(p);
		}
		std::pair<int, int> FindLocation(Person* p)
		{
			if (m_usrToFloorElevator.find(p) == m_usrToFloorElevator.end()) return{ -1,-1 };
			return m_usrToFloorElevator[p];
		}
		void Enqueue(Person * p, int srcFloor, int tgtFloor)
		{
			m_floorWaitingQueue[srcFloor].push({ p,tgtFloor });
		}
		void UpdateElevators()
		{
			std::queue<int> idleElevators;
			for (int i = 0; i < m_numElevaotr; ++i)
			{
				//1. unload elevator at its arrival floor
				std::pair<int, std::unordered_set<Person*>> arrival = m_elevator[i].Unload();
				if (!arrival.second.empty())
				{
					m_floorToUsr[arrival.first].insert(arrival.second.begin(), arrival.second.end());
					for (auto & p : arrival.second)
						m_usrToFloorElevator[p] = { arrival.first, -1 };
				}
				//2. load elevator at its arrival floor
				std::unordered_map<Person*, int> passenger;
				while (!m_floorWaitingQueue[arrival.first].empty())
				{
					auto personPair = m_floorWaitingQueue[arrival.first].front();
					m_floorWaitingQueue[arrival.first].pop();
					passenger.insert(personPair);
					m_usrToFloorElevator[personPair.first] = { -1, i };
				}
				if (!passenger.empty())
					m_elevator[i].Load(passenger);
				else if (m_elevator[i].Idle())
					idleElevators.push(i);//if an elevator is not loading any person and its passenger is empty, it becomes idle, collect it
			}

			//dispatch all idle elevators to floors with non-empty waiting queue
			for (int i = 0; i < m_numFloor && !idleElevators.empty(); ++i)
			{
				if (!m_floorWaitingQueue[i].empty())
				{
					int e = idleElevators.front();
					idleElevators.pop();
					std::unordered_map<Person*, int> passenger;
					while (!m_floorWaitingQueue[i].empty())
					{
						auto personPair = m_floorWaitingQueue[i].front();
						m_floorWaitingQueue[i].pop();
						passenger.insert(personPair);
						m_usrToFloorElevator[personPair.first] = { -1, e };
					}
					m_elevator[e].CloseDoor();
					m_elevator[e].MoveTo(i);
					m_elevator[e].Load(passenger);
				}
			}
		}
	};

	class Person
	{
		Building * m_building;
	public:
		Person(): m_building(NULL) {}

		bool EnterBuilding(Building * b)
		{
			if (m_building == NULL && b != NULL)
			{
				m_building = b;
				b->EnterPerson(this);
				return true;
			}
			return false;
		}
		bool LeaveBuilding()
		{
			if (m_building == NULL) return false;
			std::pair<int, int> location = m_building->FindLocation(this);
			if (location.first < 0 || location.first != 0) return false;
			m_building->LeavePerson(this);
			m_building = NULL;
			return true;
		}
		void FetchElevator(int tgtFloor)
		{
			if (m_building == NULL) return;
			std::pair<int, int> location = m_building->FindLocation(this);//<floor,elevator>
			if (location.first < 0) return;//floor is invalid
			if (location.first == tgtFloor) return;
			m_building->Enqueue(this, location.first, tgtFloor);
		}
	};
}
#endif
