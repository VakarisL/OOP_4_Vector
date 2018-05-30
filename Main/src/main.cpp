#include <iostream>
#include <string>
#include <vector>
#include "Headers/Vector.h"

void display_sizes(const Vector<int>& nums1,
                   const Vector<int>& nums2,
                   const Vector<int>& nums3) {
	std::cout << "nums1: " << nums1.size()
	          << " nums2: " << nums2.size()
	          << " nums3: " << nums3.size() << '\n';
}

int main() {
	Vector<int> nums1 {3, 1, 4, 6, 5, 9};
	Vector<int> wildcard {2, 1, 4, 6};
	Vector<int> nums2;
	Vector<int> nums3;

	std::cout << "Initially:\n";
	display_sizes(nums1, nums2, nums3);

	// copy assignment copies data from nums1 to nums2
	nums2 = nums1;
	nums3 = wildcard;

	std::cout << "After assigment:\n";
	display_sizes(nums1, nums2, nums3);

	// move assignment moves data from nums1 to nums3,
	// modifying both nums1 and nums3
	nums3 = std::move(nums1);

	std::cout << "After move assigment:\n";
	display_sizes(nums1, nums2, nums3);

	nums2.clear();

	std::cout << "After clear():\n";
	display_sizes(nums1, nums2, nums3);

	nums2.assign({8, 6, 8, 9, 5, 3, 1});

	std::cout << "After assign():\n";
	display_sizes(nums1, nums2, nums3);

	std::cout << "at: " << nums2.at(4) << std::endl;
	std::cout << "Front: " << nums2.front() << std::endl;
	std::cout << "Back: " << nums2.back() << std::endl;
	std::cout << "begin: " << nums2.begin() << " value: " << *nums2.begin() <<  std::endl;
	std::cout << "end: " << nums2.end() << " value: " << *nums2.end() << std::endl;
	std::cout << "Reverse begin/end: ";
	for (auto i = nums2.rbegin(); i != nums2.rend(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	std::cout << "nums1 empty? " << nums1.empty() << " Nums2 empty? " << nums2.empty() << std::endl;
	std::cout << "Max size: " << nums2.max_size() << std::endl;

	std::cout << "reserve():\n";
	std::cout << "nums2 capacity before: " << nums2.capacity() << std::endl;
	nums2.reserve(15);
	std::cout << "nums2 capacity after: " << nums2.capacity() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}
	nums2.shrink_to_fit();
	std::cout << "nums2 capacity after shrink_to_fit: " << nums2.capacity() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}

	nums2.insert(nums2.begin() + 2, {10, 1, 3, 4});
	std::cout << "nums2 capacity after insert: " << nums2.capacity() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}

	nums2.emplace(nums2.begin() + 1, 99);
	std::cout << "nums2 capacity after emplace: " << nums2.capacity() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}


	nums2.erase(nums2.begin() + 1, nums2.begin() + 3);
	std::cout << "nums2 size after erase: " << nums2.size() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}

	nums2.push_back(16);
	std::cout << "nums2 size after push_back: " << nums2.size() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}

	nums2.emplace_back(17);
	std::cout << "nums2 size after emplace_back: " << nums2.size() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}

	nums2.pop_back();
	std::cout << "nums2 size after pop_back: " << nums2.size() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}

	nums2.resize(15, 7);
	std::cout << "nums2 size after resize: " << nums2.size() << std::endl;
	for (int i = 0; i < nums2.size(); ++i) {
		std::cout << nums2[i] << std::endl;
	}

	return 0;
}