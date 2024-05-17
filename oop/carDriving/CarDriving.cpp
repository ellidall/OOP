#include "./CarCommandHandler.h"

int main()
{
	Car car;
	CarCommandHandler commandHandler(car);
	commandHandler.HandleCarDriving();

	return EXIT_SUCCESS;
}