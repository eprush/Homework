#include "header.hpp"

int main()
{
	std::vector <int> vector(10);
	std::iota(std::begin(vector), std::end(vector), 1);

	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(vector));
	std::for_each(std::begin(vector), std::end(vector), [](auto element) {std::cout << element << std::endl; });



	system("pause");
	return EXIT_SUCCESS;
}