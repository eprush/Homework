#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include "words.hpp"
#include "hash_templates.hpp"

int main()
{
	const std::size_t count_of_elements = 640000, step = 1000;
	std::mt19937 gen{ std::random_device()() };
	std::uniform_int_distribution<int> uid(0, count_of_elements);
	std::vector<int> v(count_of_elements);
	auto begin = v.begin(), end = v.end();
	std::generate(begin, end, [&uid, &gen]()
		{ return uid(gen); });

	auto words = make_random_words(count_of_elements);
	auto word = words.begin();
	std::set <std::size_t> s;
	std::size_t count_of_collisions = 0;

	std::ofstream outf("for_graphic.xls");
	if (!outf)
	{
		std::cerr << "for_graphic.xlsx could not be opened for writing" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	for (auto i=0U; begin != end; ++begin)
	{
		if (!(s.insert(hash_value(*begin, *(word++)))).second) {++count_of_collisions;}
		if (!(++i % step)) { outf << count_of_collisions << std::endl; }
	}

	system("pause");
	return EXIT_SUCCESS;
}