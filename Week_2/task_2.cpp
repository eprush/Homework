#include "timer.hpp"
#include <random>
#include <iterator> 
#include <vector> 
#include <list>
#include <forward_list>
#include <array>
#include <deque>

#define DEQUE std::deque<int>
#define LIST std::list<int>
#define FORWARD_LIST std::forward_list<int>
#define VECTOR std::vector<int>
#define ITERATOR ::iterator

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