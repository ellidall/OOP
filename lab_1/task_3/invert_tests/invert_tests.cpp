#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Invert/InvertMatrix.h"

using namespace std;

SCENARIO("ReadMatrix")
{
	WHEN("Invalid input")
	{
		string matrixFileName = "123.txt";

		THEN("Error: invalid input")
		{
			REQUIRE_THROWS_AS(ReadMatrix(matrixFileName), invalid_argument);
		}
	}

	WHEN("Invalid matrix dimension")
	{
		string matrixFileName = "invalid_matrix.txt";

		THEN("Error: invalid matrix dimension")
		{
			REQUIRE_THROWS_AS(ReadMatrix(matrixFileName), invalid_argument);
		}
	}

	WHEN("Valid input")
	{
		string matrixFileName = "matrix.txt";
		Matrix matrix = { 1, -2, 3, 4, 0, 6, -7, 8, 9 };

		THEN("Correct output")
		{
			REQUIRE(ReadMatrix(matrixFileName) == matrix);
		}
	}

	WHEN("Matrix with redundant data")
	{
		string matrixFileName = "matrix_with_redundant_data.txt";
		Matrix matrix = { 1, -2, 3, 4, 0, 6, -7, 8, 9 };

		THEN("Correct output")
		{
			REQUIRE(ReadMatrix(matrixFileName) == matrix);
		}
	}
}

SCENARIO("InverseMatrix")
{
	WHEN("Determinant is zero")
	{
		Matrix matrix = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

		THEN("Matrix cannot be inverted (determinant = 0)")
		{
			REQUIRE(InverseMatrix(matrix) == nullopt);
		}
	}

	WHEN("Correct to invert input matrix")
	{
		Matrix matrix = { 1, -2, 3, 4, 0, 6, -7, 8, 9 };

		THEN("Correct inverted matrix")
		{
			REQUIRE(InverseMatrix(matrix) != nullopt);
		}
	}
}