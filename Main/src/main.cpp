#include <iostream>
#include <string>
#include "Headers/Vector.h"

int main(){
	//Vector<Vector<int>> V{{1,2},{3,4}};
	// Vector<std::string> St{4, "potato"};
	// Vector<Vector<int>> V{{1,3,4},{22,23,24},{145,253,134}};
	// std::cout << V.size() << std::endl;
	// std::cout << V.element(2).element(2) << std::endl;
	// std::cout << St.element(3) << std::endl;
	
	Vector<int> Test {5,3};
	std::cout << Test.element(0) << std::endl;


	return 0;
}