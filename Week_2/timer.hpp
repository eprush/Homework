#pragma once
#include <iostream>
#include <chrono>

class Timer
{
private:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using microseconds_t = std::chrono::microseconds;

public:
	explicit Timer() :m_begin(clock_t::now()), m_time(0), m_turned_on(false) {}
	~Timer() noexcept
	{
		pause();
	}

	void pause()
	{
		if (m_turned_on)
		{
			microseconds_t delta_time(std::chrono::duration_cast <microseconds_t> (clock_t::now() - m_begin).count());
			m_time += delta_time;
			print_time(delta_time);
		}
	}
	void resume()
	{
		if (!m_turned_on)
		{
			m_begin = clock_t::now();
		}
	}

	const microseconds_t& time() const noexcept
	{
		return m_time;
	}
	double delta_time(time_point_t& delta_time)
	{
		return std::chrono::duration_cast <microseconds_t> (delta_time).count();
	}

private:
	void print_time(const microseconds_t& delta_time)
	{
		std::cout << "The working time of this section of the code is equal " << delta_time.count() << " microseconds" << std::endl;
		std::cout << "The working time of all code is equal " << m_time.count() << " microseconds" << std::endl;
	}

private:
	time_point_t m_begin;
	microseconds_t m_time;
	bool m_turned_on;
};
