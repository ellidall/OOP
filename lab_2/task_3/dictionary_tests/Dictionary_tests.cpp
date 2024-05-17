#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary/Translate.h"

using namespace std;

SCENARIO("RunDialogWithUser")
{
	SetConsoleSettings();
	WHEN("Сorrect input with recording new translation")
	{
		Dictionary dictionary = {
			{ "cat", "кошка" },
			{ "dog", "собака" },
			{ "horse", "лошадь" },
		};
		Dictionary expectedDictionary = {
			{ "cat", "кошка" },
			{ "dog", "собака" },
			{ "fox", "лиса" },
			{ "horse", "лошадь" },
		};
		istringstream input("cat\nfox\nлиса\n...\n");


		THEN("Correct recording to dictionary")
		{
			RunDialogWithUser(dictionary, input);
			REQUIRE(dictionary == expectedDictionary);
		}
	}

	WHEN("Empty input dictionary")
	{
		Dictionary dictionary = {};
		Dictionary expectedDictionary = {
			{ "fox", "лиса" },
		};
		istringstream input("fox\nлиса\n...\n");

		THEN("Correct dictionary creating")
		{
			RunDialogWithUser(dictionary, input);
			REQUIRE(dictionary == expectedDictionary);
		}
	}
}

//добавить тесты на вывод словаря
