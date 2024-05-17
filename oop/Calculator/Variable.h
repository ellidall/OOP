#pragma once

#include <cmath>
#include <set>
#include <memory>
#include "Observable.h"

class Variable
{
public:
	Variable() : m_value(std::nan("")) {}
	Variable(double value) : m_value(value) {}

	double GetValue() const;
	void SetValue(double value);
	void AddSubscriber(Observable* subscriber);
	void NotifySubscribers() const;

private:
	double m_value;
	// изучить подробнее указатели
	// subscriber должен быть простым указателем
	// ссылки на переменные и фунции - unique_ptr
	// плохо, что SetValue усть в Function
	std::set<Observable*> m_subscribers;
};