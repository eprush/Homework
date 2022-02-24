#include <iostream>
#include <vector>
#include <iterator>
#include "hash.hpp"

int main()
{
	std::set <std::size_t> s;
	const std::size_t count_of_elements = 20000;
	const std::size_t step = 2000;

	std::set <std::string> words = make_random_words(count_of_elements);
	std::set<std::string>::iterator word = words.begin();
	std::size_t hash = 0;

	system("pause");
	return EXIT_SUCCESS;
}