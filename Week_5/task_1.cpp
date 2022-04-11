#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <Windows.h>


int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	std::cout << "Enter a cash count in dollars ";
	long double money = 0.0;
	const double exchange_rate = 83.43;
	std::cin >> std::get_money(money);


	std::cout << "Entered count equals ";
	std::cout.imbue(std::locale("eu_US.utf8"));
	std::cout << std::showbase << std::put_money(money) << std::endl;

	money *= exchange_rate;
	std::cout << "Cash count in rubles ";
	std::cout.imbue(std::locale("ru_RU.utf8"));
	std::cout << std::showbase << std::put_money(money) << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}