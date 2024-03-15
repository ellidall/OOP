#pragma once

#include "CopyFileWithReplacement.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos == std::string::npos)
		{
			break;
		}
		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (!(output << ReplaceString(line, searchString, replacementString) << "\n"))
		{
			throw std::ofstream::failure("Error: writing to the stream was incorrect\n");
		}
		
	}
	if (!input.eof())
	{
		throw std::ios_base::failure("Error: the file is not fully read\n");
	}
}

void CopyFileWithReplacement(const std::string& inputFileName,	const std::string& outputFileName,
	const std::string& searchString,const std::string& replacementString)
{
	std::ifstream inputFile;
	std::ofstream outputFile;

	inputFile.open(inputFileName);
	outputFile.open(outputFileName);
	if (!inputFile.is_open())
	{
		throw std::ios_base::failure("Error: Unable to open file " + inputFileName + "\n");
	}
	if (!outputFile.is_open())
	{
		throw std::ios_base::failure("Error: Unable to open file " + outputFileName + "\n");
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk\n");
	}
}
