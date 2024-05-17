#include "Function.h"

double Function::GetOperationResult() const
{
	switch (m_operation)
	{
	case Operations::Non:
		return m_arg1->GetValue();
	case Operations::Plus:
		return m_arg1->GetValue() + m_arg2->GetValue();
	case Operations::Minus:
		return m_arg1->GetValue() - m_arg2->GetValue();
	case Operations::Multiplication:
		return m_arg1->GetValue() * m_arg2->GetValue();
	case Operations::Division:
	{
		const double denominator = m_arg2->GetValue();
		if (denominator == 0)
		{
			throw std::invalid_argument("Denominator cannot be zero");
		}
		return m_arg1->GetValue() / m_arg2->GetValue();
	}
	default:
		throw std::invalid_argument("Unknown command");
	}
}

void Function::Update()
{
	SetValue(GetOperationResult());
}