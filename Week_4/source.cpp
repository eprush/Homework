#include "header.hpp"

int main()
{
	std::vector <int> vector(10);
	std::iota(std::begin(vector), std::end(vector), 1);
	std::default_random_engine dre(0);
	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(vector));
	std::shuffle(std::begin(vector), std::end(vector), std::default_random_engine(0));
	std::sort(std::begin(vector), std::end(vector));
	vector.erase(std::unique(std::begin(vector), std::end(vector)), std::end(vector));

	int count  = std::count_if(std::begin(vector), std::end(vector), [](auto element) { if (element % 2) return element; });
	std::cout << count << std::endl << "\n";

	auto result_pair = std::minmax_element(std::cbegin(vector), std::cend(vector));
	std::cout << *result_pair.first  << " " << *result_pair.second << std::endl;

	auto simple = [](auto element)
	{
		for (auto i = 0U; i < std::sqrt(element); ++i)
		{
			if (!(element % i))
				return false;
		}
		return true;
	};
	auto simple_iterator = std::find_if(std::cbegin(vector), std::cend(vector), simple);
	std::cout << *simple_iterator << std::endl;

	std::vector<int> v;
	std::copy(std::cbegin(vector), std::cend(vector), std::back_inserter(v));
	std::transform(std::begin(vector), std::end(vector), std::begin(v), std::begin(vector), [](auto rhs, auto lhs) {return rhs * lhs; });

	std::uniform_int_distribution <int> uid;
	std::generate(std::begin(v), std::end(v), [&uid, &dre]() {return uid(dre); });

	auto sum = 0U;
	std::for_each(std::cbegin(v), std::cend(v), [&sum](auto element) {sum += element; });
	std::cout << sum << std::endl;

	/*std::for_each(std::begin(v), std::end(v), [](auto element) {std::cout << element << std::endl; });*/



	system("pause");
	return EXIT_SUCCESS;
}