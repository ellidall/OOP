#pragma once

class CPoint
{
private:
	double m_x;
	double m_y;

public:
	CPoint(double x, double y)
		: m_x(x)
		, m_y(y)
	{};

	void SetX(double x);
	void SetY(double y);
	double GetX() const;
	double GetY() const;
	bool operator==(CPoint const& other) const;
};