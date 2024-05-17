#include "GeneratePrimeNumbers.h"
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>

struct Args
{
	int upperBound;

	Args(int upperBound): upperBound(upperBound) {}
};

Args ParseArgs(int argc, char* argv[])
{
	if (!argv || argc != 2)
	{
		throw std::invalid_argument("Error: invalid arguments\nUsage: primeNumbers.exe <upperBound>");
	}

	return std::stoi(argv[1]);
}

int main(int argc, char* argv[])
{
	boost::timer time;
	time.restart();

	try
	{
		Args args = ParseArgs(argc, argv);
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(args.upperBound);
		std::cout << "Prime numbers amount: " << primeNumbers.size() << std::endl;
		std::cout << "Time to build a set: " << time.elapsed() << '\n';
		PrintSet(std::cout, primeNumbers);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}