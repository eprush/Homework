#include "C:\Users\ASUS\OneDrive\Рабочий стол\Homework\Week_3\timer.hpp"
#include "Threads_guard.hpp"
#include <numeric>
#include <random>
#include <future>
#include <fstream>

template < typename Iterator, typename T >
struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, std::size_t num_threads, T init)
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

	return init;
}

void measure(std::vector<int>& v, std::size_t start = 16, std::size_t count = 500)
{
	Timer t;
	std::ofstream outf("measures.xls");
	if (!outf)
	{
		throw std::ios_base::failure("File could not be opened for writing");
	}

	int result = 0;
	for (auto i = 0U; i < count; ++i)
	{
		t.resume();
		result = parallel_accumulate(std::begin(v), std::end(v), start + i, 0);
		t.pause();
		outf << t.delta_time() << std::endl;
	}
}

std::size_t optimize(std::size_t start = 16, std::size_t count = 500)
{
	std::ifstream inf("measures.xls");
	inf.seekg(0, std::ios::beg);

	if (!inf)
	{
		throw std::ios::failure("File could not be opened for reading");
	}

	double longer_time = 0.0, less_time = 0.0;
	count += start;
	inf >> longer_time;
	inf >> less_time;
	while (longer_time - less_time >= 1.0 and start <= count)
	{
		++start;
		longer_time = less_time;
		inf >> less_time;
	}

	return start;
}

int main()
{
	std::vector < int > v(100);
	std::iota(std::begin(v), std::end(v), 1);

	try 
	{ 
		measure(v); 
		std::cout << "The most optimal count of currents equals " << optimize() << std::endl;//19
	}
	catch (std::ios_base::failure& exception)
	{
		std::cerr << "Standard exception: " << exception.what() << " in " << __LINE__ << " line" <<  std::endl;
	}
	catch (std::exception& exception)
	{
		std::cerr << "Standard exception: " << exception.what() << " in " << __LINE__ << " line" << std::endl;
	}
	catch (...)
	{
		std::cerr << "Undefined error in " << __LINE__ << std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}