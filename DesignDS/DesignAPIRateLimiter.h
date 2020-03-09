#ifndef _DESIGN_API_RATE_LIMITER_H
#define _DESIGN_API_RATE_LIMITER_H
#include "Debug.h"
#include "TestCase.h"
/*
Grokking the system design interview: Design an API Rate Limiter
assume max 500 hits per hour, max 10 hits per min
input timestamp is sec
see also DesignHitCounter.h, LoggerRateLimiter.h
 */
class DesignAPIRateLimiter
{
    //const int HOUR = 3600;
    //const int MINUTE = 60;
    //const int MAX_HIT_HOUR = 500;
    //const int MAX_HIT_MINUTE = 10;
    const int HOUR = 30;
    const int MINUTE = 5;
    const int MAX_HIT_HOUR = 15;
    const int MAX_HIT_MINUTE = 3;
public:
    DesignAPIRateLimiter(){}

    std::unordered_map<std::string, std::pair<std::queue<std::pair<int,int>>,int>> usrQue;//<user,<<timestamp,hitCountPerMin>,hitCountPerHour>>
    bool Hit_Queue(const std::string & user, int timestamp)
    {
        if (usrQue.count(user) == 0)
        {
            usrQue.insert({user, std::pair<std::queue<std::pair<int,int>>, int>({std::queue<std::pair<int,int>>({{timestamp,1}}),1})});
            return true;
        }
        else
        {
            //1.1. remove front pairs that are out of range of 1 hour
            auto itr = usrQue.find(user);
            while (!itr->second.first.empty() && timestamp - itr->second.first.front().first > HOUR)//3600sec per hour
            {
                itr->second.second -= itr->second.first.front().second;
                itr->second.first.pop();
            }
            //1.2. exceed hour limit
            if (itr->second.second >= MAX_HIT_HOUR) return false;

            //2.1. in range of 1 minute
            if (timestamp - itr->second.first.back().first <= MINUTE)
            {
                //2.1.1. exceed minute limit
                if (itr->second.first.back().second >= MAX_HIT_MINUTE)
                    return false;
                //2.1.2. not exceed minute limit
                ++itr->second.first.back().second;
            }
            else//2.2. out of range of 1 minute
                itr->second.first.push({timestamp,1});


            ++itr->second.second;
            return true;
        }
    }

    void Test()
    {
        auto v = TestCase::RandSortedVec(100, 1, 100);
        std::cout << "DesignAPIRateLimit: ";
        for (auto & i : v)
        {
            bool res = Hit_Queue("a", i);
            std::cout << "(" << i << "," << res << "),";
        }
        std::cout << std::endl;
    }

};
/*
DesignAPIRateLimit: (1,1),(1,1),(2,1),(4,0),(6,0),(8,1),(9,1),(10,1),(11,0),(12,0),(16,1),(18,1),(18,1),(19,0),(19,0),
 (20,0),(20,0),(22,1),(22,1),(23,1),(23,0),(25,0),(26,0),(27,0),(27,0),(28,1),(29,1),(34,1),(35,1),(36,1),(37,0),(38,0),
 (39,0),(39,0),(39,0),(40,1),(41,1),(42,1),(42,0),(42,0),(43,0),(44,0),(46,1),(46,0),(48,1),(50,1),(51,0),(52,1),(52,0),
 (53,1),(53,1),(54,0),(57,0),(57,0),(59,1),(59,1),(61,1),(62,0),(63,0),(65,1),(67,1),(69,1),(69,0),(71,1),(71,1),(72,1),
 (72,0),(72,0),(73,0),(73,0),(73,0),(74,0),(74,0),(74,0),(75,0),(75,0),(75,0),(76,0),(76,0),(77,1),(80,1),(80,1),(83,1),
 (85,1),(86,1),(86,0),(86,0),(86,0),(88,0),(89,0),(90,1),(92,1),(93,1),(93,0),(94,0),(96,1),(97,1),(98,1),(99,0),(100,0),
 */
#endif
