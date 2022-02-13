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
    VECTOR v(100);
    std::generate(v.begin(), v.begin() + 100, [&uid, &gen]() -> int
        { return uid(gen); }); //generate 100 random number

    std::array<int, 100> array;
    LIST  list(100);
    FORWARD_LIST forward_list(100);
    DEQUE deque(100);

    DEQUE ITERATOR it_d = deque.begin();
    FORWARD_LIST ITERATOR it_f = forward_list.begin();
    LIST ITERATOR it_l = list.begin();
    VECTOR ITERATOR it_v = v.begin();
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

	system("pause");
	return EXIT_SUCCESS;
}