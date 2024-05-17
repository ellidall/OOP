#pragma once

#include "StandartImports.h"

using Dictionary = std::map<std::string, std::string>;

void SetConsoleSettings();
std::string GetValueFromStream(std::istream& stream);
Dictionary ReadDictionary(const std::string& inputFileName);
void RunDialogWithUser(Dictionary& dictionary, std::istream& stream);
void SaveDictionsry(std::string& outputFileName, const Dictionary& dictionary);
void AskAboutSaveNecessity(const std::string& fileName, const Dictionary& dictionary);