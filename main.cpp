#include <iostream>
#include <map>
#include "reserve_allocator.h"
#include "MyList.h"

long fact(int x){
    if (!x)
        return 1;
    else
        return x * fact(x - 1);
}

int main(){

    //создание  простого map и заполнение значениями
    auto simpleMap = std::map<int, long>{};
    for(auto i = 0; i < 10; ++i)
        simpleMap.emplace(i, fact(i));

    //создание map с кастомным аллокатором
	auto customAllocatorMap = std::map<int, long, std::less<int>, reserve_allocator<std::pair<int, long>, 10>>{};
 	for (auto i = 0; i < 10; i++)
        customAllocatorMap.emplace(i, fact(i));
    //вывод значений
    //for(auto i : customAllocatorMap)
    //    std::cout<<i.first<<" "<<i.second<<std::endl;


    //создание кастомного списка
    auto simpleList = MyList<int>{};
    for(auto i = 0; i < 10; ++i)
        simpleList.append(i);

    //создание кастомного списка с кастомным аллокатором
    auto customAllocatorList = MyList<int, reserve_allocator<int, 10>>{};
    for(auto i = 0; i < 10; ++i)
        customAllocatorList.append(i);
    //вывод значений
    for(auto i : customAllocatorList)
	   std::cout<<i<<" ";

    std::cout<<std::endl;

	return 0;
};
