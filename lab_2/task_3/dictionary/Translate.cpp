#include "Translate.h"

const std::string EXIT_WORD = "...";
const std::string EXIT_FROM_TRANSLATOIN_WORD = "";
const std::string PREFIX_FOR_TRANSLATION = ">> ";

void SetConsoleSettings()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

std::string GetValueFromStream(std::istream& stream)
{
	std::string value;
	getline(stream, value);
	return value;
}

Dictionary ReadDictionary(const std::string& inputFileName)
{
	std::ifstream file(inputFileName);
	if (!file.is_open())
	{
		throw std::invalid_argument("Error: Unable to open file " + inputFileName);
	}

	Dictionary dictionary;
	std::string phrase;
    std::string	translation;
	while (std::getline(file, phrase) && std::getline(file, translation))
	{
		dictionary[phrase] = translation;
	}

	if (!file.eof())
	{
		throw std::runtime_error("Error while reading the file");
	}

	return dictionary;
}

void SaveDictionsry(const std::string& outputFileName, const Dictionary& dictionary)
{
	std::ofstream outputFile;
	outputFile.open(outputFileName);

	if (!(outputFile.is_open()))
	{
		throw std::invalid_argument("Error: Unable to open file " + outputFileName);
	}
	
	for (const auto& [phrase, translation] : dictionary)
	{
		if (!(outputFile << phrase << "\n" << translation << std::endl))
		{
			throw std::ios_base::failure("Error while writing to the file");
		}
	}
}

void AskAboutSaveNecessity(const std::string& fileName,
	const Dictionary& dictionary)
{
	std::cout << "Вы добавили новые переводы, созранить изменения? (y/n)" << std::endl;
	std::string answer = GetValueFromStream(std::cin);
	if (answer == "y" || answer == "Y")
	{
		SaveDictionsry(fileName, dictionary);
		std::cout << "Изменения успешно сохранены" << std::endl;
	}
	else
	{
		std::cout << "Изменения не были сохранены" << std::endl;
	}
}

//void AskForSetTranslation(Dictionary& dictionary, std::istream& stream)
//{
//	std::cout << "Перевод не найден, введите перевод сами (чтобы выйти нажмите Enter)" << std::endl;
//	std::string value = GetValueFromStream(stream);
//	std::cout << "Можете продолжать переводить (чтобы выйти введите '"
//			  << EXIT_WORD << "'):" << std::endl;
//	if (value != EXIT_FROM_TRANSLATOIN_WORD)
//	{
//		dictionary[key] = value;
//	}
//}

void RunDialogWithUser(Dictionary& dictionary, std::istream& stream)
{
	std::cout << "Вводите слова, которые хотите перевести с английского (чтобы выйти введите '"
		<< EXIT_WORD << "'):" << std::endl;
	std::string key;
	while (getline(stream, key))
	{
		if (key == EXIT_WORD)
		{
			break;
		}
		auto record = dictionary.find(key);
		if (record != dictionary.end())
		{
			std::cout << PREFIX_FOR_TRANSLATION << record->second << std::endl;
		}
		else
		{
			//Выглядит сложно, вынести в функцию
			std::cout << "Перевод не найден, введите перевод сами (чтобы выйти нажмите Enter)" << std::endl;
			std::string value = GetValueFromStream(stream);
			std::cout << "Можете продолжать переводить (чтобы выйти введите '"
				<< EXIT_WORD << "'):" << std::endl;
			if (value != EXIT_FROM_TRANSLATOIN_WORD)
			{
				dictionary[key] = value;
			}
		}
	}
}