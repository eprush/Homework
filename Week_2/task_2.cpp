#include "timer.hpp"
#include <array>
#include <random> 
#include <algorithm> 
#include <iterator> 
#include <vector> 
#include <list>
#include <cstddef>

int main()
{
    std::mt19937 gen{ std::random_device()() };
    std::uniform_int_distribution<int> uid(0, 100);
    std::vector<int> v(100);
    std::generate(v.begin(), v.begin() + 100, [&uid, &gen]() -> int
        { return uid(gen); });

    std::array<int, 100> my_array;
    std::list
    std::vector<int>::iterator it_v = v.begin(), std::array<int,100>::iterator it_array = my_array.begin();


	system("pause");
	return EXIT_SUCCESS;
}