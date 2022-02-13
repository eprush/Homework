#include <vector> 
#include <iostream>

int main()
{
	std::vector<int> v;
	v.push_back(0);
	std::size_t capacity = v.capacity();
	std::cout << "The capacity of the vector is equal " << capacity << " now" <<  std::endl;
	while (capacity == v.capacity())
	{
		v.push_back(1);
	}
	std::cout << "The capacity of the vector changes by " << v.capacity() / capacity << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}