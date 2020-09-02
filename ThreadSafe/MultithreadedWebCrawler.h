#ifndef _MULTITHREADED_WEB_CRAWLER_H
#define _MULTITHREADED_WEB_CRAWLER_H
#include "Debug.h"
#include <thread>
#include <mutex>
#include <condition_variable>
/*
Leetcode: Web Crawler Multithreaded
Given a url startUrl and an interface HtmlParser, implement a Multi-threaded web crawler to crawl all links
 that are under the same hostname as startUrl.
Return all urls obtained by your web crawler in any order.
Your crawler should:
Start from the page: startUrl
Call HtmlParser.getUrls(url) to get all urls from a webpage of given url.
Do not crawl the same link twice.
Explore only the links that are under the same hostname as startUrl.
As shown in the example url above, the hostname is example.org. For simplicity sake, you may assume all urls use
 http protocol without any port specified.
 For example, the urls http://leetcode.com/problems and http://leetcode.com/contest are under the same hostname,
 while urls http://example.org/test and http://example.com/abc are not under the same hostname.
The HtmlParser interface is defined as such:
interface HtmlParser {
  // Return a list of all urls from a webpage of given url.
  // This is a blocking call, that means it will do HTTP request and return when this request is finished.
  public List<String> getUrls(String url);
}
Note that getUrls(String url) simulates performing a HTTP request.
You can treat it as a blocking function call which waits for a HTTP request to finish.
It is guaranteed that getUrls(String url) will return the urls within 15ms.
Single-threaded solutions will exceed the time limit so, can your multi-threaded web crawler do better?
Below are two examples explaining the functionality of the problem, for custom testing purposes you'll have three variables urls, edges and startUrl.
Notice that you will only have access to startUrl in your code, while urls and edges are not directly accessible to you in code.
Follow up:
Assume we have 10,000 nodes and 1 billion URLs to crawl. We will deploy the same software onto each node.
 The software can know about all the nodes. We have to minimize communication between machines and make sure each node does equal amount of work.
 How would your web crawler design change?
What if one node fails or does not work?
How do you know when the crawler is done?
 */

class MultithreadedWebCrawler
{
    const int NUM_THREADS = 12;
    std::mutex mMutex;
    std::condition_variable mCondition;
    std::unordered_set<std::string> mVisit;
    std::queue<std::string> mQue;
    int mWaiting;
public:
    class HtmlParser
    {
    public:
        std::vector<std::string> getUrls(std::string url);
    };
    std::vector<std::string> Crawl(std::string startUrl, HtmlParser htmlParser)
    {
        mWaiting = 0;
        std::vector<std::thread> threadVec;
        std::string domain = getDomain(startUrl);

        //===critical Section===
        std::unique_lock<std::mutex> lock(mMutex);
        mVisit.insert(startUrl); //include startUrl
        mQue.push(startUrl);
        for (int i = 0; i < NUM_THREADS; ++i)
            threadVec.push_back(std::thread(&MultithreadedWebCrawler::crawlThread, this, &htmlParser, domain));
        lock.unlock();
        //===Critical Section===

        for (int i = 0; i < NUM_THREADS; ++i)
            threadVec[i].join();

        std::vector<std::string> res(mVisit.begin(), mVisit.end());
        return res;
    }
private:
    //'crawling thread' to crawl urls in mQue that are under the same domain as startUrl
    void crawlThread(HtmlParser * parser, std::string domain)
    {
        while (1)
        {
            //===Critical Section===
            std::unique_lock<std::mutex> lock(mMutex);
            ++mWaiting;

            while (mQue.empty() && (mWaiting < NUM_THREADS))
                mCondition.wait(lock);

            //mCondition.wait(lock, [this] { return !mQue.empty() || (mQue.empty() && mWaiting==NUM_THREADS); });

            if (mQue.empty())
                return;
            --mWaiting;
            std::string url = mQue.front();
            mQue.pop();
            lock.unlock();
            //===Critical Section===

            std::vector<std::string> neighbors = parser->getUrls(url);

            //===Critical Section===
            lock.lock();
            for (auto & neighbor : neighbors)
                if (!mVisit.count(neighbor) && getDomain(neighbor) == domain)
                {
                    //only include urls that are under the same domain as startUrl
                    mVisit.insert(neighbor);
                    mQue.push(neighbor);
                }
            mCondition.notify_all();
            //===Critical Section===
        }
    }
    std::string getDomain(const std::string & url)
    {
        size_t idx = url.find("/", 7); //find 1st "/" idx after http://
        return url.substr(0, idx); //return http://xxx.xxx
    }
};
#endif
