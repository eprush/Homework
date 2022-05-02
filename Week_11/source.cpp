#include "game.hpp"

int main()
{
	try
	{
		asteroids::Game game;
		game.run();
	}
	catch(const std::logic_error& err)
	{
		std::cerr << err.what() << " in " << __LINE__ << " line" << std::endl;
	}
	catch(const std::exception& err)
	{
		std::cerr << err.what() << " in " << __LINE__ << " line" << std::endl;
	}
	catch (...)
	{
		std::cerr << "Some undefined error in " << __LINE__ << " line" << std::endl;
	}
	
	return EXIT_SUCCESS;
}