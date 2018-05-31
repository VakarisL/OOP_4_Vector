#include <iostream>
#include <string>
#include <vector>
#include "Headers/Vector.h"
#include "Headers/Timer.h"


int main() {
	Timer t;
	Vector<int> v1;
	for(int i=1; i<= 10000; ++i){
		v1.push_back(i);
	}
	std::cout << 10000 << " irasu irasymo i Vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();
	Vector<int> v2;
	for(int i=1; i<= 100000; ++i){
		v2.push_back(i);
	}
	std::cout << 100000 << " irasu irasymo i Vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();
	Vector<int> v3;
	for(int i=1; i<= 1000000; ++i){
		v3.push_back(i);
	}
	std::cout << 1000000 << " irasu irasymo i Vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();
	Vector<int> v4;
	for(int i=1; i<= 10000000; ++i){
		v4.push_back(i);
	}
	std::cout << 10000000 << " irasu irasymo i Vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();
	Vector<int> v5;
	for(int i=1; i<= 100000000; ++i){
		v5.push_back(i);
	}
	std::cout << 100000000 << " irasu irasymo i Vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();          
	std::vector<int> V1;
	for(int i=1; i<= 10000; ++i){
		V1.push_back(i);
	}
	std::cout << 10000 << " irasu irasymo i std::vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();
	std::vector<int> V2;
	for(int i=1; i<= 100000; ++i){
		V2.push_back(i);
	}
	std::cout << 100000 << " irasu irasymo i std::vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();
	std::vector<int> V3;
	for(int i=1; i<= 1000000; ++i){
		V3.push_back(i);
	}
	std::cout << 1000000 << " irasu irasymo i std::vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();
	std::vector<int> V4;
	for(int i=1; i<= 10000000; ++i){
		V4.push_back(i);
	}
	std::cout << 10000000 << " irasu irasymo i std::vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	
	t.reset();
	std::vector<int> V5;
	for(int i=1; i<= 100000000; ++i){
		V5.push_back(i);
	}
	std::cout << 100000000 << " irasu irasymo i std::vector konteineri (sekundemis): "
	          << t.elapsed() << std::endl;
	return 0;
}