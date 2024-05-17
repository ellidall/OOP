#include "GeneratePrimeNumbers.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound > MAX_UPPER_BOUND)
	{
		throw std::invalid_argument("Upper bound is greater than the maximum allowed value");
	}

	std::vector<bool> sieve(upperBound + 1, true);
	std::set<int> primeNumbers;

	for (size_t i = 2; i <= upperBound; ++i)
	{
		if (sieve[i])
		{
			primeNumbers.emplace_hint(primeNumbers.cend(), i);
			// напистать тест для проверки в debug
			// ускорить цикл в два раза
			for (size_t j = i * i; j <= upperBound; j += i)
			{
				sieve[j] = false;
			}
		}
	}

	return primeNumbers;
}

void PrintSet(std::ostream& output, const std::set<int>& set)
{
	for (int element : set)
	{
		output << element << " ";
	}
	output << std::endl;
}