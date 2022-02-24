#include <iostream>
#include <vector>
#include "hash.hpp"

int main()
{
	std::set <std::size_t> s;
	const std::size_t count_of_elements = 20000;
	const std::size_t step = 2000;
	std::size_t count_of_collisions = 0;

	std::mt19937 gen{ std::random_device()() };
	std::uniform_int_distribution<int> uid(0, count_of_elements);
	std::vector<int> v(count_of_elements);
	std::vector<int>::iterator begin = v.begin();
	std::vector<int>::iterator end = v.end();
	std::generate(begin, end, [&uid, &gen]()
		{ return uid(gen); });

	std::set <std::string> words = make_random_words(count_of_elements);
	std::set<std::string>::iterator word = words.begin();

	for (; begin != end; ++begin, ++word)
	{
		std::size_t hash = hash_value(*begin, *word);
		if ((s.insert(hash)).second) {}
		else
		{
			++count_of_collisions;
		}

		if ((count_of_elements - (end - begin)) % step == 0) //for graphic
		{
			std::cout << "Count of elements equals " << count_of_elements - (end - begin) << std::endl <<
				"Count of collisions equals " << count_of_collisions << std::endl <<
				std::endl;
		}
	}
	std::cout << count_of_collisions << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}