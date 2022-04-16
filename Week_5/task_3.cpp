#include <iostream>
#include <string>
#include <regex>
#include <numeric>

int main()
{
    std::string str("sr admin@mail.mipt.ru hdfhh_...2002 pavlovich.er@phystech.edu@@mail.ru@@ 2022_ dest..royer@gmail.com 2345yjhgf i.s.m.mipt@yandex.ru ");
    const std::regex regex( R"((\w+\.?)+\w+@((\w+\.?)+\w+))" );
    
    std::for_each(std::sregex_iterator(std::begin(str), std::end(str), regex), std::sregex_iterator(), [](auto i)
        {
            std::cout << i.str() << ' ' << "Domain name is " << i[2].str() << std::endl;
        });


    //pavlovich.er@phystech.edu - yes
    //dest..royer@gmail.com - no, because two points

	system("pause");
	return EXIT_SUCCESS;
}