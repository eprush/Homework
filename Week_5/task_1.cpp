#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <Windows.h>


int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	std::stringstream in;
	std::string str = "";
	in << str << std::endl;
	std::cout << "Enter a cash count in dollars ";
	in.imbue(std::locale("en_US.UTF-8"));
	long double money = 0.0;
	std::cin >> std::get_money(money);


	std::cout << "Entered count equals ";
	std::cout.imbue(std::locale("eu_US.utf8"));
	std::cout << std::showbase << std::put_money(money) << std::endl;

	money *= 83.43;
	std::cout << "Cash count in rubles ";
	std::cout.imbue(std::locale("ru_RU.utf8"));
	std::cout << std::showbase << std::put_money(money) << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}