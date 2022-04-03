#include <iostream>
#include <locale>
#include <string>
#include <regex>

int main()
{
    std::cout.imbue(std::locale("eu_US.UTF-8"));
    std::string str("srhdfhh_...2002 pavlovich.er@phystech.edu@@mail.ru@@ 2022_ dest..royer@gmail.com 2345yjhgf ");
    const std::regex regex(R"(\w+\.{1}\w+@(\w+\.\w+))");
    std::smatch match;

    while (std::regex_search(str, match, regex))
    {
        for (auto i = 0U; i < std::size(match); i += 2)
        {
            std::cout << "Email adress: " << match[i] << " Domain name: " << match[i + 1] << std::endl;
        }
        str = match.suffix().str();
    }
    //pavlovich.er@phystech.edu - yes
    //dest..royer@gmail.com - no, because two points

	system("pause");
	return EXIT_SUCCESS;
}