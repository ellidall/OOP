#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../../catch2/catch.hpp"
#include "../Calculator/Calculator.h"
#include "../Calculator/Function.h"

TEST_CASE("Test Calculator")
{
	Calculator calculator;

	SECTION("TEST InitVariable")
	{
		std::string name = "variable";
		calculator.InitVariable(name);
		REQUIRE(isnan(calculator.GetVariable(name).GetValue()));
		REQUIRE_THROWS_AS(calculator.InitVariable(name), std::invalid_argument);
	}

	SECTION("TEST SetVariable")
	{
		std::string name = "variable1";
		std::string assignableVariableName = "variable2";

		SECTION("assigning a variable value to another UNINITIALIZED variable")
		{
			REQUIRE_THROWS_AS(calculator.SetVariable(name, assignableVariableName), std::invalid_argument);
		}
		SECTION("assigning a variable value to another INITIALIZED variable")
		{
			calculator.InitVariable(assignableVariableName);
			calculator.SetVariable(name, assignableVariableName);
			REQUIRE(isnan(calculator.GetVariable(name).GetValue()));
		}
		SECTION("assigning a variable value to another INITIALIZED function")
		{
			std::string functionName = "func";
			calculator.InitVariable(assignableVariableName);
			calculator.SetFunction(functionName, assignableVariableName);
			calculator.SetVariable(name, functionName);
			REQUIRE(isnan(calculator.GetVariable(name).GetValue()));
		}
		SECTION("assigning a variable value to DECIMAL")
		{
			double decimalValue = 10;
			calculator.SetVariable(name, decimalValue);
			REQUIRE(calculator.GetVariable(name).GetValue() == decimalValue);
		}
	}

	SECTION("TEST SetFunction")
	{
		std::string name = "function";
		std::string nameOfArg = "variable";
		std::string nameOfArg1 = "variable1";
		std::string nameOfArg2 = "variable2";

		SECTION("assigning a function value to another INITIALIZED variable")
		{
			double decimalValue = 10;
			calculator.SetVariable(nameOfArg, decimalValue);
			calculator.SetFunction(name, nameOfArg);
			REQUIRE(calculator.GetVariable(name).GetValue() == decimalValue);
		}
		SECTION("assigning a function value to another INITIALIZED function")
		{
			std::string functionInArg = "func";

			double decimalValue = 10;
			calculator.SetVariable(nameOfArg, decimalValue);
			calculator.SetFunction(functionInArg, nameOfArg);
			calculator.SetFunction(name, functionInArg);
			REQUIRE(calculator.GetVariable(name).GetValue() == decimalValue);
		}
		SECTION("assigning a value to a function via a formula")
		{
			std::string functionInArg = "func";
			calculator.SetVariable(nameOfArg1, 10);
			calculator.SetVariable(nameOfArg2, 20);
			SECTION("VARIABLES")
			{
				SECTION("operator '+'")
				{
					calculator.SetFunction(name, nameOfArg1, nameOfArg2, Operations::Plus);
					REQUIRE(calculator.GetVariable(name).GetValue() == 30);
				}
				SECTION("operator '-'")
				{
					calculator.SetFunction(name, nameOfArg1, nameOfArg2, Operations::Minus);
					REQUIRE(calculator.GetVariable(name).GetValue() == -10);
				}
				SECTION("operator '*'")
				{
					calculator.SetFunction(name, nameOfArg1, nameOfArg2, Operations::Multiplication);
					REQUIRE(calculator.GetVariable(name).GetValue() == 200);
				}
				SECTION("operator '/'")
				{
					calculator.SetFunction(name, nameOfArg1, nameOfArg2, Operations::Division);
					REQUIRE(calculator.GetVariable(name).GetValue() == 0.5);
				}
				SECTION("division by zero")
				{
					calculator.SetVariable(nameOfArg2, 0.0);
					REQUIRE_THROWS_AS(calculator.SetFunction(name, nameOfArg1, nameOfArg2, Operations::Division), std::invalid_argument);
				}
			}
			
			SECTION("FUNCTIONS")
			{
				SECTION("assigning a function to other functions")
				{
					std::string nameOfFunc1 = "func1";
					std::string nameOfFunc2 = "func2";
					calculator.SetFunction(nameOfFunc1, nameOfArg1);
					calculator.SetFunction(nameOfFunc2, nameOfArg2);
					calculator.SetFunction(name, nameOfFunc1, nameOfFunc2, Operations::Plus);
					REQUIRE(calculator.GetVariable(name).GetValue() == 30);
				}
				SECTION("assigning a function to other function and variable")
				{
					std::string nameOfFunc1 = "func1";
					calculator.SetFunction(nameOfFunc1, nameOfArg1);
					calculator.SetFunction(name, nameOfFunc1, nameOfArg2, Operations::Plus);
					REQUIRE(calculator.GetVariable(name).GetValue() == 30);
				}
				SECTION("assigning a function to other UNINITIALIZED variables")
				{
					REQUIRE_THROWS_AS(calculator.SetFunction(name, "q1"), std::invalid_argument);
					REQUIRE_THROWS_AS(calculator.SetFunction(name, "q1", "q2", Operations::Plus), std::invalid_argument);
				}
			}
		}
	}

	SECTION("Test Update")
	{
		std::string variableName1 = "var1";
		std::string variableName2 = "var2";
		std::string functionName = "func";
		calculator.SetVariable(variableName1, 10.0);
		calculator.SetVariable(variableName2, 200.0);
		calculator.SetFunction(functionName, variableName1, variableName2, Operations::Plus);
		REQUIRE(calculator.GetVariable(functionName).GetValue() == 210);
		calculator.SetVariable(variableName1, 100.0);
		REQUIRE(calculator.GetVariable(functionName).GetValue() == 300);
	}
}