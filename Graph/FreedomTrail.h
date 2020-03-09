#ifndef FREEDOM_TRAIL_H
#define FREEDOM_TRAIL_H
#include "Debug.h"
/*
Leetcode: Freedom Trail
In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring", and use the dial to spell a specific keyword in order to open the door.
Given a string ring, which represents the code engraved on the outer ring and another string key, which represents the keyword needs to be spelled.
You need to find the minimum number of steps in order to spell all the characters in the keyword.

Initially, the first character of the ring is aligned at 12:00 direction.
You need to spell all the characters in the string key one by one by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by pressing the center button.
At the stage of rotating the ring to spell the key character key[i]:
You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step.
The final purpose of the rotation is to align one of the string ring's characters at the 12:00 direction, where this character must equal to the character key[i].
If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 1 step.
After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.

Input: ring = "godding", key = "gd"
Output: 4
Explanation:
For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
Also, we need 1 more step for spelling.
So the final output is 4.
*/
class FreedomTrail
{
public:
	FreedomTrail() {}

	int DP2D(const std::string & ring, const std::string & key)
	{
		int N = key.size();
		int M = ring.size();
		std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M, INT_MAX));
		dp[0][0] = 0;
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (ring[j] == key[i - 1])//cur ring char matches cur key char
				{
					for (int k = 0; k < M; ++k)//lookup prev result
					{
						if (dp[i - 1][k] != INT_MAX)
						{
							//(k+M-j)%M = steps from k to j in backward if k < j, in forward if k > j
							//(j+M-k)%M = steps from j to k in forward if k < j, in backward if k > j
							//in reverse means going through head and tail
							dp[i][j] = std::min(dp[i][j], dp[i - 1][k] + std::min((k + M - j) % M, (j + M - k) % M));
						}
					}
				}
			}
		}

		int res = INT_MAX;
		for (int j = 0; j < M; ++j)
			res = std::min(res, dp[N][j]);

		std::cout << "FreedomTrail DP2D for \"" << ring << "\", \"" << key << "\": " << res + N << std::endl;
		return res + N;
	}
public:
	int DFS_DP(const std::string & ring, const std::string & key)
	{
		std::unordered_map<std::string, std::unordered_map<int, int>> dp;
		int res = recur(ring, key, 0, dp);
		std::cout << "FreedomTrail DFS_DP for \"" << ring << "\", \"" << key << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(std::string ring, const std::string & key, int i, std::unordered_map<std::string, std::unordered_map<int, int>> & dp)
	{
		int N = key.size();
		if (i == N) return 0;
		if (dp[ring].count(i))
			return dp[ring][i];

		//compute the forward distance to find key[i]
		int fwd = ring.find(key[i]);

		//compute the backward distance to find key[i]
		int bwd = ring.size() - ring.rfind(key[i]);
		std::string bwdState = ring;
		std::rotate(bwdState.rbegin(), bwdState.rbegin() + bwd, bwdState.rend());//right rotate

		//std::cout << ring << "," << key[i] << ":" << fwd << "(" << ring.substr(fwd)+ring.substr(0,fwd) << ")," << bwd << "(" << bwdState << ")" << std::endl;

		int fwdRes = 1 + fwd + recur(ring.substr(fwd) + ring.substr(0, fwd), key, i + 1, dp);
		int bkdRes = 1 + bwd + recur(bwdState, key, i + 1, dp);
		return dp[ring][i] = std::min(fwdRes, bkdRes);
	}
public:
	//BFS is too slow to pass online judge
	int BFS_DP(const std::string & ring, const std::string & key)
	{
		int N = key.size();
		int M = ring.size();
		std::unordered_map<char, std::set<int>> map;//<char, all occur idxs>
		for (int i = 0; i < M; ++i)
			map[ring[i]].insert(i);

		int res = INT_MAX;
		std::queue<std::vector<int>> que;//[beginIdxOfRing, beginIdxOfKey, numOfSteps]
		std::unordered_map<int, std::unordered_map<int, int>> dp;
		que.push({ 0,0,0 });
		while (!que.empty())
		{
			int rBegin = que.front()[0];
			int kBegin = que.front()[1];
			int steps = que.front()[2];
			que.pop();

			if (kBegin == N)
			{
				res = std::min(res, steps);
				continue;
			}

			//std::string cur = ring.substr(rBegin) + ring.substr(0, rBegin);

			//compute the forward distance to find key[kBegin]
			int fwd = FWD(map, key[kBegin], rBegin, M);
			//int fwd2 = cur.find(key[kBegin]);
			int nxtRBegin = rBegin + fwd >= M ? rBegin + fwd - M : rBegin + fwd;
			if (dp[nxtRBegin].count(kBegin) == 0 || dp[nxtRBegin][kBegin] > steps + fwd + 1)
			{
				dp[nxtRBegin][kBegin] = steps + fwd + 1;
				que.push({ nxtRBegin, kBegin + 1, steps + fwd + 1 });
			}
			//compute the backward distance to find key[kBegin]
			int bkd = BKD(map, key[kBegin], rBegin, M);
			//std::string rRing(cur);
			//std::reverse(rRing.begin(), rRing.end());
			//rRing = rRing.substr(M-1) + rRing.substr(0, M-1);//last char + all chars before last char
			//int bkd2 = rRing.find(key[kBegin]);
			int nxtRBegin2 = rBegin - bkd < 0 ? rBegin - bkd + M : rBegin - bkd;
			if (dp[nxtRBegin2].count(kBegin) == 0 || dp[nxtRBegin2][kBegin] > steps + bkd + 1)
			{
				dp[nxtRBegin2][kBegin] = steps + bkd + 1;
				que.push({ nxtRBegin2, kBegin + 1, steps + bkd + 1 });
			}

			//std::cout << cur << "," << rRing << "," << key[kBegin] << ":" << fwd << "," << bkd << ";" << fwd2 << "," << bkd2 << std::endl;
		}

		std::cout << "FreedomTrail BFS_DP for \"" << ring << "\", \"" << key << "\": " << res << std::endl;
		return res;
	}
private:
	int FWD(std::unordered_map<char, std::set<int>> & map, char c, int idx, int M)//idx is the begin of ring
	{
		//std::cout << "FWD:" << c << "," << idx << std::endl;
		auto iter = map[c].lower_bound(idx);
		if (iter != map[c].end())
			return (*iter - idx);
		return *map[c].begin() + (M - idx);
	}
	int BKD(std::unordered_map<char, std::set<int>> & map, char c, int idx, int M)//idx is the begin of ring
	{
		//std::cout << "BKD:" << c << "," << idx << std::endl;
		auto iter = map[c].lower_bound(idx);
		if (iter != map[c].end() && *iter == idx)
			return 0;
		if (iter == map[c].begin())
			return idx + (M - *map[c].rbegin());
		return idx - *std::prev(iter);
	}

public:
	//time limit exceeded
	int BFS_DP_Simple(const std::string & ring, const std::string & key)
	{
		int N = key.size();
		int M = ring.size();
		int res = INT_MAX;
		std::unordered_map<std::string,std::unordered_map<int,int>> dp;
		std::queue<std::tuple<std::string,int,int>> que;
		que.push({ring,0,0});
		while(!que.empty())
		{
			std::string state = std::get<0>(que.front());
			int idx = std::get<1>(que.front());
			int numSteps = std::get<2>(que.front());
			que.pop();
			if (idx == N)
			{
				res = std::min(res, numSteps);
				continue;
			}
			int fwd = state.find(key[idx]);
			std::string fwdState = state.substr(fwd) + state.substr(0, fwd);
			if (dp[fwdState].count(idx) == 0 || dp[fwdState][idx] > numSteps + fwd + 1)
			{
				dp[fwdState][idx] = numSteps + fwd + 1;
				que.push({fwdState, idx+1, numSteps+fwd+1});
			}

			int bwd = state.size() - state.rfind(key[idx]);
			std::string bwdState = state;
			std::rotate(bwdState.rbegin(), bwdState.rbegin() + bwd, bwdState.rend());//right rotate
			if (dp[bwdState].count(idx) == 0 || dp[bwdState][idx] > numSteps + bwd + 1)
			{
				dp[bwdState][idx] = numSteps + bwd + 1;
				que.push({bwdState, idx+1, numSteps+bwd+1});
			}
		}
		std::cout << "FreedomTrail BFS_DP_Simple for \"" << ring << "\", \"" << key << "\": " << res << std::endl;
		return res;
	}
};
/*
FreedomTrail DP2D for "godding", "ond": 9
FreedomTrail DFS_DP for "godding", "ond": 9
FreedomTrail BFS_DP for "godding", "ond": 9
FreedomTrail BFS_DP_Simple for "godding", "ond": 9
FreedomTrail DP2D for "czjdn", "zzznnnjjjdddccc": 23
FreedomTrail DFS_DP for "czjdn", "zzznnnjjjdddccc": 23
FreedomTrail BFS_DP for "czjdn", "zzznnnjjjdddccc": 23
FreedomTrail BFS_DP_Simple for "czjdn", "zzznnnjjjdddccc": 23
*/
#endif
