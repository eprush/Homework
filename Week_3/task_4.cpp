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
	hashed_non_unique <
	member < Human, std::string, &Human::name > >,
	hashed_non_unique <
	member < Human, std::size_t, &Human::phone	> >,
	random_access <>,
	ordered_non_unique <
	member < Human, std::size_t, &Human::phone > > > >;

int main()
{

	const std::size_t vector_index = 2;

	human_multi_index humans;

	humans.insert({ "Ivan",    850 });
	humans.insert({ "Michael",    4242 });
	humans.insert({ "Diana",  1245 });
	humans.insert({ "Anna", 9958 });

	auto& hashed_phone_index = humans.get < 1 >();
	std::cout << hashed_phone_index.count(4) << std::endl;

	auto iterator = hashed_phone_index.find(850); 
	hashed_phone_index.modify(iterator, [](Human& human) { human.name = "Egor"; });

	std::cout << hashed_phone_index.find(0)->name << std::endl;
	std::cout << std::endl;

	const auto& ordered_phone_index = humans.get < 3 >();
	auto begin = ordered_phone_index.lower_bound(4);
	auto end = ordered_phone_index.upper_bound(4);

	for (; begin != end; ++begin)
	{
		std::cout << begin->name << std::endl;
	}
	std::cout << std::endl;

	const auto& random_access_index = humans.get < 2 >();
	std::cout << random_access_index[0].name << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}