#include<iostream>
#include<mutex>
#include<thread>

std::mutex mutexx;
int x = 1;

void print(const std::string& thread_name){
    std::cout << thread_name << ++x <<" accessing.\n";
}

void add(){
    std::lock_guard<std::mutex> guard(mutexx);
    x += 2;
}

void mul(){
    std::lock_guard<std::mutex> guard(mutexx);
    x *= 4;
}

void printX(){
    std::cout << x << "\n";
}

void reset(){
    std::lock_guard<std::mutex> guard(mutexx);
    x = 1;
}

int main(){
    std::thread th1(add);
    std::thread th2(mul);
    std::thread th3(printX);
    std::thread th4(reset);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    return 0;
}