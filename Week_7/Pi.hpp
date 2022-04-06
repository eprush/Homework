#pragma once
#include <vector>
#include <numeric>
#include <future>
#include <thread>
#include <random>

class Pi
{
public:
	double compute(bool is_seq = true, std::size_t points = 1000000)
	{
		if(is_seq)
			return Monte_Carlo(points);
		return par_Monte_Carlo(points);
	}

private:
	bool in_circle(double x, double y, double radius = 1.0)
	{
		return ((x - radius) * (x - radius) + (y - radius) * (y - radius) <= radius*radius);
	}

	std::size_t count_in_circle(std::size_t points);

private:
	double Monte_Carlo(std::size_t points)
	{
		return 4.0 * count_in_circle(points) / points;
	}

	double par_Monte_Carlo(std::size_t points);
};