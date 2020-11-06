#ifndef CLOCK_ANGLE_H
#define CLOCK_ANGLE_H
#include <iostream>
/*
Leetcode: Angle Between Hands of a Clock
http://www.geeksforgeeks.org/calculate-angle-hour-hand-minute-hand/
http://stackoverflow.com/questions/2748965/fnd-angle-between-hour-and-minute-hands-in-an-analog-clock
http://stackoverflow.com/questions/20601427/how-do-i-calculate-the-angle-between-the-hour-and-minutes-hands
Calculate the angle between hour hand and minute hand.
*/
class ClockAngle
{
public:
	ClockAngle(){}
	~ClockAngle(){}

	double Solve(int hour, int min)
	{
		if (hour < 0 || min < 0 || hour > 12 || min > 60)
			throw std::runtime_error("");

		if (hour == 12)
			hour = 0;
		if (min == 60)
			min = 0;
		//now hour: 0~11, min: 0~59
		
		/*
		(360 / 12 / 60) == 0
		(360.0 / 12.0 / 60.0) == 0.5
		*/
		double hourAngle = (360.0 / 12.0) * hour + (360.0 / 12.0 / 60.0) * min;
		double minuteAngle = (360.0 / 60.0) * min;
		double angle = hourAngle - minuteAngle;
		if (angle < 0)
			angle = 0 - angle;
		if (angle > 180)
			angle = 360 - angle;

		std::cout << "ClockAngle for \"" << hour << "," << min << "\": " << angle << " " << this->Formula(hour, min) << std::endl;
		return angle;
	}

	double Formula(int hour, int min)
	{
		double res = std::abs((hour * 30 + min * 0.5) - (min * 6));
		return std::min(360 - res, res);
	}
};
/*
ClockAngle for "7,59": 114.5 114.5
ClockAngle for "5,50": 125 125
ClockAngle for "2,50": 145 145
ClockAngle for "10,2": 71 71
ClockAngle for "0,2": 11 11
*/
#endif