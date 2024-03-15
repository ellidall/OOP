#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTML_decode/HTMLDecode.h"

using namespace std;

SCENARIO("HtmlDecode")
{
	WHEN("Input is empty")
	{
		string htmlText = "";

		THEN("Correct decode")
		{
			REQUIRE(HTML::HtmlDecode(htmlText) == "");
		}
	}

	WHEN("Input with multiple &")
	{
		string htmlText = "&&&&quot;";

		THEN("Correct decode")
		{
			REQUIRE(HTML::HtmlDecode(htmlText) == "&&&\"");
		}
	}
}

SCENARIO("ReadStreamWithDecode")
{
	WHEN("Input is empty")
	{
		istringstream htmlText("");

		THEN("Error")
		{
			REQUIRE_THROWS_AS(HTML::ReadStreamWithDecode(htmlText), std::invalid_argument);
		}
	}

	WHEN("Multiline input")
	{
		istringstream htmlText("abc\n\n&lt;");

		THEN("Correct output")
		{
			REQUIRE(HTML::ReadStreamWithDecode(htmlText) == "abc\n\n<\n");
		}
	}
}