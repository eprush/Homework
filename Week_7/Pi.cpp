#include "Pi.hpp"

void Pi::count_in_circle(std::size_t points, std::size_t& result)
{
	std::hash<std::thread::id> hasher;
	std::default_random_engine engine(hasher(std::this_thread::get_id()));
	std::uniform_real_distribution <double> uid(0.0, 2.0);

	for (auto i = 0U; i < points; ++i)
	{
		if (in_circle(uid(engine), uid(engine)))
		{
			++result;
		}
	}
}

std::size_t Pi::count_in_circle(std::size_t points)
{
	std::hash<std::thread::id> hasher;
	std::default_random_engine engine(hasher(std::this_thread::get_id()));
	std::uniform_real_distribution <double> uid(0.0, 2.0);

	auto result = 0U;
	for (auto i = 0U; i < points; ++i)
	{
		if (in_circle(uid(engine), uid(engine)))
		{
			++result;
		}
	}
	return result;
}

double Pi::global_counter_Monte_Carlo(std::size_t points)
{
	const auto num_threads = std::thread::hardware_concurrency() != 0 ? std::thread::hardware_concurrency() : 2;

	std::vector < std::thread > threads(num_threads - 1);
	auto result = count_in_circle(points/num_threads);

	for (auto i = 0U; i < num_threads - 1; ++i)
	{
		std::packaged_task<void(std::size_t, std::size_t&)> task([this](auto points, auto& result){ Pi::count_in_circle(points, result); });
		threads[i] = std::thread(std::move(task), points / num_threads, std::ref(result));
		threads[i].join();
	}

	return 4.0 * result/points;
}

double Pi::par_Monte_Carlo(std::size_t points)
{
	const auto num_threads = std::thread::hardware_concurrency() != 0 ? std::thread::hardware_concurrency() : 2;

	std::vector < std::future < std::size_t > > futures(num_threads - 1);
	std::vector < std::thread > threads(num_threads - 1);

	for (auto i = 0U; i < num_threads - 1; ++i)
	{
		std::packaged_task<std::size_t(std::size_t)> task([this](auto points) {return Pi::count_in_circle(points); });
		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), points / num_threads);
	}

	auto result = count_in_circle(points / num_threads);
	for (auto i = 0U; i < num_threads - 1; ++i)
	{
		result += futures[i].get();
		threads[i].join();
	}

	return 4.0 * result / points;
}