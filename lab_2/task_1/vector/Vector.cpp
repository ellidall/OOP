#include "ArithmeticMean.h"

int main()
{
	std::vector<double> numbers = ReadNumbers(std::cin);
	TransformVectorByArithmeticMean(numbers);
	PrintNumbers(numbers);
	std::cout << "Sorted vector: ";
	SortNumbers(numbers);
	PrintNumbers(numbers);
	return 0;
}