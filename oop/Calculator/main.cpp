#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "CalculatorCommandHandler.h"

int main()
{
	//std::ifstream in("./1.txt");
	Calculator calculator;
	CalculatorCommandHandler handler(calculator, std::cin, std::cout);
	
	std::cout << "Start calculating" << std::endl;
	while (!std::cin.eof() && !std::cin.fail())
	{
		handler.HandleCalculating();
	}

	return 0;
}