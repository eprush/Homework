#include <iostream>
#include <numeric>
#include <future>


template <class Iterator, class Func>
void par_for_each(Iterator begin, Iterator end, Func lambda)
{
	const std::size_t length = std::distance(begin, end);
	const std::size_t max_length = 16;
	if (length <= max_length)
	{
		std::for_each(begin, end, lambda);
	}
	else
	{
		Iterator middle = begin;
		std::advance(middle, length / 2);

		auto first_half_result = std::async(
			std::launch::async, par_for_each<Iterator, Func>, begin, middle, lambda);
	
		par_for_each (middle, end, lambda);
		first_half_result.get();
	}
}

//int main()
//{
//	std::vector<int> v(100);
//	std::iota(std::begin(v), std::end(v), 1);
//
//	par_for_each(std::begin(v), std::end(v), [](auto element) {std::cout << element << std::endl; });
//
//	system("pause");
//	return EXIT_SUCCESS;
//}