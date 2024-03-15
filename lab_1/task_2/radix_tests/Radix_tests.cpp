#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../radix/ChangeRadix.h"

using namespace std;

SCENARIO("ChangeRadix")
{
	WHEN("Input string is empty")
	{
		string str = "";
		int sourceRadix = 10;
		int destinationRadix = 2;
		bool wasError = false;

		THEN("Output with error about empty input string")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError)
				== "Invalid input string");
		}
	}

	WHEN("Numbers in the input string are larger than the source radix")
	{
		string str = "99";
		int sourceRadix = 2;
		int destinationRadix = 10;
		bool wasError = false;

		THEN("Output with error about invalid characters")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError)
				== "Invalid input string");
		}
	}

	WHEN("Input string with invalid characters")
	{
		string str = "9!";
		int sourceRadix = 10;
		int destinationRadix = 2;
		bool wasError = false;

		THEN("Output with error about invalid characters")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError)
				== "Invalid input string");
		}
	}

	WHEN("Invalid source radix")
	{
		string str = "33";
		int sourceRadix = 1;
		int destinationRadix = 10;
		bool wasError = false;

		THEN("Output with error about invalid source radix")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError)
				== "Radix should be between 2 and 36");
		}
	}

	WHEN("Invalid destination radix")
	{
		string str = "33";
		int sourceRadix = 4;
		int destinationRadix = 37;
		bool wasError = false;

		THEN("Output with error about invalid destination radix")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError)
				== "Radix should be between 2 and 36");
		}
	}

	WHEN("Valid positive input string")
	{
		string str = "33";
		int sourceRadix = 10;
		int destinationRadix = 8;
		bool wasError = false;

		THEN("Output with right result")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError) == "41");
		}
	}

	WHEN("Valid negative input string")
	{
		string str = "-33";
		int sourceRadix = 10;
		int destinationRadix = 8;
		bool wasError = false;

		THEN("Output with right result")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError) == "-41");
		}
	}

	WHEN("String indicating the number causes an overflow")
	{
		string str = "3000000000";
		int sourceRadix = 10;
		int destinationRadix = 36;
		bool wasError = false;

		THEN("Output with error about overflow")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError)
				== "Invalid input string");
		}
	}

	WHEN("Input with insignificant zeros in front")
	{
		string str = "000000000000010";
		int sourceRadix = 10;
		int destinationRadix = 2;
		bool wasError = false;

		THEN("Correct output without insignificant zeros in front")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError) == "1010");
		}
	}

	WHEN("Boundary value of INT_MAX")
	{
		string str = "+2147483647";
		int sourceRadix = 10;
		int destinationRadix = 2;
		bool wasError = false;

		THEN("Correct output")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError) == "1111111111111111111111111111111");
		}
	}

	WHEN("Boundary value of INT_MIN")
	{
		string str = "-2147483648";
		int sourceRadix = 10;
		int destinationRadix = 2;
		bool wasError = false;

		THEN("Correct output")
		{
			REQUIRE(ChangeRadix(sourceRadix, destinationRadix, str, wasError) == "-10000000000000000000000000000000");
		}
	}
}