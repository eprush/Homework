#include <iostream>
#include <vector>
#include "hash.hpp"

int main()
{
	std::set <std::size_t> s;
	std::size_t step = 2000;
	const std::size_t count_of_points = 12;
	std::size_t count_of_collisions = 0;

	for (auto i = 0U; i < count_of_points; ++i)
	{
		std::mt19937 gen{ std::random_device()() };
		std::uniform_int_distribution<int> uid(0, step);
		std::vector<int> v(step);
		std::vector<int>::iterator begin = v.begin();
		std::vector<int>::iterator end = v.end();
		std::generate(begin, end, [&uid, &gen]()
			{ return uid(gen); });

		std::set <std::string> words = make_random_words(step);
		std::set<std::string>::iterator word = words.begin();

		for (; begin != end; ++begin, ++word)
		{
			std::size_t hash = hash_value(*begin, *word);
			if ((s.insert(hash)).second) {}
			else
			{
				++count_of_collisions;
			}
		}
		step += step;
		std::cout << count_of_collisions << std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}