#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include<iostream>
#include<chrono>

class Timer{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
    void Stop(){
        auto endTimePoinr = std::chrono::high_resolution_clock::now();

        int64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
        int64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoinr).time_since_epoch().count();

        int64_t duration = end - start;
        std::cout << duration << "us\n";
    }
public:
    Timer(){
        m_startTimePoint = std::chrono::high_resolution_clock::now();
    }
    ~Timer(){
        Stop();
    }
};

#endif