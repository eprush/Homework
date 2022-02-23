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
    const std::size_t count = 100000;
    const std::size_t measures = 10;
    Timer t;
    long long vector_time = 0;
    long long deque_time = 0;
    long long array_time = 0;
    long long list_time = 0;
    long long forward_list_time = 0;
    for (auto j = 0U; j < measures; ++j)
    {
        std::mt19937 gen{ std::random_device()() };
        std::uniform_int_distribution<int> uid(0, count);
        std::array<int, count> array;
        auto begin = array.begin();
        auto end = array.end();
        std::generate(begin, end, [&uid, &gen]()
            { return uid(gen); }); //generate 100000 random number

        std::vector<int> v(begin, end);
        std::list<int>  list(begin, end);
        std::forward_list<int> forward_list(begin, end);
        std::deque<int> deque(begin, end);

        t.resume();
        std::sort(v.begin(), v.end());
        t.pause();
        vector_time += t.delta_time();

        t.resume();
        list.sort();
        t.pause();
        list_time += t.delta_time();

        t.resume();
        std::sort(begin, end);
        t.pause();
        array_time += t.delta_time();

        t.resume();
        forward_list.sort();
        t.pause();
        forward_list_time += t.delta_time();

        t.resume();
        std::sort(deque.begin(), deque.end());
        t.pause();
        deque_time += t.delta_time();
    }
   
    std::cout << "Average vector sorting time equals " << std::setw(2) << std::right << vector_time / measures << " microseconds" << std::endl <<   
        "Average deque sorting time equals " << std::setw(2) << std::right << deque_time / measures << " microseconds" << std::endl <<              
        "Average list sorting time equals " << std::setw(4) << std::right << list_time / measures << " microseconds" << std::endl <<                
        "Average forward_list sorting time equals " << std::setw(2) << std::right << forward_list_time / measures << " microseconds" << std::endl <<
        "Average array sorting time equals " << std::setw(2) << std::right << array_time / measures << " microseconds" << std::endl;                

    //most often the vector is the fastest but sometimes the array is faster
	system("pause");
	return EXIT_SUCCESS;
}