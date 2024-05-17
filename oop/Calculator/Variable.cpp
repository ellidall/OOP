#include "Variable.h"

double Variable::GetValue() const { return m_value; }

void Variable::SetValue(double value) 
{ 
	m_value = value;
	NotifySubscribers();
}

void Variable::AddSubscriber(Observable* subscriber)
{
	m_subscribers.insert(subscriber);
}

void Variable::NotifySubscribers() const
{
	for (auto sub : m_subscribers)
	{
		sub->Update();
	}
}