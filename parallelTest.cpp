#include<iostream>
#include<thread>
#include<mutex>
#include<fstream>
#include<random>
#include<vector>
#include"timer.hpp"

std::string words[5] = {"hello", "to", "good", "day", "you"};

void makeDummies(){
    for(int i = 1; i <= 16; i++){
        std::string name = "texts/dummy" + std::to_string(i) + ".txt";
        std::fstream file(name, file.out);
        file << i << " Okay.";
        file.close();
    }
}

void fillDummies(int number){
    std::string name = "texts/dummy" + std::to_string(number) + ".txt";
    std::fstream file(name, file.out);
    std::string word = words[std::rand() % 5];
    word[0] -= 32;
    file << word;
    for(int i = 1; i < 100000; i++){
        word = words[std::rand() % 5];
        if(i % 5 == 0){
            word[0] -= 32;
            file << ". " << word;
        }
        else
            file << " " << word;
    }
    file << ".";
    file.close();
}

int main(){
    // makeDummies();
    std::vector<std::thread> threads;
    for(int i = 0; i < 16; i++)
        threads.emplace_back(std::thread(fillDummies, i + 1));
    for(std::thread& th : threads)
        th.join();
    return 0;
}