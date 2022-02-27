#pragma once
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
	member < Human, std::size_t, &Human::phone > >,
	hashed_non_unique <
	member < Human, std::string, &Human::name > >
	> >;