#include<iostream>
#include<thread>
#include<mutex>
#include<functional>

std::mutex lock;

void testFun(){
    std::unique_lock<std::mutex> guard(lock, std::defer_lock);
    std::cout << guard.owns_lock() << "\n";
    guard.lock();
    std::cout << guard.owns_lock() << "\n";
}

int main(){
    testFun();
    return 0;
}