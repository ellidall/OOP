#include "CDate.h"

int main()
{
	try
	{
	
		CDate today(11, Month::MAY, 2224);

		std::cout << today.GetDay() << CDate::SEPARATOR 
			<< static_cast<unsigned>(today.GetMonth()) << CDate::SEPARATOR
			<< today.GetYear() << "   " << static_cast<unsigned>(today.GetWeekDay()) 
			<< std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	

	return EXIT_SUCCESS;
}