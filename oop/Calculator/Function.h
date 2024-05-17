#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "Variable.h"

enum class Operations
{
	Plus,
	Minus,
	Multiplication,
	Division,
	Non,
};

//метод SetValue не нужен
class Function : public Variable, public Observable
{
public:
	Function(std::unique_ptr<Variable> arg1, std::unique_ptr<Variable> arg2, Operations operation)
		: Variable(std::nan(""))
		, m_arg1(std::move(arg1))
		, m_arg2(std::move(arg2))
		, m_operation(operation)
	{
		SetValue(GetOperationResult());
	}

	Function(std::unique_ptr<Variable> arg1)
		: Variable(arg1->GetValue())
		, m_arg1(std::move(arg1))
		, m_arg2(nullptr)
		, m_operation(Operations::Non)
	{
	}

	void Update() override;

private:
	std::unique_ptr<Variable> m_arg1;
	std::unique_ptr<Variable> m_arg2;
	Operations m_operation;

	double GetOperationResult() const;
};