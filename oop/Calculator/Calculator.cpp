#include "Calculator.h"

std::unique_ptr<Variable> Calculator::FindVariable(const std::string& name) const
{
	const auto it = m_variables.find(name);
	if (it != m_variables.end())
	{
		return it->second;
	}

	return nullptr;
}

std::unique_ptr<Function> Calculator::FindFunction(const std::string& name) const
{
	const auto it = m_functions.find(name);
	if (it != m_functions.end())
	{
		return std::move(it->second);
	}

	return nullptr;
}

std::unique_ptr<Variable> Calculator::FindOperand(const std::string& name) const
{
	auto variable = FindVariable(name);
	auto function = FindFunction(name);
	if (variable != nullptr)
	{
		return std::move(variable);
	}
	else if (function != nullptr)
	{
		return std::move(function);
	}

	return nullptr;
}

Variable Calculator::GetVariable(const std::string& name) const
{
	const auto operand = FindOperand(name);
	if (operand == nullptr)
	{
		throw std::invalid_argument("Error: '" + name + "' is not initialized");
	}

	return *operand;
}

void Calculator::InitVariable(const std::string& name)
{
	if (FindOperand(name) != nullptr)
	{
		throw std::invalid_argument("Error: Variable '" + name + "' has already been initialized");
	}
	
	auto variable = std::make_unique<Variable>();
	m_variables.emplace(name, variable);
	return;
}

void Calculator::SetVariable(const std::string& name, const std::string& assignableVariableName)
{
	const auto variable = FindOperand(assignableVariableName);
	if (variable == nullptr)
	{
		throw std::invalid_argument("Error: '" + assignableVariableName + "' is not initialized");
	}

	const auto variableByName = FindVariable(name);
	const auto functionByName = FindFunction(name);
	if (variableByName != nullptr && functionByName == nullptr)
	{
		variableByName->SetValue(variable->GetValue());
	}
	else if (variableByName == nullptr && functionByName == nullptr)
	{
		auto newVariable = std::make_unique<Variable>(variable->GetValue());
		m_variables.emplace(name, newVariable);
	}

	return;
}

void Calculator::SetVariable(const std::string& name, const double value)
{
	const auto variable = FindVariable(name);
	const auto function = FindFunction(name);
	if (variable != nullptr && function == nullptr)
	{
		variable->SetValue(value);
	}
	else if (variable == nullptr && function == nullptr)
	{
		auto newVariable = std::make_unique<Variable>(value);
		m_variables.emplace(name, newVariable);
	}

	return;
}

void Calculator::SetFunction(const std::string& name, const std::string& nameOfArg1,
	const std::string& nameOfArg2, Operations operation)
{
	const auto function = FindOperand(name);
	if (function != nullptr)
	{
		throw std::runtime_error("Error: '" + name + "' has already been defined");
	}

	const auto variable1 = FindOperand(nameOfArg1);
	const auto variable2 = FindOperand(nameOfArg2);
	if (variable1 == nullptr || variable2 == nullptr)
	{
		throw std::invalid_argument("Error: '" + nameOfArg1 + "' or '" + nameOfArg2 + "' is not initialized");
	}

	// переделать на обычный указатель
	Function* newFunction = new Function(std::move(variable1), variable2, operation);
	variable1->AddSubscriber(newFunction);
	variable2->AddSubscriber(newFunction);
	m_functions.emplace(name, newFunction);

	return;
}

void Calculator::SetFunction(const std::string& name, const std::string& nameOfArg)
{
	const auto function = FindOperand(name);
	if (function != nullptr)
	{
		throw std::runtime_error("Error: '" + name + "' has already been defined");
		
	}

	const auto variable = FindOperand(nameOfArg);
	if (variable == nullptr)
	{
		throw std::invalid_argument("Error: '" + nameOfArg + "' is not initialized");
	}

	auto newFunction = std::make_unique<Function>(variable);
	m_functions.emplace(name, newFunction);

	return;
}

Calculator::VariablesMap Calculator::GetAllVriables() const {return std::move(m_variables); }

Calculator::FunctionsMap Calculator::GettAllFunctions() const { return m_functions; }