#include "header.hpp"

int main()
{
	std::vector <int> vector(10);
	std::iota(std::begin(vector), std::end(vector), 1);

	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(vector));
	std::shuffle(std::begin(vector), std::end(vector), std::default_random_engine(0));
	std::sort(std::begin(vector), std::end(vector));
	vector.erase(std::unique(std::begin(vector), std::end(vector)), std::end(vector));
	int count  = std::count_if(std::begin(vector), std::end(vector), [](auto element) { if (element % 2) return element; });
	std::cout << count << std::endl << "\n";

	/*std::for_each(std::begin(vector), std::end(vector), [](auto element) {std::cout << element << std::endl; });*/



	system("pause");
	return EXIT_SUCCESS;
}