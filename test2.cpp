#include<iostream>
#include<thread>
#include<atomic>
int main(){
    int var = 0;
    auto f = [&var]{var++;};
    std::thread th1(f), th2(f), th3(f);
    th1.join();
    th2.join();
    th3.join();
    std::cout << var << " ";
    std::atomic<int> varA = 0;
    auto ff = [&varA]{varA++;};
    std::thread th4(ff), th5(ff), th6(ff);
    th4.join();
    th5.join();
    th6.join();
    std::cout << var << " ";
    return 0;
}