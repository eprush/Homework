#include "Threads_guard.hpp"
#include <iostream>
#include <numeric>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>


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
		const auto num_threads = std::thread::hardware_concurrency() != 0 ? std::thread::hardware_concurrency() : 2;
		const auto block_size = length / num_threads;
		std::vector < std::thread >		  threads(num_threads - 1);
		Threads_guard guard(threads);
		auto block_start = begin;
		for (auto i = 0U; i < num_threads - 1; ++i)
		{
			Iterator block_end = block_start;
			std::advance(block_end, block_size);

			std::packaged_task < void(Iterator, Iterator, Func) > task{par_for_each < Iterator, Func >};
			threads[i] = std::thread(std::move(task), block_start, block_end, lambda);

			block_start = block_end;
		}
		par_for_each (block_start, end, lambda);
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