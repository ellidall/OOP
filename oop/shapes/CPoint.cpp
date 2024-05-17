#include "CPoint.h"

void CPoint::SetX(double x)
{
	this->m_x = x;
}

void CPoint::SetY(double y)
{
	this->m_y = y;
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

bool CPoint::operator==(CPoint const& other) const
{
	return m_x == other.m_x && m_y == other.m_y;
}
