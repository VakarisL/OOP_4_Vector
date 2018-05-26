#include <iostream>
#include <string>
#include <vector>
#include "Headers/Vector.h"

void display_sizes(const Vector<int>& nums1,
                   const Vector<int>& nums2,
                   const Vector<int>& nums3)
{
    std::cout << "nums1: " << nums1.size() 
              << " nums2: " << nums2.size()
              << " nums3: " << nums3.size() << '\n';
}

int main() {
	//Vector<Vector<int>> V{{1,2},{3,4}};
	// Vector<std::string> St{4, "potato"};
	// Vector<Vector<int>> V{{1,3,4},{22,23,24},{145,253,134}};
	// std::cout << V.size() << std::endl;
	// std::cout << V.element(2).element(2) << std::endl;
	// std::cout << St.element(3) << std::endl;

	// Vector<int> Test(5, 3);
	// std::cout << Test[0] << std::endl;

	// std::vector<int> test_original{5, 3};
	// std::cout << test_original[0] << std::endl;



	// ############# TESTS ######################
	//c-tors

	// Vector<int> empty;
	// std::cout << empty[0] << std::endl;

	//std::cout << "hi"<<std::endl;

	// std::vector<int> Temp(10, 2);
	// std::vector<std::vector<int>> Potato(10, Temp);
	// std::cout << Potato[0][0]; //<< " "<< Potato[5] << " "<< Potato[9]<< std::endl;

	// Vector<std::string> st(10,"Potato");
	// std::cout << st[0];// << " "<< Potato[5] << " "<< Potato[9]<< std::endl;

	// Vector<int> V{1,2,3,4,5};
	// std::cout << V[0] << " " << V[4	] << std::endl;

	// Vector<std::string> godpls{"potato", "potato2"};
	// std::cout <<godpls[0];
	// // Vector<std::vector<int>> Ve{{1,2},{3,4}};
	// std::cout << Ve[0][1] << " " << Ve[1][0] << std::endl;


	Vector<int> nums1 {3, 1, 4, 6, 5, 9};
	Vector<int> wildcard {2,1,4,6};
    Vector<int> nums2; 
    Vector<int> nums3;
 
    std::cout << "Initially:\n";
    display_sizes(nums1, nums2, nums3);
 
    // copy assignment copies data from nums1 to nums2
    nums2 = nums1;
    nums3= wildcard;
 
    std::cout << "After assigment:\n"; 
    display_sizes(nums1, nums2, nums3);
 
    // move assignment moves data from nums1 to nums3,
    // modifying both nums1 and nums3
    nums3 = std::move(nums1);
 
    std::cout << "After move assigment:\n"; 
    display_sizes(nums1, nums2, nums3);

	return 0;
}