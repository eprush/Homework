#include "timer.hpp"
#include <random>
#include <iterator> 
#include <iomanip>
#include <algorithm>
#include <vector> 
#include <list>
#include <forward_list>
#include <array>
#include <deque>

int main()
{
    const int count = 100000;
    Timer t;
    long long vector_time = 0, deque_time = 0, array_time = 0, list_time = 0, forward_list_time = 0;
    for (auto j = 0U; j < 10; ++j)
    {
        std::mt19937 gen{ std::random_device()() };
        std::uniform_int_distribution<int> uid(0, count);
        std::vector<int> v(count);
        std::vector<int>::iterator begin = v.begin();
        std::vector<int>::iterator end = v.end();
        std::generate(begin, end, [&uid, &gen]() -> int
            { return uid(gen); }); //generate 100000 random number

        std::array<int, count> array;
        std::list<int>  list(begin, end);
        std::forward_list<int> forward_list(begin, end);
        std::deque<int> deque(begin, end);

        std::array<int, count>::iterator it_array = array.begin();

        while (begin != end)//copy vector
        {
            *it_array = *begin;
            ++begin, ++it_array;
        }

        t.resume();
        std::sort(v.begin(), v.begin() + 100000);
        t.pause();
        vector_time += t.delta_time();

        t.resume();
        list.sort();
        t.pause();
        list_time += t.delta_time();

        t.resume();
        std::sort(array.begin(), array.begin() + 100000);
        t.pause();
        array_time += t.delta_time();

        t.resume();
        forward_list.sort();
        t.pause();
        forward_list_time += t.delta_time();

        t.resume();
        std::sort(deque.begin(), deque.begin() + 100000);
        t.pause();
        deque_time += t.delta_time();
    }
   
    std::cout << "Average vector sorting time equals " << std::setw(2) << std::right << vector_time / 10.0 << " microseconds" << std::endl <<   
        "Average deque sorting time equals " << std::setw(2) << std::right << deque_time / 10.0 << " microseconds" << std::endl <<              
        "Average list sorting time equals " << std::setw(4) << std::right << list_time / 10.0 << " microseconds" << std::endl <<                
        "Average forward_list sorting time equals " << std::setw(2) << std::right << forward_list_time / 10.0 << " microseconds" << std::endl <<
        "Average array sorting time equals " << std::setw(2) << std::right << array_time / 10.0 << " microseconds" << std::endl;                

    //most often the vector is the fastest but sometimes the array is faster
	system("pause");
	return EXIT_SUCCESS;
}