#include "C:\Users\ASUS\OneDrive\Рабочий стол\Homework\Week_3\timer.hpp"
#include <random>
#include <vector>
#include <array>
#include <execution>
#include <fstream>

void random_fill(std::vector<int>& v)
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine dre(static_cast<std::size_t> (seed));
	std::uniform_int_distribution uid(0, static_cast<int>(std::size(v)));
	std::generate(std::begin(v), std::end(v), [&uid, &dre]() {return uid(dre); });
}

void measure_for_each(std::size_t start = 1000, std::size_t end = 100000)
{
	std::ofstream out_1("measures_1.xls");
	std::ofstream out_2("measures_1_par.xls");
	if (!out_1 and !out_2)
	{
		throw std::ios_base::failure("File could not be opened for writing");
	}
	auto add{ [](auto& element)
	{ ++element; }
	};

	Timer t;
	const std::size_t block_size = (end - start)/1000 >= 1 ? (end - start) / 1000 : 1;
	std::vector<int> v(end);
	random_fill(v);
	for (auto i = 0U; i < 1000; ++i)
	{
		t.resume();
		std::for_each(std::begin(v), std::next(std::begin(v), start + i * block_size), add);
		t.pause();
		out_1 << t.delta_time() << std::endl;

		t.resume();
		std::for_each(std::execution::par, std::begin(v), std::next(std::begin(v), start + i * block_size), add);
		t.pause();
		out_2 << t.delta_time() << std::endl;
	}
}

void measure_partial_sum(std::size_t start = 1000, std::size_t end = 100000)
{
	std::ofstream out_1("measures_2.xls");
	std::ofstream out_2("measures_2_par.xls");
	if (!out_1 and !out_2)
	{
		throw std::ios_base::failure("File could not be opened for writing");
	}

	Timer t;
	const std::size_t block_size = (end - start) / 1000 >= 1 ? (end - start) / 1000 : 1;
	std::array<int, 100000> collector;
	auto begin = std::begin(collector);
	std::vector<int> v(end);
	random_fill(v);
	for (auto i = 0U; i < 1000; ++i)
	{
		t.resume();
		std::partial_sum(
			std::begin(v), std::next(std::begin(v), start + i*block_size), begin);
		t.pause();
		out_1 << t.delta_time() << std::endl;

		t.resume();
		std::inclusive_scan(std::execution::par,
			std::begin(v), std::next(std::begin(v), start + i * block_size), begin);
		t.pause();
		out_2 << t.delta_time() << std::endl;
	}
}

void measure_transform(std::size_t start = 1000, std::size_t end = 100000)
{
	std::ofstream out_1("measures_3.xls");
	std::ofstream out_2("measures_3_par.xls");
	if (!out_1 and !out_2)
	{
		throw std::ios_base::failure("File could not be opened for writing");
	}

	Timer t;
	const std::size_t block_size = (end - start) / 1000 >= 1 ? (end - start) / 1000 : 1;
	std::vector<int> v_1(end);
	std::vector<int> v_2(end);
	auto begin = std::begin(v_2);
	random_fill(v_1);
	random_fill(v_2);
	int result = 0;
	for (auto i = 0U; i < 1000; ++i)
	{
		t.resume();
		result = std::inner_product(
			std::begin(v_1), std::next(std::begin(v_1), start + i * block_size), begin , 0);
		t.pause();
		out_1 << t.delta_time() << std::endl;

		t.resume();
		result = std::transform_reduce(std::execution::par,
			std::begin(v_1), std::next(std::begin(v_1), start + i * block_size), begin, 0);
		t.pause();
		out_2 << t.delta_time() << std::endl;
	}
}

int main()
{
	try
	{
		measure_for_each();
		measure_partial_sum();
		measure_transform();
	}
	catch (std::ios_base::failure& e)
	{
		std::cerr << e.what() << " in " << __LINE__ << " line" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << " in " << __LINE__ << " line" << std::endl;
	}
	catch (...)
	{
		std::cerr << "Undefined error in " << __LINE__ << " line" << std::endl;
	}


	system("pause");
	return EXIT_SUCCESS;
}