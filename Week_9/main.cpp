#include "interprocess_chat.hpp"

int main()
{
    std::string user_name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, user_name);
    system("pause");

    try
    {
        Chat(user_name).run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Undefined error " << std::endl;
    }

    return EXIT_SUCCESS;
}