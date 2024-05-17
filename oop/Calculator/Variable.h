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
	// ������� ��������� ���������
	// subscriber ������ ���� ������� ����������
	// ������ �� ���������� � ������ - unique_ptr
	// �����, ��� SetValue ���� � Function
	std::set<Observable*> m_subscribers;
};