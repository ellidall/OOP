#include "ChangeRadix.h"

const size_t MAX_RADIX_VALUE = 36;
const size_t MIN_RADIX_VALUE = 2;

int CharToInt(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		return 10 + ch - 'A';
	}
	else if (ch >= 'a' && ch <= 'z')
	{
		return 10 + ch - 'a';
	}
	else
	{
		return -1;
	}
}

char IntToChar(int number)
{
	if (number >= 0 && number <= 9)
	{
		return static_cast<char>('0' + number);
	}
	else if (number >= 10 && number <= 35)
	{
		return static_cast<char>('A' + number - 10);
	}
	else
	{
		return '?';
	}
}

int CalculateUsingRadix(int numericValue, int number,
	int radix, bool& wasError)
{
	if (number < 0)
	{
		if (numericValue >= (INT_MIN - number) / radix)
		{
			wasError = false;
			return numericValue * radix + number;
		}
		else
		{
			wasError = true;
			return numericValue;
		}
	}
	if (numericValue <= (INT_MAX - number) / radix)
	{
		wasError = false;
		return numericValue * radix + number;
	}
	else
	{
		wasError = true;
		return numericValue;
	}
}

int StringToInt(const std::string& str, int sourceRadix, bool& wasError)
{
	int numericValue = 0;
	int startIndex = 0;
	bool isNegative = false;

	if (str.empty())
	{
		wasError = true;
		return numericValue;
	}
	if (str[0] == '+')
	{
		startIndex = 1;
	}
	if (str[0] == '-')
	{
		isNegative = true;
		startIndex = 1;
	}
	
	for (size_t i = startIndex; i < str.length(); i++)
	{
		int number = CharToInt(str[i]);
		if (number < 0 || number >= sourceRadix)
		{
			wasError = true;
			return numericValue;
		}
		numericValue = CalculateUsingRadix(numericValue, 
			isNegative ? -1 * number : number, sourceRadix, wasError);
		if (wasError)
		{
			return numericValue;
		}
	}

	wasError = false;
	return numericValue;
}

std::string IntToString(int number, int destinationRadix)
{
	std::string result;
	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
	}
	while (number != 0)
	{
		int n = number % destinationRadix;
		if (isNegative)
		{
			n *= -1;
		}
		result = IntToChar(n) + result;
		number /= destinationRadix;
	}

	return isNegative ? '-' + result : (result.empty() ? "0" : result);
}

std::string ChangeRadix(int sourceRadix, int destinationRadix,
	const std::string& str, bool& wasError)
{
	if (sourceRadix < MIN_RADIX_VALUE || sourceRadix > MAX_RADIX_VALUE 
		|| destinationRadix < MIN_RADIX_VALUE || destinationRadix > MAX_RADIX_VALUE)
	{
		wasError = true;
		return "Radix should be between " + std::to_string(MIN_RADIX_VALUE) + " and " + std::to_string(MAX_RADIX_VALUE);
	}

	int numericValue = StringToInt(str, sourceRadix, wasError);
	if (wasError)
	{
		return "Invalid input string";
	}

	wasError = false;
	return IntToString(numericValue, destinationRadix);
}