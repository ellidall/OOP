#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../replace/CopyFileWithReplacement.h"

using namespace std;

SCENARIO("CopyStreamWithReplacement")
{
	WHEN("Input file is empty")
	{
		istringstream input("");
		ostringstream output;
		string searchString = "1";
		string replasementString = "22";

		THEN("Output file is empty")
		{
			CopyStreamWithReplacement(input, output, searchString, replasementString);
			REQUIRE(output.str().empty());
		}
	}

	WHEN("Search string is empty")
	{
		istringstream input("11111111");
		ostringstream output;
		string searchString;
		string replasementString = "22";

		THEN("Correct copy input file to output")
		{
			CopyStreamWithReplacement(input, output, searchString, replasementString);
			REQUIRE(output.str() == "11111111\n");
		}
	}

	WHEN("Search and replasement strings are recursively dependent")
	{
		istringstream input("121");
		ostringstream output;
		string searchString = "1";
		string replasementString = "11";

		THEN("Correct output")
		{
			CopyStreamWithReplacement(input, output, searchString, replasementString);
			REQUIRE(output.str() == "11211\n");
		}
	}

	WHEN("Multiline input")
	{
		istringstream input("123\n\n12");
		ostringstream output;
		string searchString = "2";
		string replasementString = "22";

		THEN("Correct multiline output")
		{
			CopyStreamWithReplacement(input, output, searchString, replasementString);
			REQUIRE(output.str() == "1223\n\n122\n");
		}
	}

	WHEN("Search string was not found in input")
	{
		istringstream input("11111111");
		ostringstream output;
		string searchString = "2";
		string replasementString = "22";

		THEN("Correct copy input file to output")
		{
			CopyStreamWithReplacement(input, output, searchString, replasementString);
			REQUIRE(output.str() == "11111111\n");
		}
	}
}

SCENARIO("CopyFileWithReplacement")
{
	WHEN("Unable to open input file")
	{
		string inputFileName = "input.txt";
		string outputFileName = "output.txt";
		string searchString = "2";
		string replasementString = "22";

		THEN("Exception: Unable to open input file")
		{
			REQUIRE_THROWS_AS(CopyFileWithReplacement(inputFileName, outputFileName,
				searchString, replasementString), ios_base::failure);
		}
	}
}