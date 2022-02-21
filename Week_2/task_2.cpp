#include "timer.hpp"
#include <random>
#include <iterator> 
#include <algorithm>
#include <vector> 
#include <list>
#include <forward_list>
#include <array>
#include <deque>

int main()
{
    std::mt19937 gen{ std::random_device()() };
    std::uniform_int_distribution<int> uid(0, 100000);
    std::vector<int> v(100000);
    std::generate(v.begin(), v.begin() + 100000, [&uid, &gen]() -> int
        { return uid(gen); }); //generate 100000 random number

    std::vector<int>::iterator begin = v.begin();
    std::vector<int>::iterator end = v.end();
    std::array<int, 100000> array;
    std::list<int>  list(begin, end);
    std::forward_list<int> forward_list(begin, end);
    std::deque<int> deque(begin, end);

    std::array<int, 100000>::iterator it_array = array.begin();

    while (begin != end)//copy vector
    {
        *it_array = *begin;
        ++begin, ++it_array;
    }

    Timer t;
    t.resume();
    std::sort(v.begin(), v.begin() + 100000);
    t.pause();

    t.resume();
    list.sort();
    t.pause();

    t.resume();
    std::sort(array.begin(), array.begin() + 100000);
    t.pause();

    t.resume();
    forward_list.sort();
    t.pause();

    t.resume();
    std::sort(deque.begin(), deque.begin() + 100000);
    t.pause();
    //some results of measures
    //23 38 25 25 93 microseconds
    //22 15 23 21 80 microseconds
    //31 22 29 42 116  microseconds
    //26 17 27 18 117  microseconds
    //24 18 43 21 89  microseconds

    //average time
    std::cout << (23 + 22 +  31 +  26 + 24) / 5.0 << std::endl
        << (38 + 15 + 22 + 17 + 18) / 5.0 << std::endl
        << (25 + 23 + 29 + 27 + 43) / 5.0 << std::endl
        << (25 + 21 + 42 + 18 + 31) / 5.0 << std::endl
        << (93 + 80 + 116 + 117 + 89) / 5.0 << std::endl;
    //the fastest sort is sort in std::list

	system("pause");
	return EXIT_SUCCESS;
}