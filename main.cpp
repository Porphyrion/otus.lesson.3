#include <iostream>
#include "MyList.h"

int main(){

	MyList<int> IntList{1,2,3,4,5,6,7,8,9};

	for (auto i : IntList){
		std::cout<<i;
	}

	return 0;
}