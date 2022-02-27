#include <iostream>
#include "guide.hpp"

int main()
{
	const std::size_t sort = 0, vector = 1, phone = 2, name = 3;
	human_multi_index humans;

	humans.insert({ "Ivan",    850 });
	humans.insert({ "Michael",    4242 });
	humans.insert({ "Diana",  1245 });
	humans.insert({ "Anna", 9958 });
	humans.insert({ "Daria", 850 });

	const auto& sort_index = humans.get< sort >();
	auto sort_begin = sort_index.begin();
	const auto sort_end = sort_index.end();
	for (; sort_begin != sort_end; ++sort_begin)
		std::cout << sort_begin->name << std::endl;

	const auto& vector_index = humans.get < vector >();
	std::cout << vector_index.at(4).name << std::endl << "\n";

	const auto& name_index = humans.get< name >();
	auto name_iterator = name_index.find("Daria");
	if (name_iterator != name_index.end())
		std::cout << name_iterator->phone << std::endl << "\n";
	else
		std::cerr << "Search error" << std::endl;


	const auto& phone_index = humans.get < phone >();
	auto phone_iterator = phone_index.find(850);
	if (phone_iterator != phone_index.end())
		std::cout << phone_iterator->phone << std::endl << "\n";
	else
		std::cerr << "Search error" << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}