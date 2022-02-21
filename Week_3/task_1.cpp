#include "timer.hpp"
#include <random>
#include <iterator> 
#include <algorithm>
#include <set>
#include <vector>

int main()
{
    Timer t;
    long long vector_time = 0, set_time = 0;
    for (auto j = 0U; j < 5; ++j)
    {
        std::mt19937 gen{ std::random_device()() };
        std::uniform_int_distribution<int> uid(0, 100000);
        std::vector<int> v(100000);
        std::vector<int>::iterator begin = v.begin();
        std::vector<int>::iterator end = v.end();
        std::generate(begin, end, [&uid, &gen]() -> int
            { return uid(gen); });

        std::set<int> s;

        t.resume();
        for (auto i = 0U; i < 100000; ++i)
        {
            s.insert(v[i]);
        }
        t.pause();
        set_time += t.delta_time();

        t.resume();
        std::sort(begin, end);
        t.pause();
        vector_time += t.delta_time();
    }

    std::cout << "Average vector sorting time equals " << vector_time/5.0 << " microseconds" << std::endl << //approximately 5500 microseconds
        "Average set sorting time equals " << set_time /5.0 << " microseconds" << std::endl; //more than 25000 microseconds, in other words in 5 times more than vector

	system("pause");
	return EXIT_SUCCESS;
}