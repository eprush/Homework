#include "header.hpp"

int main()
{
	std::vector <int> vector(10);
	auto begin = std::begin(vector), end = std::end(vector);
	std::iota(begin, end, 1);


	system("pause");
	return EXIT_SUCCESS;
}