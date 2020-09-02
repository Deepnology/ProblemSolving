#ifndef _TRAFFIC_LIGHT_CONTROLLED_INTERSECTION_H
#define _TRAFFIC_LIGHT_CONTROLLED_INTERSECTION_H
#include "Debug.h"
#include <thread>
#include <mutex>
#include <condition_variable>
/*
Leetcode: Traffic Light Controlled Intersection
 */
class TrafficLight
{
    std::mutex mMutex;
    int mCurGreenRoad;
public:
    TrafficLight() : mCurGreenRoad(1)
    {

    }

    void carArrived(
            int carId,                   // ID of the car
            int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
            int direction,               // Direction of the car
            function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
            function<void()> crossCar    // Use crossCar() to make car cross the intersection
    )
    {
        std::unique_lock<std::mutex> lock(mMutex);
        if (mCurGreenRoad != roadId)
        {
            turnGreen();
            mCurGreenRoad = roadId;
        }
        crossCar();
    }
};
#endif
