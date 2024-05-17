#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector/ArithmeticMean.h"

using namespace std;

SCENARIO("ReadNumbers")
{
	WHEN("Input file is correct")
	{
		std::ifstream inputFile;
		inputFile.open("input.txt");
		vector<double> numbers = ReadNumbers(inputFile);
		vector<double> expectedNumbers = { -1, 1 };

		THEN("Correct output")
		{
			REQUIRE(numbers == expectedNumbers);
		}
	}
}

SCENARIO("TransformVectorByArithmeticMean")
{
	WHEN("Input is empty")
	{
		vector<double> numbers = {};

		THEN("Output is empty")
		{
			TransformVectorByArithmeticMean(numbers);
			REQUIRE(numbers.empty());
		}
	}

	WHEN("Correct input")
	{
		vector<double> numbers = { -1, 1 };
		vector<double> expectedNumbers = { 0, 2 };

		THEN("Correct output")
		{
			TransformVectorByArithmeticMean(numbers);
			REQUIRE(numbers == expectedNumbers);
		}
	}
}