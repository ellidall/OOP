#include "ArithmeticMean.h"

const std::string SEPARATOR = ", ";
const size_t MAX_DIGIT_AMOUNT_AFTER_DECIMAL_POINT = 3;

std::vector<double> ReadNumbers(std::istream& input)
{
	std::vector<double> numbers(std::istream_iterator<double>(input), (std::istream_iterator<double>()));
	return numbers;
}

void PrintNumbers(const std::vector<double>& numbers)
{
	for (int i = 0; i < numbers.size(); i++)
	{
		std::cout << std::fixed << std::setprecision(MAX_DIGIT_AMOUNT_AFTER_DECIMAL_POINT) << numbers[i];
		if (i != numbers.size() - 1)
		{
			std::cout << SEPARATOR;
		}
	}
	std::cout << "\n";
}

void TransformVectorByArithmeticMean(std::vector<double>& numbers)
{
	size_t positiveNumbersAmount = 0;
	double positiveNumbersSum = std::accumulate(numbers.begin(), numbers.end(), 0.0,
		[&positiveNumbersAmount](double sum, double num) {
			if (num > 0.0)
			{
				++positiveNumbersAmount;
				return sum + num;
			}
			else
			{
				return sum;
			}
		});
	double arithmeticMean = positiveNumbersSum / positiveNumbersAmount;

	std::transform(numbers.begin(), numbers.end(), numbers.begin(),
		[arithmeticMean](double x) { return x + arithmeticMean; });
}