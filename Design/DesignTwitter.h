#ifndef DESIGN_TWITTER_H
#define DESIGN_TWITTER_H
#include "Debug.h"
/*
Leetcode: Design Twitter
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed.
Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.
getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself.
Tweets must be ordered from most recent to least recent.
follow(followerId, followeeId): Follower follows a followee.
unfollow(followerId, followeeId): Follower unfollows a followee.
Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);


*/
class Twitter
{
public:
	/** Initialize your data structure here. */
	Twitter()
	{
		m_globalTweetIdx = 0;
	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId)
	{
		m_followings[userId].insert(userId);//need to follow user itself when first time posting a tweet
		m_tweets[userId].push_back({ m_globalTweetIdx++, tweetId });

		std::cout << "DesignTwitter postTweet for \"" << userId << "\": " << tweetId << std::endl;
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	std::vector<int> getNewsFeed(int userId)
	{
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;//first: globalTweetIdx, second: tweetId
		for (const auto & id : m_followings[userId])
		{
			for (auto itr = m_tweets[id].crbegin(); itr != m_tweets[id].crend(); ++itr)
			{
				if (minHeap.size() == 10 && minHeap.top().first > itr->first)
					break;
				minHeap.push(*itr);
				if (minHeap.size() > 10)
					minHeap.pop();
			}
		}
		std::vector<int> res;
		while (!minHeap.empty())
		{
			res.insert(res.begin(), minHeap.top().second);
			minHeap.pop();
		}

		std::cout << "DesignTwitter getNewsFeed for \"" << userId << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId)
	{
		m_followings[followerId].insert(followeeId);

		std::cout << "DesignTwitter follow for \"" << followerId << "\": " << followeeId << std::endl;
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId)
	{
		if (followerId != followeeId)//avoid unfollowing user itself
			m_followings[followerId].erase(followeeId);

		std::cout << "DesignTwitter unfollow for \"" << followerId << "\": " << followeeId << std::endl;
	}

private:
	int m_globalTweetIdx;//a greater globalTweetIdx means a more recent tweet
	std::unordered_map<int, std::unordered_set<int>> m_followings;//first: userIdx, second: a set of following userIdx
	std::unordered_map<int, std::vector<std::pair<int, int>>> m_tweets;//first: userIdx, second: a list of tweets<globalTweetIdx, tweetIdx> with globalTweetIdx in increasing order
};

/**
* Your Twitter object will be instantiated and called as such:
* Twitter obj = new Twitter();
* obj.postTweet(userId,tweetId);
* vector<int> param_2 = obj.getNewsFeed(userId);
* obj.follow(followerId,followeeId);
* obj.unfollow(followerId,followeeId);
*/

/*
DesignTwitter postTweet for "1": 5
DesignTwitter getNewsFeed for "1": 5
DesignTwitter follow for "1": 2
DesignTwitter postTweet for "2": 6
DesignTwitter getNewsFeed for "1": 6, 5
DesignTwitter unfollow for "1": 2
DesignTwitter getNewsFeed for "1": 5
*/
#endif
