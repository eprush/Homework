#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <Windows.h>

void show_currency_symbol(const std::string& locale_name)
{
	std::cout <<
		std::use_facet < std::moneypunct < char, false > >(
			std::locale(locale_name)).curr_symbol() << std::endl;
}

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	std::string euro = "";
	std::getline(std::cin, euro);
	std::istringstream in (euro);
	in.imbue(std::locale("en_US.UTF-8"));
	in  >> std::get_money(euro, true);

	std::cout.imbue(std::locale("ru_RU.UTF-8"));
	std::cout << std::put_money(euro, true) << " ";
	show_currency_symbol("ru_RU.UTF-8");


	system("pause");
	return EXIT_SUCCESS;
}