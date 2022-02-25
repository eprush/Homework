#include <iostream>
#include "words.hpp"
#include "9_hash.hpp"

int main()
{
	const std::size_t count_of_elements = 320000;
	const std::size_t step = 40000;
	const std::size_t length = 10;
	const std::set <std::string> words = make_random_words(count_of_elements, length);
	std::set <std::string>::const_iterator end = words.end();
	std::set <std::string>::const_iterator begin = words.begin();

	const std::size_t count_of_function = 9;
	Function function;
	std::size_t hash = 0;
	for (auto i = 0U; i < count_of_function; )
	{
		std::set <std::size_t> for_hash;
		std::set<std::string>::iterator word = begin;
		std::size_t count_of_collisions = 0;
		function = static_cast<Function>(i);
		std::cout << ++i << std::endl;
		for (auto elements_now=0U; word != end; ++word)
		{
			hash = Hash(*word, length, function);
			if ((for_hash.insert(hash)).second) {}
			else
			{
				++count_of_collisions;
			}

			if ((++elements_now) % step == 0) //for graphic
			{
				std::cout << "Count of elements equals " << elements_now << std::endl <<
					"Count of collisions equals " << count_of_collisions << std::endl <<
					std::endl;
			}
		}
		std::cout << "Count of elements equals " << count_of_elements << std::endl <<
			"Count of collisions equals " << count_of_collisions << std::endl <<
			std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}