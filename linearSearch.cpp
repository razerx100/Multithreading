#include<iostream>
#include<vector>
#include<thread>
#include"timer.hpp"
#include<mutex>

std::mutex key;

void find8(int offset, const std::vector<int>& data){
    std::lock_guard<std::mutex> guard(key);
    for(int i = 0 + offset; i < data.size(); i += 8){
        if(data[i] == 8)
            std::cout << "Found\n";
    }
}

int main(){
    int x = 0;
    std::vector<int> v(0xfffff, 1);
    v.back() = 8;
    {
        Timer timer;
        for(int i : v){
            if(i == 8)
                std::cout << "Found\n";
        }
    }
    std::vector<std::thread> threads;
    {
        Timer timer;
        for(int i = 0; i < 8; i++)
            threads.emplace_back(std::thread(find8, i, v));
        for(std::thread& th : threads)
            th.join();
    }
    return 0;
}