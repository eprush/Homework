#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include "words.hpp"
#include "hash_templates.hpp"

std::set < std::string > make_random_words(std::size_t N, std::size_t length = 10) // length = 10 - good enough
{
	std::uniform_int_distribution <> letter(97, 122);
	std::default_random_engine e(static_cast <std::size_t> (
		std::chrono::system_clock::now().time_since_epoch().count()));

	std::set < std::string > words;

	for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
		for (auto& c : s)
			c = letter(e);

	return words;
}

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