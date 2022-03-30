#include "C:\Users\ASUS\OneDrive\Рабочий стол\Homework\Week_3\timer.hpp"
#include <random>
#include <execution>
#include <fstream>

void measure_for_each(std::size_t count_of_measures)
{
	Timer t;
	std::ofstream outf("measures_1.xlsx");
	if (!outf)
	{
		throw std::ios_base::failure("File could not be opened for writing");
	}
	auto add{ [](auto& element)
	{ ++element; }
	};

	std::vector<int> v(100000);
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine dre(static_cast<std::size_t> (seed));
	std::uniform_int_distribution uid(0, 100000);
	std::generate(std::begin(v), std::end(v), [&uid, &dre]() {return uid(dre); });
	for (auto i = 0U; i < count_of_measures; ++i)
	{
		t.resume();
		std::for_each(std::begin(v), std::end(v), add);
		t.pause();
		outf << t.delta_time();

		t.resume();
		std::for_each(std::execution::par, std::begin(v), std::end(v), add);
		t.pause();
		outf << t.delta_time() << std::endl;
	}
}

void measure_partial_sum(std::size_t count_of_measures)
{

}

void measure_transform(std::size_t count_of_measures)
{

}

int main()
{
	const std::size_t count = 10;
	try
	{
		measure_for_each(count);
		measure_partial_sum(count);
		measure_transform(count);
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