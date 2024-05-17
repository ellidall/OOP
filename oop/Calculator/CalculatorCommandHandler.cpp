#include "CalculatorCommandHandler.h"

const std::string COMMAND_VAR = "var";
const std::string COMMAND_LET = "let";
const std::string COMMAND_FN = "fn";
const std::string COMMAND_PRINT = "print";
const std::string COMMAND_PRINTVARS = "printvars";
const std::string COMMAND_PRINTFNS = "printfns";
const std::string EQUAL_SYMBOL = "=";

CalculatorCommandHandler::CalculatorCommandHandler(
	Calculator& calculator, std::istream& input, std::ostream& output
)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ 
		{ COMMAND_VAR,       [this](std::istream& stream) { return HandleCommandVar(stream); } }, 
		{ COMMAND_LET,       [this](std::istream& stream) { return HandleCommandLet(stream); } },
		{ COMMAND_FN,        [this](std::istream& stream) { return HandleCommandFn(stream); } },
		{ COMMAND_PRINT,     [this](std::istream& stream) { return HandleCommandPrint(stream); } },
		{ COMMAND_PRINTVARS, [this](std::istream& stream) { return HandleCommandPrintVars(); } },
		{ COMMAND_PRINTFNS,  [this](std::istream& stream) { return HandleCommandPrintFns(); } },
	})
{
}

void CalculatorCommandHandler::CheckIsVariableNameValid(const std::string& name) const
{
	if (name.empty() || std::isdigit(name[0]))
	{
		throw std::invalid_argument("Error: Variable name is invalid");
	}
}

void CalculatorCommandHandler::CheckIsEqualSymbolValid(const std::string& equalSymbol) const
{
	if (equalSymbol != EQUAL_SYMBOL)
	{
		throw std::invalid_argument("Error: Equal symbol should be '" + EQUAL_SYMBOL + "'");
	}
}

void CalculatorCommandHandler::CheckIsOperationSymbolValid(const std::string& operationSymbol) const
{
	if (m_validOperations.find(operationSymbol) == m_validOperations.end())
	{
		throw std::invalid_argument("Error: Operation " + operationSymbol + " is invalid");
	}
}

void CalculatorCommandHandler::HandleCommandVar(std::istream& stream)
{
	std::string variableName;
	stream >> variableName;

	CheckIsVariableNameValid(variableName);
	m_calculator.InitVariable(variableName);
}

void CalculatorCommandHandler::HandleCommandLet(std::istream& stream)
{
	std::string variableName;
	std::string equalSymbol;
	std::string value;
	stream >> variableName >> equalSymbol >> value;

	CheckIsVariableNameValid(variableName);
	CheckIsEqualSymbolValid(equalSymbol);
	
	try
	{ 
		double numericValue = std::stod(value);
		m_calculator.SetVariable(variableName, numericValue);
	}
	catch (const std::exception& e)
	{
		CheckIsVariableNameValid(value);
		m_calculator.SetVariable(variableName, value);
	}

	return;
}

Operations CalculatorCommandHandler::DefineOperation(const std::string& operation) const
{
	if (operation == "+")
	{
		return Operations::Plus;
	}
	else if (operation == "-")
	{
		return Operations::Minus;
	}
	else if (operation == "*")
	{
		return Operations::Multiplication;
	}
	else if (operation == "/")
	{
		return Operations::Division;
	}
	else
	{
		return Operations::Non;
	}
}

void CalculatorCommandHandler::HandleCommandFn(std::istream& stream)
{
	std::string functionName;
	std::string equalSymbol;
	std::string nameOfArg1;
	std::string operationSymbol;
	std::string nameOfArg2;
	stream >> functionName >> equalSymbol >> nameOfArg1 >> operationSymbol >> nameOfArg2;

	CheckIsVariableNameValid(functionName);
	CheckIsEqualSymbolValid(equalSymbol);
	CheckIsVariableNameValid(nameOfArg1);
	if (!operationSymbol.empty())
	{
		CheckIsOperationSymbolValid(operationSymbol);
		if (!nameOfArg2.empty())
		{
			CheckIsVariableNameValid(nameOfArg2);
		}
	}

	Operations operation = DefineOperation(operationSymbol);
	if (operation == Operations::Non)
	{
		m_calculator.SetFunction(functionName, nameOfArg1);
	}
	else
	{
		m_calculator.SetFunction(functionName, nameOfArg1, nameOfArg2, operation);
	}
}

void CalculatorCommandHandler::HandleCommandPrint(std::istream& stream)
{
	std::string variableName;
	stream >> variableName;

	CheckIsVariableNameValid(variableName);

	m_output << std::fixed << std::setprecision(2) << m_calculator.GetVariable(variableName).GetValue() << std::endl;
}

void CalculatorCommandHandler::HandleCommandPrintVars() const
{
	auto variablesMap = m_calculator.GetAllVriables();
	for (const auto& pair : variablesMap)
	{
		m_output << pair.first << ":" << std::fixed << std::setprecision(2) << pair.second->GetValue() << std::endl;
	}
}

void CalculatorCommandHandler::HandleCommandPrintFns() const
{
	auto functionsMap = m_calculator.GettAllFunctions();
	for (const auto& pair : functionsMap)
	{
		m_output << pair.first << ":" << std::fixed << std::setprecision(2) << pair.second->GetValue() << std::endl;
	}
}

void CalculatorCommandHandler::HandleCalculating()
{
	try
	{
		std::string commandLine;
		getline(m_input, commandLine);
		std::istringstream stream(commandLine);

		std::string command;
		if (!(stream >> command))
		{
			throw std::invalid_argument("Invalid: Usage: <command> <action>");
		}

		auto it = m_actionMap.find(command);
		if (it == m_actionMap.end())
		{
			throw std::invalid_argument("Error: Unknown command");
		}

		it->second(stream);
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
	
}