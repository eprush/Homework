#include <iostream>
#include "words.hpp"
#include "9_hash.hpp"

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
	const std::size_t count_of_elements = 640000, step = 4000, count_of_function = 9;
	const auto words = make_random_words(count_of_elements);
	const auto end = words.end(), begin = words.begin();
	auto word = begin;

	Function function;
	for (auto i = 0U; i < count_of_function; word = begin)
	{
		std::set <std::size_t> for_hash;
		std::size_t count_of_collisions = 0;
		function = static_cast<Function>(i++);
		for (; word != end; ++word)
		{
			try
			{
				if (!(for_hash.insert(Hash(*word, function))).second) { ++count_of_collisions; }
			}
			catch (const std::exception& exception) { std::cerr << exception.what() << std::endl;}
			catch (...) { std::cerr << "Undefined error" << std::endl;}
		}
		std::cout << count_of_collisions << std::endl << "\n";
	}
	system("pause");
	return EXIT_SUCCESS;
}