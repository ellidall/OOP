#pragma once

#include "ChangeRadix.h"

struct Args
{
	std::string sourceRadix;
	std::string destinationRadix;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (!argv || argc != 4)
	{
		return std::nullopt;
	}

	Args args;
	args.sourceRadix = argv[1];
	args.destinationRadix = argv[2];
	args.value = argv[3];

	return args;
}

int main(int argc, char* argv[])
{
	const auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "Error: invalid arguments\n"
				  << "Usage: radix.exe <source radix> <destination radix> <value>\n";
		return EXIT_FAILURE;
	}

	int sourceRadix = std::stoi(args->sourceRadix);
	int destinationRadix = std::stoi(args->destinationRadix);
	bool wasError = true;
	std::string result = ChangeRadix(sourceRadix, destinationRadix, args->value, wasError);

	std::cout << result << "\n";
	if (wasError)  
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}