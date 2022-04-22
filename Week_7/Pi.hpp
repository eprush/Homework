#pragma once
#include <vector>
#include <numeric>
#include <future>
#include <thread>
#include <mutex>
#include <random>

enum class Execution_policy
{
	Seq,
	Par,
	Global
};

class Pi
{
public:
	double compute(const Execution_policy& policy, std::size_t points = 1000000)
	{
		if(policy == Execution_policy::Seq)
			return Monte_Carlo(points);
		else if(policy == Execution_policy::Par)
			return par_Monte_Carlo(points);
		return global_counter_Monte_Carlo(points);
	}

private:
	bool in_circle(double x, double y, double radius = 1.0)
	{
		return ((x - radius) * (x - radius) + (y - radius) * (y - radius) <= radius*radius);
	}

	void count_in_circle(std::size_t points, std::size_t& result);
	std::size_t count_in_circle(std::size_t points);

private:
	double Monte_Carlo(std::size_t points)
	{
		return 4.0 * count_in_circle(points) / points;
	}

	double par_Monte_Carlo(std::size_t points);

	double global_counter_Monte_Carlo(std::size_t points);

private:
	mutable std::mutex m_mutex;
};