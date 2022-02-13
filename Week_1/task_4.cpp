#include "timer.hpp"

int main()
{
	double number = 2.5;
	Timer t;
	for (auto i = 0U; i < 1000000; ++i)
	{
		if (i % 1000 < 92)
		{
			t.resume();
		}
		else
		{
			t.pause();
		}
		number = std::pow(number, 1.9);
		number -= std::log10(number);
	}
	std::cout << number << std::endl;


	system("pause");
	return EXIT_SUCCESS;
}