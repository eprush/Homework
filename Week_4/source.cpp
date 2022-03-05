#include "header.hpp"

int main()
{
	//1
	std::vector <int> v_1(10);
	std::iota(std::begin(v_1), std::end(v_1), 1);

	//2
	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(v_1));

	//3
	std::default_random_engine dre(0);
	std::shuffle(std::begin(v_1), std::end(v_1), std::default_random_engine(0));

	//4
	std::sort(std::begin(v_1), std::end(v_1));
	v_1.erase(std::unique(std::begin(v_1), std::end(v_1)), std::end(v_1));

	//5
	int count = std::count_if(std::begin(v_1), std::end(v_1), [](auto element) { return element * (element%2); });
	std::cout << count << std::endl << "\n";

	//6
	auto result_pair = std::minmax_element(std::cbegin(v_1), std::cend(v_1));
	std::cout << *result_pair.first << " " << *result_pair.second << std::endl << "\n";

	//7
	auto simple = [](auto element)
	{
		for (auto i = 0U; i < std::sqrt(element); ++i)
		{
			if (!(element % i))
				return false;
		}
		return true;
	};
	auto simple_iterator = std::find_if(std::cbegin(v_1), std::cend(v_1), simple);
	if (simple_iterator != std::end(v_1)) { std::cout << *simple_iterator << std::endl; }

	//8
	std::transform(std::begin(v_1), std::end(v_1), std::begin(v_1),std::begin(v_1), [](auto lhs, auto rhs) {return rhs * lhs; });

	//9
	std::vector<int> v_2(std::size(v_1));
	std::uniform_int_distribution <int> uid (-100000, 100000);
	std::generate(std::begin(v_2), std::end(v_2), [&uid, &dre]() {return uid(dre); });

	//10
	std::cout << std::accumulate(std::cbegin(v_2), std::cend(v_2), 0) << std::endl << "\n";

	//11
	std::fill_n(std::begin(v_2), 3, 1);

	//13
	std::vector<int> v_3;
	std::transform(std::begin(v_1), std::end(v_1), std::begin(v_2), std::back_inserter(v_3), [](auto lhs, auto rhs) {return lhs - rhs; });

	//14
	std::replace_if(std::begin(v_3), std::end(v_3), [](auto element) {return (element < 0); }, 0);
	v_3.erase(std::remove(std::begin(v_3), std::end(v_3), 0), std::end(v_3));

	//15
	std::reverse(std::begin(v_3), std::end(v_3));

	//16
	std::partial_sort(std::begin(v_3), std::next(std::begin(v_3), 2), std::end(v_3));
	std::for_each(std::begin(v_3), std::next(std::begin(v_3), 3), [](auto element) {std::cout << element << std::endl; });

	//17
	std::sort(std::begin(v_1), std::end(v_1));
	std::sort(std::begin(v_2), std::end(v_2));

	//18
	std::vector<int> v_4;
	std::merge(std::begin(v_1), std::end(v_1), std::begin(v_2), std::end(v_2), std::back_inserter(v_4));

	//19
	auto range = std::equal_range(std::begin(v_4), std::end(v_4), 1);
	std::cout << std::distance(range.first, range.second) << std::endl << "\n";

	/*std::copy(std::begin(v_1), std::end(v_1), std::ostream_iterator <std::vector<int>>(std::cout));
	std::cout << "n";
	std::copy(std::begin(v_2), std::end(v_2), std::ostream_iterator <std::vector<int>>(std::cout));
	std::cout << "n";
	std::copy(std::begin(v_3), std::end(v_3), std::ostream_iterator <std::vector<int>>(std::cout));
	std::cout << "n";
	std::copy(std::begin(v_4), std::end(v_4), std::ostream_iterator <std::vector<int>>(std::cout));*/
	system("pause");
	return EXIT_SUCCESS;
}
