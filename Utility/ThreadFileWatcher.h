#ifndef THREAD_FILE_WATCHER_H
#define THREAD_FILE_WATCHER_H

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <filesystem>
#include <chrono>
#include <vector>
#include <functional>

namespace fs = std::filesystem;

class ThreadFileWatcher
{
    inline static std::thread m_thread;
    inline static bool m_isThreadRunning = false;    
    inline static std::string m_watchedFile;
    inline static fs::file_time_type m_lastWriteTime;

    inline static std::mutex m_taskArrMutex;
    inline static std::vector<std::function<void(void)>> m_taskArr;
    inline static bool m_stopThread = false;
    inline static std::condition_variable m_taskArrCond;

    static void watcherThread()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(m_taskArrMutex);
            m_taskArrCond.wait(lock, [] { return !m_taskArr.empty() || m_stopThread; });
            if (m_stopThread)
            {
                std::cout << "Exiting..." << std::endl;
                break;
            }
            auto copyTaskArr = m_taskArr;
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            if (fs::exists(m_watchedFile))
            {
                auto curWriteTime = fs::last_write_time(m_watchedFile);
                if (curWriteTime != m_lastWriteTime)
                {
                    m_lastWriteTime = curWriteTime;

                    std::ifstream file(m_watchedFile);
                    if (file.is_open())
                    {
                        std::string content;
                        std::getline(file, content);
                        file.close();

                        if (content.find('x') != std::string::npos)
                        {
                            m_stopThread = true;
                        }
                        else
                        {
                            for (int i = 0; i < (int)copyTaskArr.size(); ++i)
                            {
                                char idx = (i <= 9 ? (i + '0') : (i - 10 + 'a'));
                                if (content.find(idx) != std::string::npos)
                                {
                                    std::cout << "Execute task array [" << idx << "]..." << std::endl;
                                    copyTaskArr[i]();
                                }
                            }
                        }
                    }
                    else
                        std::cerr << "Error opening file: " << m_watchedFile << std::endl;
                }
            }
        }
    }
public:
    static void pushBackTask(std::function<void()> func)
    {
        std::lock_guard<std::mutex> lock(m_taskArrMutex);
        m_taskArr.push_back(func);
        m_taskArrCond.notify_one();
    }
    static void pushBackTaskC(void(*func)())
    {
        if (func)
        {
            pushBackTask([func]() { func(); });
        }
    }
    static void start(const std::string& watchedFile, bool detach = true)
    {
        if (!m_isThreadRunning)
        {
            m_watchedFile = watchedFile;
            if (!fs::exists(m_watchedFile))
            {
                std::ofstream file(m_watchedFile);
                file.close();
            }
            m_lastWriteTime = fs::last_write_time(m_watchedFile);
            m_thread = std::thread(watcherThread);
            if (detach) m_thread.detach();
            m_isThreadRunning = true;
        }
    }
    static void stop()
    {
        {
            std::lock_guard<std::mutex> lock(m_taskArrMutex);
            m_stopThread = true;
        }
        m_taskArrCond.notify_one();
        if (m_thread.joinable())
            m_thread.join();
        m_isThreadRunning = false;
    }
};

#endif
