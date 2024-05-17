#include "Translate.h"

std::optional<std::string> GetDictionaryFileName(char* argv[])
{
	//без проверки argc нельзя
	if (!argv[1])
	{
		return std::nullopt;
	}

	return argv[1];
}

int main(int argc, char* argv[])
{
	try
	{
		SetConsoleSettings();
		const auto dictionaryFileName = GetDictionaryFileName(argv);
		if (!dictionaryFileName.has_value())
		{
			throw std::invalid_argument("Error: Usage dictionary.exe <dictionaryFileName>");
		}
		const std::string& fileName = dictionaryFileName.value();
		Dictionary dictionary = ReadDictionary(fileName);
		Dictionary newDictionary = dictionary;
		RunDialogWithUser(newDictionary, std::cin);
		if (dictionary != newDictionary)
		{
			//в иф засунуть как бул
			AskAboutSaveNecessity(fileName, newDictionary);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
