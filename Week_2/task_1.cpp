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
	std::cout << "The capacity of the vector changes by " << v.capacity() / capacity << std::endl;

	v.reserve(4);
	capacity = 4;
	for (auto i = 2; i < 10; ++i)
	{
		v.push_back(i);
		std::cout << static_cast <double> (v.capacity()) / capacity << std::endl;
		capacity = v.capacity();
	}

	system("pause");
	return EXIT_SUCCESS;
}