#include <iostream>
#include <vector>
#include <numeric>
#include <future>
#include <thread>
#include <random>
#include <cmath>

bool in_circle(double x, double y, double radius = 1.0)
{
	return (std::sqrt((x - radius)*(x - radius) + (y - radius)*(y - radius)) <= radius);
}

double count_in_circle(std::size_t points, std::size_t a = 1)
{
	const int count = 100000000;
	std::mt19937 engine(0);
	std::uniform_int_distribution <int> uid(0, 2 * count);
	auto k = 0U;
	for (auto i = 0U; i < points; ++i)
	{
		if (in_circle(uid(engine)  / static_cast<double>(points) / a, uid(engine)/ a / static_cast<double>(points)))
		{
			++k;
		}
	}
	return static_cast<double>(k);
}

double Monte_Carlo(std::size_t points)
{
	return 4 * count_in_circle(points) / points;
}

double par_Monte_Carlo(std::size_t points)
{
	const std::size_t num_threads = std::thread::hardware_concurrency() != 0 ? std::thread::hardware_concurrency() : 2;

	std::vector < std::future < double > > futures(num_threads - 1);
	std::vector < std::thread > threads(num_threads - 1);

	for (auto i = 0U; i < (num_threads - 1); ++i)
	{
		std::packaged_task<double (std::size_t, std::size_t)> task{count_in_circle};
		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), points / num_threads, num_threads);
	}
	auto result = count_in_circle(points / num_threads, num_threads);
	for (auto i = 0U; i < num_threads - 1; ++i)
	{
		result += futures[i].get();
		threads[i].join();
	}

	return 4 * result / points;
}

int main()
{
	const std::size_t count_of_points = 100000000;
	std::cout << Monte_Carlo(count_of_points) << "\n";
	std::cout << par_Monte_Carlo(count_of_points) << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}