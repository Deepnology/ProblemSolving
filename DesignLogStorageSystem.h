#ifndef DESIGN_LOG_STORAGE_SYSTEM_H
#define DESIGN_LOG_STORAGE_SYSTEM_H
#include "Debug.h"
/*
Leetcode: Design Log Storage System
You are given several logs that each log contains a unique id and timestamp.
Timestamp is a string that has the following format: Year:Month:Day:Hour:Minute:Second,
for example, 2017:01:01:23:59:59. All domains are zero-padded decimal numbers.
Design a log storage system to implement the following functions:
void Put(int id, string timestamp):
Given a log's unique id and timestamp, store the log in your storage system.
int[] Retrieve(String start, String end, String granularity):
Return the id of logs whose timestamps are within the range from start to end.
Start and end all have the same format as timestamp. However, granularity means the time level for consideration.
For example, start = "2017:01:01:23:59:59", end = "2017:01:02:23:59:59", granularity = "Day",
it means that we need to find the logs within the range from Jan. 1st 2017 to Jan. 2nd 2017.

Example 1:
put(1, "2017:01:01:23:59:59");
put(2, "2017:01:01:22:59:59");
put(3, "2016:01:01:00:00:00");
retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year"); // return [1,2,3], because you need to return all logs within 2016 and 2017.
retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Hour"); // return [1,2], because you need to return all logs start from 2016:01:01:01 to 2017:01:01:23, where log 3 is left outside the range.

Note:
There will be at most 300 operations of Put or Retrieve.
Year ranges from [2000,2017]. Hour ranges from [00,23].
Output for Retrieve has no order required.
*/
class DesignLogStorageSystem
{
	std::map<long, int> toId;
public:
	DesignLogStorageSystem()
	{

	}

	void put(int id, std::string timestamp)
	{
		toId.insert({ Compress(timestamp),id });
	}
	std::vector<int> retrieve(std::string s, std::string e, std::string gra)
	{
		long begin = Compress(s, gra, true);
		long end = Compress(e, gra, false);
		std::vector<int> res;
		auto beginItr = toId.lower_bound(begin);
		auto endItr = toId.upper_bound(end);
		for (; beginItr != endItr; ++beginItr)
		{
			res.push_back(beginItr->second);
		}
		return res;
	}

	long Compress(std::string timestamp, std::string gra, bool isStart)
	{
		std::unordered_map<std::string, int> map({ { "Year",0 },{ "Month",1 },{ "Day",2 },{ "Hour",3 },{ "Minute",4 },{ "Second",5 } });
		int level = map[gra];
		std::istringstream iss(timestamp);
		std::string s;
		std::vector<int> nums;
		while (getline(iss, s, ':'))
			nums.push_back(stoi(s));
		long res;

		//note: min month: 1, min day: 1, min hour: 0, min minute: 0, min second: 0
		if (isStart)
			res = (nums[0] - 1999L) * 12 * 31 * 24 * 60 * 60 +
			(level < 1 ? 1 * 31 * 24 * 60 * 60 + 1 * 24 * 60 * 60 + 0 * 60 * 60 + 0 * 60 + 0 : nums[1] * 31 * 24 * 60 * 60 +
			(level < 2 ? 1 * 24 * 60 * 60 + 0 * 60 * 60 + 0 * 60 + 0 : nums[2] * 24 * 60 * 60 +
			(level < 3 ? 0 * 60 * 60 + 0 * 60 + 0 : nums[3] * 60 * 60 +
			(level < 4 ? 0 * 60 + 0 : nums[4] * 60 +
			(level < 5 ? 0 : nums[5])))));
		else
			res = (nums[0] - 1999L) * 12 * 31 * 24 * 60 * 60 +
			(level < 1 ? 12 * 31 * 24 * 60 * 60 + 31 * 24 * 60 * 60 + 24 * 60 * 60 + 60 * 60 + 60 : nums[1] * 31 * 24 * 60 * 60 +
			(level < 2 ? 31 * 24 * 60 * 60 + 24 * 60 * 60 + 60 * 60 + 60 : nums[2] * 24 * 60 * 60 +
			(level < 3 ? 24 * 60 * 60 + 60 * 60 + 60 : nums[3] * 60 * 60 +
			(level < 4 ? 60 * 60 + 60 : nums[4] * 60 +
			(level < 5 ? 60 : nums[5])))));
		return res;

	}

	long Compress(std::string timestamp)
	{
		std::istringstream iss(timestamp);
		std::string s;
		std::vector<int> nums;
		while (getline(iss, s, ':'))
			nums.push_back(stoi(s));
		long res = (nums[0] - 1999L) * 12 * 31 * 24 * 60 * 60 +
			nums[1] * 31 * 24 * 60 * 60 +
			nums[2] * 24 * 60 * 60 +
			nums[3] * 60 * 60 +
			nums[4] * 60 +
			nums[5];
		return res;
	}
};
/*

*/
#endif
