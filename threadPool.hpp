#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__
#include<functional>
#include<queue>
#include<vector>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<atomic>

class ThreadPool {
public:
    static ThreadPool* create_pool();
    static ThreadPool* create_pool(int threadNumber);
    void add_job(std::function<void()> job);
    void shutdown();
    void wait_till_tasks_finished();

    ~ThreadPool();
private:
    static ThreadPool *sInstance;
    std::queue<std::function<void()>> mJobQueue;
    std::vector<std::thread> mThreadPool;
    std::mutex mMutex;
    std::condition_variable mCVar;
    std::atomic<bool> mJobsDone;
    std::vector<bool> mIsSleeping;
    bool stopped;

    ThreadPool();
    ThreadPool(int number);

    void work_thread(int index);
};
#endif