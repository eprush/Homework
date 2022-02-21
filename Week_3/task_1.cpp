#include "timer.hpp"
#include <random>
#include <iterator> 
#include <algorithm>
#include <set>
#include <vector>

int main()
{
    std::mt19937 gen{ std::random_device()() };
    std::uniform_int_distribution<int> uid(0, 100000);
    std::vector<int> v(100000);
    std::vector<int>::iterator begin = v.begin();
    std::vector<int>::iterator end = v.end();
    std::generate(begin, end, [&uid, &gen]() -> int
        { return uid(gen); });

    std::set<int> set(begin, end);

	system("pause");
	return EXIT_SUCCESS;
}