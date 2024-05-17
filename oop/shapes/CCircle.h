#pragma once

#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint start, CPoint end);
	CLineSegment(CPoint start, CPoint end, uint32_t color);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void SetStartPoint(CPoint newStartPoint);
	void SetEndPoint(CPoint newEndPoint);
	void SetOutlineColor(uint32_t newColor);

private:
	uint32_t m_outlineColor = 0xFF0000;
	CPoint m_startPoint;
	CPoint m_endPoint;
};