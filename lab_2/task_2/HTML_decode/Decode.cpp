#include "HTMLDecode.h"

int main()
{
	try
	{
		std::string decodedText = HTML::ReadStreamWithDecode(std::cin);
		std::cout << "Decoded text: " << decodedText << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}