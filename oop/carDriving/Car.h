#pragma once

#include <iostream>
#include <map>
#include <optional>

const int NEUTRAL_GEAR = 0;
const int BACKWARD_GEAR = -1;
const int MAX_BACKWARD_SPEED = 20;

enum class Direction
{
	FORWARD,
	BACKWARD,
	STANDING_STILL,
};

class Car
{
public:
	Car() : m_engineOn(false), m_gear(0), m_speed(0) {}

	const std::map<Direction, std::string> m_directionToString = {
		{ Direction::FORWARD, "forward" },
		{ Direction::BACKWARD, "backward" },
		{ Direction::STANDING_STILL, "standing still" }
	};

	bool IsEngineOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int newGear);
	bool SetSpeed(int newSpeed);
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

private:
	bool m_engineOn;
	int m_gear;
	int m_speed;
	const std::map<int, std::pair<int, int>> m_availableSpeedByGear = {
		{ BACKWARD_GEAR, { 0, MAX_BACKWARD_SPEED } },
		{ NEUTRAL_GEAR, { -MAX_BACKWARD_SPEED, 150 } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } },
	};

	std::optional<std::pair<int, int>> GetAvailableSpeedRangeByGear(int gear) const;
};