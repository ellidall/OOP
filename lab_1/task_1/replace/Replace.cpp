#include "CopyFileWithReplacement.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replacementString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (!argv || argc != 5)
	{
		return std::nullopt;
	}
	if (argv[1] == argv[2])
	{
		std::cout << "Error: names of input and output files must not match\n";
		return std::nullopt;
	}

	Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replacementString = argv[4];

	return args;
}

int main(int argc, char* argv[])
{
	const auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "Error: invalid arguments\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return EXIT_FAILURE;
	}

	try
	{
		CopyFileWithReplacement(args->inputFileName, args->outputFileName,
			args->searchString,	args->replacementString);
		std::cout << "Successfull replacement\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}