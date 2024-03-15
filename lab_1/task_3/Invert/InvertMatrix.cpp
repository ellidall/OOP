#include "InvertMatrix.h"

Minor CreateMinor(const Matrix& matrix, size_t rowIndex, size_t columnIndex)
{
	Minor minor;
	int minorRow = 0, minorCol = 0;
	for (size_t row = 0; row < MATRIX_DIMENSION; ++row)
	{
		if (row == rowIndex)
			continue;
		for (size_t col = 0; col < MATRIX_DIMENSION; ++col)
		{
			if (col == columnIndex)
				continue;
			minor[minorRow][minorCol] = matrix[row][col];
			++minorCol;
		}
		++minorRow;
		minorCol = 0;
	}
	return minor;
}

void PrintMinor(const Minor& minor)
{
	for (int i = 0; i < MINOR_DIMENSION; ++i)
	{
		for (int j = 0; j < MINOR_DIMENSION; ++j)
		{
			std::cout << minor[i][j] << "   ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

double GetMinorDeterminant(const Minor& minor)
{
	return minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0];
}

double GetMatrixDeterminant(const Matrix& matrix)
{
	double det = 0.0;
	size_t i = 0;

	for (size_t j = 0; j < MATRIX_DIMENSION; ++j)
	{
		Minor minor = CreateMinor(matrix, i, j);
		double minorDet = GetMinorDeterminant(minor);

		if (j % 2 == 0)
			det += matrix[0][j] * minorDet;
		else
			det -= matrix[0][j] * minorDet;
	}

	return det;
}

Matrix CreateAlgebraicCofactorMatrix(const Matrix& initialMatrix)
{
	Matrix algebraicAdditionsMatrix;

	for (size_t i = 0; i < MATRIX_DIMENSION; ++i)
	{
		for (size_t j = 0; j < MATRIX_DIMENSION; ++j)
		{
			Minor minor = CreateMinor(initialMatrix, i, j);
			algebraicAdditionsMatrix[i][j] = GetMinorDeterminant(minor);
		}
	}

	return algebraicAdditionsMatrix;
}

Matrix TransposeMatrix(const Matrix& mat)
{
	Matrix transposedMatrix;

	for (int i = 0; i < MATRIX_DIMENSION; ++i)
	{
		for (int j = 0; j < MATRIX_DIMENSION; ++j)
		{
			transposedMatrix[i][j] = mat[j][i];
		}
	}

	return transposedMatrix;
}

Matrix MultiplyMatrixElementsByCoefficient(const Matrix& matrix, double coefficient)
{
	Matrix modifiedMatrix;

	for (int i = 0; i < MATRIX_DIMENSION; ++i)
	{
		for (int j = 0; j < MATRIX_DIMENSION; ++j)
		{
			modifiedMatrix[i][j] = coefficient * matrix[i][j];
		}
	}

	return modifiedMatrix;
}

Matrix ReadMatrix(const std::string& matrixFileName)
{
	std::ifstream inputFile(matrixFileName);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Error: Unable to open file " + matrixFileName + "\n");
	}

	Matrix result{};
	std::string line;
	size_t row = 0;
	size_t col = 0;
	while (getline(inputFile, line) && row < MATRIX_DIMENSION)
	{
		std::istringstream iss(line);
		double value;
		col = 0;
		while (col < MATRIX_DIMENSION && iss >> value)
		{
			result[row][col] = value;
			++col;
		}
		++row;
	}
	if (row != MATRIX_DIMENSION || col != MATRIX_DIMENSION)
	{
		throw std::invalid_argument("Error: number of rows and columns of the matrix should be 3");
	}

	return result;
}

std::optional<Matrix> InverseMatrix(const Matrix& mat)
{
	double det = GetMatrixDeterminant(mat);
	if (det == 0)
	{
		return std::nullopt;
	}
	Matrix algebraicCofactorMatrix = CreateAlgebraicCofactorMatrix(mat);
	Matrix transposedMatrix = TransposeMatrix(algebraicCofactorMatrix);

	return MultiplyMatrixElementsByCoefficient(transposedMatrix, 1/det);
}

void PrintMatrix(const Matrix& matrix)
{
	for (int i = 0; i < MATRIX_DIMENSION; ++i)
	{
		for (int j = 0; j < MATRIX_DIMENSION; ++j)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << "    ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}