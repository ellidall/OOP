#pragma once

#include "StandartImports.h"

constexpr const size_t MATRIX_DIMENSION = 3;
constexpr const size_t MINOR_DIMENSION = 2;

using Matrix = std::array<std::array<double, MATRIX_DIMENSION>, MATRIX_DIMENSION>;
using Minor = std::array<std::array<double, MINOR_DIMENSION>, MINOR_DIMENSION>;

Matrix ReadMatrix(const std::string& matrixFileName);
std::optional<Matrix> InverseMatrix(const Matrix& mat);
void PrintMatrix(const Matrix& matrix);