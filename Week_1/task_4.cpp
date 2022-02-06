#include <iostream>
#include <chrono>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	Timer():m_begin(clock_t::now()){}
	~Timer() noexcept
	{
		count += 1;
		time = std::chrono::duration_cast <std::chrono::microseconds> (clock_t::now() - m_begin).count();
		std::cout << "The working time of " << count << "'th section of the code equals " << time << " microseconds" << std::endl;
	}
private:
	time_point_t m_begin;
	static long long time;
	static size_t count;
};
size_t Timer::count = 0;
long long Timer::time = 0;

int main()
{
	{
		Timer t;
		double number = 2.0;
		for (auto i = 0U; i < 100000000; ++i)
		{
			number = std::pow(number, 2.5) * 1.01;
			number += number;
		}
		std::cout << number << std::endl;
	}

	//Your code could be here. We will not measure it
	//...

	{
		Timer t;
		double number = 123456789;
		while (number > 1)
		{
			number = std::sqrt(number);
		}
		std::cout << number << std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}