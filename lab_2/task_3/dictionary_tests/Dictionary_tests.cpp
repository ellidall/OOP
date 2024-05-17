#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary/Translate.h"

using namespace std;

SCENARIO("RunDialogWithUser")
{
	SetConsoleSettings();
	WHEN("�orrect input with recording new translation")
	{
		Dictionary dictionary = {
			{ "cat", "�����" },
			{ "dog", "������" },
			{ "horse", "������" },
		};
		Dictionary expectedDictionary = {
			{ "cat", "�����" },
			{ "dog", "������" },
			{ "fox", "����" },
			{ "horse", "������" },
		};
		istringstream input("cat\nfox\n����\n...\n");


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
			{ "fox", "����" },
		};
		istringstream input("fox\n����\n...\n");

		THEN("Correct dictionary creating")
		{
			RunDialogWithUser(dictionary, input);
			REQUIRE(dictionary == expectedDictionary);
		}
	}
}

//�������� ����� �� ����� �������
