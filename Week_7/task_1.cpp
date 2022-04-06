#include "..\Week_3\timer.hpp"
#include "Pi.hpp"

int main()
{
	Pi pi;
	Timer t;
	t.resume();
	std::cout << pi.compute() << " ";
	t.pause();
	std::cout << t.delta_time() << "\n";
	t.resume();
	std::cout << pi.compute(false) << " ";
	t.pause();
	std::cout << t.delta_time() << std::endl;
	//Output
	//3.14264 226345
	//3.14426 51504
	
	//obviously, parallel algorithm works faster, because
	//we use a small count of threads

	system("pause");
	return EXIT_SUCCESS;
}