#include "InvertMatrix.h"

struct Args
{
	std::string inputFileName;
};

Args ParseArgs(int argc, char* argv[])
{
	if (!argv || argc != 2)
	{
		throw std::invalid_argument("Error: invalid arguments\nUsage: invert.exe <inputFile>\n");
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		const auto args = ParseArgs(argc, argv);
		Matrix mat = ReadMatrix(args.inputFileName);
		const auto inversedMatrix = InverseMatrix(mat);
		if (inversedMatrix.has_value())
		{
			PrintMatrix(inversedMatrix.value());
		}
		else
		{
			std::cout << "Matrix cannot be inverted (determinant = 0)\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}