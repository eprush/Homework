#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <exception>


class Threads_guard
{
public:
	explicit Threads_guard(std::vector<std::thread>& threads) : m_threads(threads) {}
	Threads_guard(Threads_guard const&) = delete;
	Threads_guard operator=(Threads_guard const&) = delete;

	~Threads_guard() noexcept
	{
		try
		{
			for (auto i = 0U; i < m_threads.size(); ++i)
			{
				if (m_threads[i].joinable())
				{
					m_threads[i].join();
				}
			}
		}
		catch (std::exception& exception)
		{
			std::cerr << "Standard error: " << exception.what() << " in " << __LINE__ << " line" << std::endl;
		}
		catch (...)
		{
			std::cerr << "Some undefined error in " << __LINE__ << " line" << std::endl;
		}
	}
private:
	std::vector <std::thread>& m_threads;
};