#include <iostream>
#include <vector>
#include <iterator>
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
	std::set <std::size_t> s;
	const std::size_t count_of_elements = 320000;
	const std::size_t step = 40000;

	std::mt19937 gen{ std::random_device()() };
	std::uniform_int_distribution<int> uid(0, count_of_elements);
	std::vector<int> v(count_of_elements);
	std::vector<int>::iterator begin = v.begin();
	std::vector<int>::iterator end = v.end();
	std::generate(begin, end, [&uid, &gen]()
		{ return uid(gen); });

	std::set <std::string> words = make_random_words(count_of_elements);
	std::set<std::string>::iterator word = words.begin();
	std::size_t hash = 0;
	std::size_t count_of_collisions = 0;

	for (; begin != end; ++begin, ++word)
	{
		hash = hash_value(*begin, *word);
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
	std::cout << "Count of elements equals " << count_of_elements - (end - begin) << std::endl <<
		"Count of collisions equals " << count_of_collisions << std::endl <<
		std::endl;

	system("pause");
	return EXIT_SUCCESS;
}