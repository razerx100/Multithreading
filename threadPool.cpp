#include"threadPool.hpp"

ThreadPool *ThreadPool::sInstance = nullptr;

ThreadPool* ThreadPool::create_pool(){
    if(!sInstance)
        sInstance = new ThreadPool();
    return sInstance;
}

ThreadPool* ThreadPool::create_pool(int threadNumber){
    if(!sInstance)
        sInstance = new ThreadPool(threadNumber);
    return sInstance;
}

void ThreadPool::add_job(std::function<void()> job){
    std::unique_lock<std::mutex> lock(mMutex, std::adopt_lock);
    mJobQueue.push(job);
    lock.unlock();
    mCVar.notify_one();
}

void ThreadPool::shutdown(){
    wait_till_tasks_finished();
    mJobsDone = true;
    mCVar.notify_all();
    for(std::thread& th : mThreadPool)
        th.join();
    mThreadPool.clear();
    mIsSleeping.clear();
    stopped = true;
}

ThreadPool::ThreadPool()
        : mJobsDone(false), stopped(false) {

    int availableThreads = std::thread::hardware_concurrency();
    mIsSleeping = std::vector<bool>(availableThreads, true);

    for(int i = 0; i < availableThreads; i++)
        mThreadPool.emplace_back(std::thread(&ThreadPool::work_thread, this, i));
}

ThreadPool::ThreadPool(int number)
        : mJobsDone(false), stopped(false) {

    int availableThreads = std::thread::hardware_concurrency();
    int threadsToCreate = (availableThreads < number) ? availableThreads : number;
    mIsSleeping = std::vector<bool>(threadsToCreate, true);

    for(int i = 0; i < threadsToCreate; i++)
        mThreadPool.emplace_back(std::thread(&ThreadPool::work_thread, this, i));
}

ThreadPool::~ThreadPool(){
    if(!stopped)
        shutdown();
}

void ThreadPool::work_thread(int index){
    while(true){
        std::unique_lock<std::mutex> lock(mMutex, std::adopt_lock);
        mCVar.wait(lock, [&]{ return !mJobQueue.empty() or mJobsDone; });
        if(mJobsDone)
            break;
        else {
            std::function<void()> job = mJobQueue.front();
            mJobQueue.pop();
            lock.unlock();

            mIsSleeping[index] = false;
            job();
            mIsSleeping[index] = true;
        }
    }
}

void ThreadPool::wait_till_tasks_finished(){
    while(std::find_if(mIsSleeping.begin(), mIsSleeping.end(), [](bool value){ return !value; }) != mIsSleeping.end()){}
}