#include<iostream>
#include"threadPool.hpp"

void fun1(){
    std::cout << "Hello 1\n";
}

void fun2(){
    std::cout << "Hello 2\n";
}

void fun3(){
    std::cout << "Hello 3\n";
}

void fun4(){
    std::cout << "Hello 4\n";
}

void fun5(){
    std::cout << "Hello 5\n";
}

int main(){
    ThreadPool* pool = ThreadPool::create_pool(3);
    pool->add_job(fun1);
    pool->add_job(fun2);
    pool->add_job(fun3);
    pool->add_job(fun4);
    pool->add_job(fun5);
    delete pool;
    return 0;
}