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
    std::uniform_int_distribution<int> uid(0, 100);
    std::vector<int> v(100);
    std::generate(v.begin(), v.begin() + 100, [&uid, &gen]() -> int
        { return uid(gen); }); //generate 100 random number

    std::array<int, 100> array;
    std::list<int>  list(100);
    std::forward_list<int> forward_list(100);
    std::deque<int> deque(100);

    std::deque<int>::iterator it_d = deque.begin();
    std::forward_list<int>::iterator it_f = forward_list.begin();
    std::list<int>::iterator it_l = list.begin();
    std::vector<int>::iterator it_v = v.begin();
    std::array<int, 100>::iterator it_array = array.begin();

    while (it_v != v.end())//copy vector
    {
        *it_d = *it_v;
        *it_f = *it_v;
        *it_l = *it_v;
        *it_array = *it_v;
        ++it_v, ++it_d, ++it_f, ++it_l, ++it_array;
    }

    Timer t;
    t.resume();
    std::sort(v.begin(), v.begin() + 100);
    t.pause();

    t.resume();
    list.sort();
    t.pause();

    t.resume();
    std::sort(array.begin(), array.begin() + 100);
    t.pause();

    t.resume();
    forward_list.sort();
    t.pause();

    t.resume();
    std::sort(deque.begin(), deque.begin() + 100);
    t.pause();
    //some results of measures
    //26 25 49 29 85  microseconds
    //28 31 45 23 112  microseconds
    //25 14 21 16 79  microseconds
    //26 22 25 20 83  microseconds
    //34 16 36 26 88  microseconds

    //average time
    std::cout << (26 + 28 + 25 + 26 + 34) / 5.0 << std::endl <<
        (25 + 31 + 14 + 22 + 16) / 5.0 << std::endl <<
        (49 + 45 + 21 + 25 + 36) / 5.0 << std::endl <<
        (29 + 23 + 16 + 20 + 26) / 5.0 << std::endl <<
        (85 + 112 + 79 + 83 + 88) / 5.0 << std::endl;
    //the fastest sort is sort in std::list

	system("pause");
	return EXIT_SUCCESS;
}