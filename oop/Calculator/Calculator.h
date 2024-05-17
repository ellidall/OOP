#pragma once

#include <map>
#include <memory>
#include <iostream>
#include <iomanip>
#include "Variable.h"
#include "Function.h"

class Calculator
{
public:
	Calculator() {}

	using VariablesMap = std::map<std::string, std::unique_ptr<Variable>>;
	using FunctionsMap = std::map<std::string, std::unique_ptr<Function>>; 

	void InitVariable(const std::string& name);
	void SetVariable(const std::string& name, const std::string& value);
	void SetVariable(const std::string& name, const double value);
	void SetFunction(const std::string& name, const std::string& nameOfArg1,
		const std::string& nameOfArg2, Operations operation);
	void SetFunction(const std::string& name, const std::string& nameOfArg);

	VariablesMap GetAllVriables() const;	
	FunctionsMap GettAllFunctions() const;	
	Variable GetVariable(const std::string& name) const;	

private:
	VariablesMap m_variables;
	FunctionsMap m_functions;

	std::unique_ptr<Variable> FindVariable(const std::string& name) const;
	std::unique_ptr<Function> FindFunction(const std::string& name) const;
	std::unique_ptr<Variable> FindOperand(const std::string& name) const;
};