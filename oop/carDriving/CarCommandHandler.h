#pragma once

//разобраться с инклудом
#include <iostream>
#include "Car.h"

class CarCommandHandler
{
public:
	CarCommandHandler(Car& car): m_car(car) {}

	void HandleCarDriving();

private:
	Car m_car;
	std::string m_command;

	std::string ConvertDirectionToString() const;
	void HandleCommandInfo() const;
	void HandleCommandEngineOn();
	void HandleCommandEngineOff();
	void HandleCommandSetGear();
	void HandleCommandSetSpeed();
};