#ifndef _MARATHON_TRACK_RUNNER_H
#define _MARATHON_TRACK_RUNNER_H
#include "Debug.h"
/*
Bloomberg
 */
class MarathonTrackRunner
{
    typedef std::list<std::pair<int,std::string>> RunnerList;//<numOfLaps,runner>
    typedef std::list<RunnerList> CheckPointList;//could use vector instead
    std::unordered_map<std::string, std::pair<CheckPointList::iterator, RunnerList::iterator>> runnerMap;
    CheckPointList checkPointList;
public:
    MarathonTrackRunner(){}

    void AddRunnerToCheckPoint(const std::string & runner)
    {

    }

    std::vector<std::string> GetRank()
    {
        int maxLap = 0;
        for (auto itr = checkPointList.begin(); itr != checkPointList.end(); ++itr)
            for (auto itr2 = itr->begin(); itr2 != itr->end(); ++itr2)
                maxLap = std::max(maxLap, itr2->first);
        std::vector<std::string> res;
        for (int lap = maxLap; lap >= 0; --lap)
            for (auto itr = checkPointList.begin(); itr != checkPointList.end(); ++itr)
                for (auto itr2 = itr->begin(); itr2 != itr->end(); ++itr2)
                    if (itr2->first == lap)
                        res.push_back(itr2->second);


        return res;
    }
};
#endif
