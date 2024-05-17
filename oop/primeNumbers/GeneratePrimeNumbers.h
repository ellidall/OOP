#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <string>

const int MAX_UPPER_BOUND = 100000000;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSet(std::ostream& output, const std::set<int>& set);