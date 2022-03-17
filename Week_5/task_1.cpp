#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <Windows.h>


int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	double money = 0.0;
	std::cin >> money;

	std::string euro;
	std::getline(std::cin, euro);
	std::istringstream in(euro);
	in.imbue(std::locale("en_US.UTF-8"));
	in  >> std::get_money(euro, true);

	std::cout.imbue(std::locale("ru_RU.UTF-8"));
	std::cout <<  std::put_money(money) << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}