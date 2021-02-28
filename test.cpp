#include<iostream>
#include<vector>
#include<list>
#include<functional>
#include<unordered_map>
#include<algorithm>

int main(){
    std::list<std::pair<std::string, std::string>> map;
    map.push_back({"Saikat", "Mondol"});
    map.emplace_back(std::make_pair("razerx", "100"));
    std::vector<std::reference_wrapper<std::pair<std::string, std::string>>> v(map.begin(), map.end());
    std::sort(v.begin(), v.end(), [](
        std::pair<std::string, std::string> item1, std::pair<std::string, std::string> item2){
            return item1.first[0] > item2.first[0];
        });
    map.front().second = "Hello";
    v.front().get().second = "Not hello";
    for(std::pair<std::string, std::string> p : map)
        std::cout << p.first << " " << p.second << " ";
    return 0;
}