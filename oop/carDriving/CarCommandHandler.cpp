#include "./CarCommandHandler.h"

const std::string COMMAND_STOP = "...";
const std::string COMMAND_INFO = "Info";
const std::string COMMAND_ENGINE_ON = "EngineOn";
const std::string COMMAND_ENGINE_OFF = "EngineOff";
const std::string COMMAND_SET_GEAR = "SetGear";
const std::string COMMAND_SET_SPEED = "SetSpeed";
const std::string RESPONSE_PREFIX_WORD = ">> ";
const std::string PREFIX_WORD_ON_START = "   -- ";

// проверку на переполнение
std::string CarCommandHandler::ConvertDirectionToString() const 
{
	const auto direction = m_car.GetDirection();
	switch (direction)
	{
	case Direction::FORWARD:
		return "forward";
	case Direction::BACKWARD:
		return "backward";
	case Direction::STANDING_STILL:
		return "standing still";
	default:
		throw std::invalid_argument("Unknown direction");
	}
}

void CarCommandHandler::HandleCommandInfo() const
{
	std::cout << "-------- INFO --------" << std::endl;
	std::cout << "Engine: " << (m_car.IsEngineOn() ? "on" : "off") << std::endl;
	std::cout << "Direction: " << ConvertDirectionToString() << std::endl;
	std::cout << "Speed: " << m_car.GetSpeed() << std::endl;
	std::cout << "Gear: " << m_car.GetGear() << std::endl;
	std::cout << "----------------------" << std::endl;
}

void CarCommandHandler::HandleCommandEngineOn()
{
	std::cout << RESPONSE_PREFIX_WORD;
	if (!m_car.TurnOnEngine())
	{
		std::cout << "Error: Unable to turn on engine" << std::endl;
	}
	else
	{
		std::cout << "Engine has been turned on successfully" << std::endl;
	}
}

void CarCommandHandler::HandleCommandEngineOff()
{
	std::cout << RESPONSE_PREFIX_WORD;
	if (!m_car.TurnOffEngine())
	{
		std::cout << "Error: Unable to turn off engine" << std::endl;
	}
	else
	{
		std::cout << "Engine has been turned off successfully" << std::endl;
	}
}

void CarCommandHandler::HandleCommandSetGear()
{
	int arg;
	std::cin >> arg;
	std::cout << RESPONSE_PREFIX_WORD;
	if (!m_car.SetGear(arg))
	{
		std::cout << "Error: Unable to set gear" << std::endl;
	}
	else
	{
		std::cout << "Gear has been changed successfully" << std::endl;
	}
		
}

void CarCommandHandler::HandleCommandSetSpeed()
{
	int arg;
	std::cin >> arg;
	std::cout << RESPONSE_PREFIX_WORD;
	if (!m_car.SetSpeed(arg))
	{
		std::cout << "Error: Unable to set speed" << std::endl;
	}
	else
	{
		std::cout << "Speed has been changed successfully" << std::endl;
	}
}

void CarCommandHandler::HandleCarDriving()
{
	std::cout << "START" << std::endl;
	std::cout << "Available commands:" << std::endl;
	std::cout << PREFIX_WORD_ON_START  << COMMAND_INFO << std::endl;
	std::cout << PREFIX_WORD_ON_START  << COMMAND_ENGINE_ON << std::endl;
	std::cout << PREFIX_WORD_ON_START  << COMMAND_ENGINE_OFF << std::endl;
	std::cout << PREFIX_WORD_ON_START  << COMMAND_SET_GEAR << std::endl;
	std::cout << PREFIX_WORD_ON_START  << COMMAND_SET_SPEED << std::endl;
	std::cout << PREFIX_WORD_ON_START << COMMAND_STOP << "(exit)" << std::endl;

	while (true)
	{
		try
		{
			std::cin >> m_command;
			if (m_command == COMMAND_INFO)
				HandleCommandInfo();
			else if (m_command == COMMAND_ENGINE_ON)
				HandleCommandEngineOn();
			else if (m_command == COMMAND_ENGINE_OFF)
				HandleCommandEngineOff();
			else if (m_command == COMMAND_SET_GEAR)
				HandleCommandSetGear();
			else if (m_command == COMMAND_SET_SPEED)
				HandleCommandSetSpeed();
			else if (m_command == COMMAND_STOP)
				return;
			else
				throw std::invalid_argument("Unknown command");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}