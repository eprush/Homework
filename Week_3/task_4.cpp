#include <iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;

struct Human
{
	std::string name;
	std::size_t phone;
};

using human_multi_index = multi_index_container <
	Human, indexed_by <
	ordered_non_unique <
	member < Human, std::string, &Human::name > >,
	random_access <>,
	hashed_non_unique <
	member < Human, std::size_t, &Human::phone > > ,
	hashed_non_unique <
	member < Human, std::string, &Human::name > >
	> >;

int main()
{
	const std::size_t sort_index = 0;
	const std::size_t vector_index = 1;
	const std::size_t phone_index = 2;
	const std::size_t name_index = 3;

	human_multi_index humans;

	humans.insert({ "Ivan",    850 });
	humans.insert({ "Michael",    4242 });
	humans.insert({ "Diana",  1245 });
	humans.insert({ "Anna", 9958 });
	humans.insert({ "Daria", 850 });

	const auto& ordered_index = humans.get< sort_index >();
	auto sort_begin = ordered_index.begin();
	const auto sort_end = ordered_index.end();
	for (; sort_begin != sort_end; ++sort_begin)
	{
		std::cout << sort_begin->name << std::endl;
	}
	std::cout << "\n";

	const auto& random_access_index = humans.get < vector_index >();
	std::cout << random_access_index[4].name << std::endl << "\n";

	const auto& hashed_name_index = humans.get< name_index >();
	auto name_iterator = hashed_name_index.find("Daria");
	std::cout << name_iterator->phone << std::endl << "\n";


	const auto& hashed_phone_index = humans.get < phone_index >();
	auto phone_iterator = hashed_phone_index.find(850);
	std::cout << phone_iterator->name << std::endl << "\n";

	system("pause");
	return EXIT_SUCCESS;
}