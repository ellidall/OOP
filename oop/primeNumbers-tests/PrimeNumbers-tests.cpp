#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../primeNumbers/GeneratePrimeNumbers.h"

using namespace std;

SCENARIO("GeneratePrimeNumbers")
{
	WHEN("Upper bound is greater than the maximum allowed value")
	{
		int upperBound = MAX_UPPER_BOUND + 1;
		THEN("Exception")
		{
			REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(upperBound), invalid_argument);
		}
	}

	#ifdef NDEBUG
	WHEN("Upper bound is max")
	{
		int upperBound = MAX_UPPER_BOUND;
		int expectedAmount = 5761455;

		THEN("Correct execution of the program")
		{
			REQUIRE(GeneratePrimeNumbersSet(upperBound).size() == expectedAmount);
		}
	}
	#endif

	WHEN("Arbitrary input")
	{
		// пороверить возвращаемое множество
		int upperBound = 17;
		int expectedAmount = 7;

		THEN("Correct execution of the program")
		{
			REQUIRE(GeneratePrimeNumbersSet(upperBound).size() == expectedAmount);
		}
	}

	WHEN("Upper bound is min")
	{
		int upperBound = 2;
		int expectedAmount = 1;

		THEN("Correct execution of the program")
		{
			REQUIRE(GeneratePrimeNumbersSet(upperBound).size() == expectedAmount);
		}
	}
}