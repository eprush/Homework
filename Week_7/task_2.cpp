#include "Threads_guard.hpp"
#include "C:\Users\ASUS\OneDrive\Рабочий стол\Homework\Week_3\timer.hpp"
#include <numeric>
#include <random>
#include <future>

template < typename Iterator, typename T >
struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template < typename Iterator, typename T >
void parallel_accumulate(Iterator first, Iterator last, std::size_t num_threads, T init)
//void for comfort call in measure()
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	const std::size_t block_size = length / num_threads;

	std::vector < std::future < T > > futures(num_threads - 1);
	std::vector < std::thread >		  threads(num_threads - 1);
	Threads_guard guard(threads);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		std::packaged_task < T(Iterator, Iterator) > task{ accumulate_block < Iterator, T >() };

		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), block_start, block_end);

		block_start = block_end;
	}

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		init += futures[i].get();
	}
	init += accumulate_block < Iterator, T >()(block_start, last);
}

std::size_t optimize()
{



	return EXIT_SUCCESS;
}

void measure(std::vector<int>& v, std::size_t start = 16, std::size_t count = 500)
{
	Timer t;
	for (auto i = 0U; i < count; ++i)
	{
		t.resume();
		parallel_accumulate(std::begin(v), std::end(v), start + i, 0);//comfort call
		t.pause();
		std::cout << start + i << "  " <<  t.delta_time() << std::endl;
	}
}

int main(int argc, char** argv)
{
	std::vector < int > v(100);
	std::iota(std::begin(v), std::end(v), 1);

	measure(v);

	std::cout << "The most optimal count of currents equals " << optimize() << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}