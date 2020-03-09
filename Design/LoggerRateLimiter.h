#ifndef LOGGER_RATE_LIMITER_H
#define LOGGER_RATE_LIMITER_H
#include "Debug.h"
/*
Leetcode: Logger Rate Limiter
Design a logger system that receive stream of messages along with its timestamps, each message should be printed if and only if it is not printed in the last 10 seconds.
Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given timestamp, otherwise returns false.
It is possible that several messages arrive roughly at the same time.

Example:

Logger logger = new Logger();

// logging string "foo" at timestamp 1
logger.shouldPrintMessage(1, "foo"); returns true;

// logging string "bar" at timestamp 2
logger.shouldPrintMessage(2,"bar"); returns true;

// logging string "foo" at timestamp 3
logger.shouldPrintMessage(3,"foo"); returns false;

// logging string "bar" at timestamp 8
logger.shouldPrintMessage(8,"bar"); returns false;

// logging string "foo" at timestamp 10
logger.shouldPrintMessage(10,"foo"); returns false;

// logging string "foo" at timestamp 11
logger.shouldPrintMessage(11,"foo"); returns true;
*/
class LoggerRateLimiter
{
public:
	LoggerRateLimiter() {}
	~LoggerRateLimiter() {}

	void ShouldPrintMessage(int timestamp, const std::string & message)
	{
		std::cout << "LoggerRateLimiter ShouldPrintMessage for \"" << timestamp << "\", \"" << message << "\": ";
		if (this->shouldPrintMessage(timestamp, message))
			std::cout << "1" << std::endl;
		else
			std::cout << "0" << std::endl;
	}

	bool shouldPrintMessage(int timestamp, const std::string & message)
	{
		if (!m_msgToTime.count(message))
		{
			m_msgToTime[message] = timestamp;
			return true;
		}
		if (timestamp - m_msgToTime[message] >= 10)
		{
			m_msgToTime[message] = timestamp;
			return true;
		}

		//if timestamp diff < 10: don't update timestamp
		return false;
	}

private:
	std::unordered_map<std::string, int> m_msgToTime;//first: message, second: timestamp
};
/*
LoggerRateLimiter ShouldPrintMessage for "1", "foo": 1
LoggerRateLimiter ShouldPrintMessage for "2", "bar": 1
LoggerRateLimiter ShouldPrintMessage for "3", "foo": 0
LoggerRateLimiter ShouldPrintMessage for "8", "bar": 0
LoggerRateLimiter ShouldPrintMessage for "10", "foo": 0
LoggerRateLimiter ShouldPrintMessage for "11", "foo": 1
*/
#endif
