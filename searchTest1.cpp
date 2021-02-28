#include<iostream>
#include<thread>
#include<vector>
#include"timer.hpp"

void search(const std::vector<int>& data){
    for(int i : data){
        if(i == 8)
            std::cout << "found\n";
    }
}

int main(){
    std::vector<std::vector<int>> vectorArray;
    for(int i = 0; i < 8; i++)
        vectorArray.emplace_back(std::vector<int>(0xfffff, i));
    vectorArray.back().back() = 8;
    {
        Timer timer;
        for(std::vector<int>& v : vectorArray)
            search(v);
    }
    std::vector<std::thread> threads;
    {
        Timer timer;
        for(int i = 0; i < 8; i++)
            threads.emplace_back(std::thread(search, vectorArray[i]));
        for(std::thread& th : threads)
            th.join();
    }
    return 0;
}