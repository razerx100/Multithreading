#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>
#include<execution>
#include"timer.hpp"

void print(const std::string& str){
    std::cout << str << " ";
}
void pr(const int& x){
    std::cout << x;
}
int main(){
    std::string sentences[] = {
        "Hello,",
        "I am Saikat.",
        "This the most basic concurrency test."
    };

    {
        Timer timer;
        for(int i = 0; i < 3; i++)
            print(sentences[i]);
    }
    std::vector<std::thread> threads;
    {
        for(int i = 0; i < 3; i++)
            threads.emplace_back(std::thread(print, sentences[i]));
        Timer timer;
        for(std::thread& th : threads)
            th.join();
    }
    std::vector<int> data_set = {9, 1, 5, 1, 5, 7, 2, 12, 10, 0};
    {
        Timer timer;
        std::sort(data_set.begin(), data_set.end());
    }
    {
        Timer timer;
        std::sort(std::execution::par_unseq, data_set.begin(), data_set.end());
    }
    return 0;
}

// Compiler flags ltbb and pthread required