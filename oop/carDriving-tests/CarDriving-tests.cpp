#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../carDriving/Car.h"

TEST_CASE("Test Car methods")
{
	Car car;

	SECTION("Test IsEngineOn")
	{
		REQUIRE(car.IsEngineOn() == false);
		car.TurnOnEngine();
		REQUIRE(car.IsEngineOn() == true);
	}

	SECTION("Test GetDirection")
	{
		car.TurnOnEngine();
		REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
		car.SetGear(1);
		car.SetSpeed(10);
		REQUIRE(car.GetDirection() == Direction::FORWARD);
		car.SetGear(0);
		car.SetSpeed(0);
		car.SetGear(-1);
		car.SetSpeed(10);
		REQUIRE(car.GetDirection() == Direction::BACKWARD);
	}

	SECTION("Test GetSpeed")
	{
		car.TurnOnEngine();
		car.SetGear(0);
		car.SetSpeed(0);
		car.SetGear(1);
		car.SetSpeed(15);
		REQUIRE(car.GetSpeed() == 15);
		car.SetGear(0);
		car.SetSpeed(0);
		car.SetGear(-1);
		car.SetSpeed(20);
		REQUIRE(car.GetSpeed() == 20);
	}

	SECTION("Test GetGpeed")
	{
		car.TurnOnEngine();
		REQUIRE(car.GetGear() == 0);
		car.SetGear(1);
		REQUIRE(car.GetGear() == 1);
		car.SetGear(-1);
		REQUIRE(car.GetGear() == -1);
	}

	SECTION("Test TurnOnEngine")
	{
		REQUIRE(car.IsEngineOn() == false);
		car.TurnOnEngine();
		REQUIRE(car.IsEngineOn() == true);
	}

	SECTION("Test TurnOffEngine")
	{
		REQUIRE(car.IsEngineOn() == false);
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		REQUIRE(car.TurnOffEngine() == false);
		car.SetGear(0);
		car.SetSpeed(10);
		REQUIRE(car.TurnOffEngine() == false);
		car.SetSpeed(0);
		REQUIRE(car.TurnOffEngine() == true);
	}

	SECTION("Test SetGear - Alternately switching gears")
	{
		car.TurnOnEngine();
		REQUIRE(car.SetGear(-1) == true);
		car.SetSpeed(20);
		REQUIRE(car.SetGear(0) == true);
		car.SetSpeed(0);
		REQUIRE(car.SetGear(1) == true);
		car.SetSpeed(19);
		REQUIRE(car.SetGear(2) == false);
		car.SetSpeed(20);
		REQUIRE(car.SetGear(2) == true);
		car.SetSpeed(29);
		REQUIRE(car.SetGear(3) == false);
		car.SetSpeed(30);
		REQUIRE(car.SetGear(3) == true);
		car.SetSpeed(39);
		REQUIRE(car.SetGear(4) == false);
		car.SetSpeed(40);
		REQUIRE(car.SetGear(4) == true);
		car.SetSpeed(49);
		REQUIRE(car.SetGear(5) == false);
		car.SetSpeed(50);
		REQUIRE(car.SetGear(5) == true);
	}

	SECTION("Test SetGear - Switching the gear to neutral at a forward speed")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		REQUIRE(car.SetGear(0) == true);
		REQUIRE(car.GetGear() == 0);
	}

	SECTION("Test SetGear - Switching the gear to neutral at a backward speed")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(20);
		REQUIRE(car.SetGear(0) == true);
		REQUIRE(car.GetGear() == 0);
	}

	SECTION("Test SetGear - Switching to backward gear when reversing in neutral speed")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);
		REQUIRE(car.SetGear(-1) == false);
		REQUIRE(car.GetGear() == 0);
	}

	SECTION("Test SetSpeed - The speed cannot be negative")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		REQUIRE(car.SetSpeed(-10) == false);
		REQUIRE(car.GetSpeed() == 0);
	}	

	SECTION("Test SetSpeed - Cannot accelerate in neutral gear")
	{
		car.TurnOnEngine();
		car.SetGear(0);
		REQUIRE(car.SetSpeed(30) == false);
		REQUIRE(car.GetSpeed() == 0);
	}	

	SECTION("Test SetSpeed - Cannot switch from forward speed to backward gear")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(15);
		REQUIRE(car.SetGear(-1) == false);
		REQUIRE(car.GetGear() == 1);
	}	

	SECTION("Test SetSpeed - Cannot switch from backward speed to forward gear")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(15);
		REQUIRE(car.SetGear(1) == false);
		REQUIRE(car.GetGear() == -1);
	}	

	SECTION("Test SetSpeed - Switching from the backward speed to neutral, reducing the speed and trying to switch to the forward speed")
	{
		car.TurnOnEngine();
		REQUIRE(car.SetGear(-1) == true);
		REQUIRE(car.SetSpeed(20) == true);
		REQUIRE(car.SetGear(0) == true);
		REQUIRE(car.SetSpeed(10) == true);
		REQUIRE(car.SetGear(1) == false);
		REQUIRE(car.SetSpeed(0) == true);
		REQUIRE(car.SetGear(1) == true);
		REQUIRE(car.SetGear(-1) == true);
	}	
}