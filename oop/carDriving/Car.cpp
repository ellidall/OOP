#include "Car.h"

bool Car::IsEngineOn() const { return m_engineOn; }

Direction Car::GetDirection() const
{
	if (m_speed > 0)
		return Direction::FORWARD;
	else if (m_speed < 0)
		return Direction::BACKWARD;
	else
		return Direction::STANDING_STILL;
}

int Car::GetSpeed() const { return abs(m_speed); }

int Car::GetGear() const { return m_gear; }

bool Car::TurnOnEngine()
{
	if (!IsEngineOn())
	{
		m_engineOn = true;
		m_gear = 0;
		return true;
	}
	return false;
}

bool Car::TurnOffEngine()
{
	if (IsEngineOn() && m_gear == 0 && m_speed == 0)
	{
		m_engineOn = false;
		return true;
	}
	return false;
}

bool Car::SetGear(int newGear)
{
	const auto range = GetAvailableSpeedRangeByGear(newGear);
	if (!range.has_value())
	{
		return false;
	}
	const auto [minSpeed, maxSpeed] = range.value();
	if (m_speed > 0 && newGear == BACKWARD_GEAR)
		return false;
	if (IsEngineOn() && m_speed >= minSpeed && m_speed <= maxSpeed)
	{
		m_gear = newGear;
		return true;
	}
	return false;
}

bool Car::SetSpeed(int newSpeed)
{
	if (!IsEngineOn() || newSpeed < 0 || (m_gear == NEUTRAL_GEAR && newSpeed > abs(m_speed)))
		return false;
	if (m_gear == NEUTRAL_GEAR && m_speed <= 0 && newSpeed >= 0 && newSpeed <= abs(m_speed))
	{
		m_speed = -newSpeed;
		return true;
	}
	const auto range = GetAvailableSpeedRangeByGear(m_gear);
	if (!range.has_value())
	{
		return false;
	}
	const auto [minSpeed, maxSpeed] = range.value();
	if (newSpeed >= minSpeed && newSpeed <= maxSpeed)
	{
		m_speed = (m_gear == BACKWARD_GEAR) ? -newSpeed : newSpeed;
		return true;
	}
	return false;
}

std::optional<std::pair<int, int>> Car::GetAvailableSpeedRangeByGear(int gear) const
{
	try
	{
		return m_availableSpeedByGear.at(gear);
	}
	catch (const std::exception& e)
	{
		return std::nullopt;
	}
}