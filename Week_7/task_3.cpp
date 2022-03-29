#include <iostream>
#include <numeric>
#include <vector>
#include <future>
#include <algorithm>


template <class Iterator, class Func>
constexpr Func par_for_each(Iterator begin, Iterator end, Func lambda)
{
	const std::size_t length = std::distance(begin, end);
	const std::size_t max_length = 16;
	if (length <= max_length)
	{
		return std::for_each(begin, end, lambda);
	}
	else
	{
		Iterator middle = begin;
		std::advance(middle, length / 2);

		std::future < Func > first_half_result =
			std::async(std::launch::async, par_for_each < Iterator, Func >, begin, middle, lambda);
		Func second_half_result = par_for_each (middle, end, Func());
		Func from_first_half = first_half_result.get();
		return lambda;
	}
}

int main()
{
	std::vector<int> v(100);
	std::iota(std::begin(v), std::end(v), 1);

	par_for_each(std::begin(v), std::end(v), [](auto element) {std::cout << element << std::endl; });

	system("pause");
	return EXIT_SUCCESS;
}