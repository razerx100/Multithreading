#include<iostream>
#include<future>
#include<thread>

void function(std::promise<std::string> data){
    data.set_value("Promise kept.");
}

int main(){
    std::promise<std::string> promises;
    std::future<std::string> kept = promises.get_future();

    std::thread th(function, std::move(promises));

    std::cout << kept.get();
    th.join();

    return 0;
}