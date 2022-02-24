#include <iostream>
#include <array>
#include <iterator>
#include "hash.hpp"

int main()
{
	const std::size_t count_of_elements = 20000;
	const std::size_t step = 2000;
	std::set <std::string> words = make_random_words(count_of_elements);
	std::set <std::string>::const_iterator end = words.end();
	std::set <std::string>::const_iterator begin = words.begin();

	const std::size_t count_of_function = 9;
	using function = std::size_t(std::string, std::size_t);
	std::array<function, count_of_function> function_array
	{ RSHash , JSHash , PJWHash , ELFHash , BKDRHash , SDBMHash , DJBHash , DEKHash , APHash };
	const std::size_t length = 10;

	for (auto i = 0; i < count_of_function; ++i)
	{
		std::set <std::size_t> for_hash;
		std::set<std::string>::iterator word = begin;
		std::size_t count_of_collisions = 0;
		std::size_t hash = 0;

		for (auto elements_now=0U; word != end; ++word)
		{
			hash = function_array[i](*word,length) % count_of_elements;
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