#ifndef DESIGN_TRACK_RUNNER_SYSTEM_H
#define DESIGN_TRACK_RUNNER_SYSTEM_H
#include "Debug.h"
/*
Bloomberg
Many runners (with id and name) run on a track.
There checking points (with distance to end and id) on the track.
Need to update top k runners.
Same as AllOoneIncrDecrGetMaxMin.h
*/
class DesignTrackRunnerSystem
{
	typedef std::list<std::string> KeyList;//front: earliest runner <-> back: latest runner
	typedef std::list<std::pair<int, KeyList>> ValList;//front: last checking point <-> back: first checking point
	ValList m_valList;
	std::unordered_map<std::string, std::pair<ValList::iterator, KeyList::iterator>> m_keyMap;
public:
	DesignTrackRunnerSystem() {}


};
#endif
