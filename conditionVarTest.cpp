#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>

std::condition_variable cv;
std::mutex key;
bool ready = false, processed = false;
std::string data;

void process_data(){
    std::unique_lock<std::mutex> lock(key, std::adopt_lock);
    cv.wait(lock, [](){return ready;});

    data.append("Working thread, worked. ");

    processed = true;

    lock.unlock();
    cv.notify_one();
}

int main(){
    std::thread th(process_data);

    data = "Main thread. ";
    {
        std::unique_lock<std::mutex> lock(key);
        ready = true;
    }

    cv.notify_one();

    {
        std::unique_lock<std::mutex> lock(key);
        cv.wait(lock, [](){return processed;});
    }

    std::cout << "\n" << data;

    th.join();
    return 0;
}