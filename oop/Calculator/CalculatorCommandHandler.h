#pragma once

#include "Calculator.h"
#include <string>
#include <sstream>
#include <functional>
#include <set>

class CalculatorCommandHandler
{
public: 
	CalculatorCommandHandler(Calculator& calculator, std::istream& input, std::ostream& output);

	void HandleCalculating();

private:
	Calculator m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<void(std::istream& stream)>;
	using ActionMap = std::map<std::string, Handler>;

	const ActionMap m_actionMap;

private:
	std::set<std::string> m_validOperations = { "+", "-", "*", "/" };

	void CheckIsVariableNameValid(const std::string& name) const;

	void CheckIsEqualSymbolValid(const std::string& equalSymbol) const;

	void CheckIsOperationSymbolValid(const std::string& operationSymbol) const;

	void HandleCommandVar(std::istream& stream);

	void HandleCommandLet(std::istream& stream);

	void HandleCommandFn(std::istream& stream);

	void HandleCommandPrint(std::istream& stream);

	void HandleCommandPrintVars() const;

	void HandleCommandPrintFns() const;

	Operations DefineOperation(const std::string& operation) const;
};