#include <vector> 
#include <iostream>

int main()
{
	std::vector<int> v {0};
	std::size_t capacity = v.capacity();
	for (auto i = 1; i < 5; ++i)
	{
		std::cout << "The capacity of the vector is equal " << capacity << " now" << std::endl;
		v.push_back(1);
		std::cout << "The capacity of the vector changes by " << static_cast<double>(v.capacity()) / capacity << std::endl;
		capacity = v.capacity();
	}
	//obviously, capacity increases by 1.5 times
	//because changing of capacity have means like 2 ; 1.5 ; 1.333 ; 1.5 on console

	v.reserve(6);
	capacity = 6;
	for (auto i = 5; i < 11; ++i)
	{
		v.push_back(i);
		std::cout << static_cast <double> (v.capacity()) / capacity << std::endl;
		capacity = v.capacity();
	}
	//after reserve capacity also increases by 1.5 times

	system("pause");
	return EXIT_SUCCESS;
}