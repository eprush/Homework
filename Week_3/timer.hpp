#pragma once
#include <iostream>
#include <chrono>
#include <exception>

class Timer
{
private:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using microseconds_t = std::chrono::microseconds;

public:
	Timer() :m_begin(clock_t::now()), m_time(0), m_delta(0), m_turned_on(false) {}
	~Timer() noexcept
	{
		try
		{
			pause();
		}
		catch (...)
		{
			std::cerr << "Undefined error in " << __LINE__ << " line" << std::endl;
		}
	}

	void pause()
	{
		if (m_turned_on)
		{
			m_delta = std::chrono::duration_cast <microseconds_t> (clock_t::now() - m_begin).count();
			m_turned_on = false;
			microseconds_t delta_time(m_delta);
			m_time += delta_time;
		}
	}

	void resume()
	{
		if (!m_turned_on)
		{
			m_begin = clock_t::now();
			m_turned_on = true;
		}
	}

	const auto& time() const noexcept
	{
		return m_time;
	}
	long long delta_time() const noexcept
	{
		return m_delta;
	}

private:
	time_point_t m_begin;
	microseconds_t m_time;
	long long m_delta;
	bool m_turned_on;
};