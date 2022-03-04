#include "header.hpp"

int main()
{
	std::vector <int> v_1(10);
	std::iota(std::begin(v_1), std::end(v_1), 1);
	std::default_random_engine dre(0);
	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(v_1));
	std::shuffle(std::begin(v_1), std::end(v_1), std::default_random_engine(0));
	std::sort(std::begin(v_1), std::end(v_1));
	v_1.erase(std::unique(std::begin(v_1), std::end(v_1)), std::end(v_1));

	int count = std::count_if(std::begin(v_1), std::end(v_1), [](auto element) { if (element % 2) return element; });
	std::cout << count << std::endl << "\n";

	auto result_pair = std::minmax_element(std::cbegin(v_1), std::cend(v_1));
	std::cout << *result_pair.first << " " << *result_pair.second << std::endl << "\n";

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
	std::cout << *simple_iterator << std::endl << "\n";

	std::vector<int> v_2;
	std::copy(std::cbegin(v_1), std::cend(v_1), std::back_inserter(v_2));
	std::transform(std::begin(v_1), std::end(v_1), std::begin(v_1), std::begin(v_1), [](auto rhs, auto lhs) {return rhs * lhs; });

	std::uniform_int_distribution <int> uid;
	std::generate(std::begin(v_2), std::end(v_2), [&uid, &dre]() {return uid(dre); });

	auto sum = 0U;
	std::for_each(std::cbegin(v_2), std::cend(v_2), [&sum](auto element) {sum += element; });
	std::cout << sum << std::endl << "\n";

	std::fill(std::begin(v_2), std::next(std::begin(v_2), 3), 1);

	std::vector<int> v_3;
	std::copy(std::cbegin(v_1), std::cend(v_1), std::back_inserter(v_3));
	std::transform(std::begin(v_3), std::end(v_3), std::begin(v_2), std::begin(v_3), [](auto rhs, auto lhs) {return rhs - lhs; });



	std::for_each(std::begin(v_3), std::end(v_3), [](auto element) {std::cout << element << std::endl; });
	system("pause");
	return EXIT_SUCCESS;
}