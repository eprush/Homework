#include "..\Week_3\timer.hpp"
#include "Pi.hpp"

int main()
{
	Pi pi;
	Timer t;

	t.resume();
	std::cout << pi.compute(Execution_policy::Seq) << " ";
	t.pause();
	std::cout << t.delta_time() << "\n";

	t.resume();
	std::cout << pi.compute(Execution_policy::Par) << " ";
	t.pause();
	std::cout << t.delta_time() << "\n";

	t.resume();
	std::cout << pi.compute(Execution_policy::Global) << " ";
	t.pause();
	std::cout << t.delta_time() << std::endl;
	//Output
	/*3.14056 49086
	3.14018 19891
	3.14108 19750*/
	
	//obviously, parallel algorithm works faster, because
	//we use a small count of threads

	system("pause");
	return EXIT_SUCCESS;
}