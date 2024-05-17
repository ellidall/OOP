#pragma once

#include "StandartImports.h"

std::vector<double> ReadNumbers(std::istream& input);
void PrintNumbers(const std::vector<double>& numbers);
void TransformVectorByArithmeticMean(std::vector<double>& numbers);