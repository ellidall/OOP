#include "CDate.h"

char CDate::SEPARATOR = '.';

unsigned CDate::GetTimestamp() const
{
	return m_timestamp;
}

unsigned CDate::GetYear() const
{
	unsigned year = MIN_YEAR;
	unsigned days = m_timestamp;

	// сделать без цикла
	while (days > static_cast<unsigned>(IsLeapYear(year) ? 366 : 365))
	{
		days -= IsLeapYear(year) ? 366 : 365;
		year++;
	}

	return year;
}

Month CDate::GetMonth() const
{
	unsigned year = MIN_YEAR;
	Month month = Month::JANUARY;
	unsigned days = m_timestamp;

	while (days > static_cast<unsigned>(IsLeapYear(year) ? 366 : 365))
	{
		days -= IsLeapYear(year) ? 366 : 365;
		year++;
	}
	
	unsigned daysInMonth = GetDaysInMonth(month, year);
	while (days > daysInMonth)
	{
		days -= daysInMonth;
		month = static_cast<Month>(static_cast<unsigned>(month) + 1);
		daysInMonth = GetDaysInMonth(month, year);
	}

	return month;
}

unsigned CDate::GetDay() const
{
	unsigned year = MIN_YEAR;
	Month month = Month::JANUARY;
	unsigned days = m_timestamp;

	while (days > static_cast<unsigned>(IsLeapYear(year) ? 366 : 365))
	{
		days -= IsLeapYear(year) ? 366 : 365;
		year++;
	}
	
	unsigned daysInMonth = GetDaysInMonth(month, year);
	while (days > daysInMonth)
	{
		days -= daysInMonth;
		month = static_cast<Month>(static_cast<unsigned>(month) + 1);
		daysInMonth = GetDaysInMonth(month, year);
	}

	return days;
}

WeekDay CDate::GetWeekDay() const
{
	unsigned day = (m_timestamp - MIN_DAY + DAYS_OFFSET_FOR_START_DATE) % DAYS_OF_WEEK;
	return static_cast<WeekDay>(day);
}

bool CDate::IsLeapYear(unsigned year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned CDate::GetDaysInMonth(Month month, unsigned year) const
{
	switch (month)
	{
	case Month::APRIL:
	case Month::JUNE:
	case Month::SEPTEMBER:
	case Month::NOVEMBER:
		return 30;
	case Month::FEBRUARY:
		return IsLeapYear(year) ? 29 : 28;
	default:
		return 31;
	}
}

bool CDate::IsValidDate(unsigned day, Month month, unsigned year) const
{
	if (year < MIN_YEAR || year >= MAX_YEAR + 1)
		return false;
	if (static_cast<unsigned>(month) < MIN_MONTH || static_cast<unsigned>(month) > MAX_MONTH)
		return false;
	if (day < 1 || day > GetDaysInMonth(month, year))
		return false;
	return true;
}

bool CDate::IsValidTimestamp() const
{
	unsigned day = GetDay();
	Month month = GetMonth();
	unsigned year = GetYear();
	return IsValidDate(day, month, year);
}

unsigned CDate::DateToTimestamp(unsigned day, Month month, unsigned year) const
{
	unsigned days = 0;
	for (unsigned y = 1970; y < year; ++y)
		days += IsLeapYear(y) ? 366 : 365;
	for (unsigned m = 1; m < static_cast<unsigned>(month); ++m)
		days += GetDaysInMonth(static_cast<Month>(m), year);
	days += day;
	return days;
}

CDate& CDate::operator++()
{
	++m_timestamp;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp = *this;
	++(*this);
	return temp;
}

CDate& CDate::operator--()
{
	--m_timestamp;
	if (!IsValidTimestamp())
		throw std::invalid_argument("ERROR: Result of the operation is an invalid date");
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp = *this;
	--(*this);
	return temp;
}

CDate operator+(const CDate& date1, const CDate& date2)
{
	return CDate(date1.GetTimestamp() + date2.GetTimestamp());
}

CDate CDate::operator-(unsigned days) const
{
	return CDate(m_timestamp - days);
}

int CDate::operator-(const CDate& date2) const
{
	return static_cast<int>(m_timestamp) - static_cast<int>(date2.m_timestamp);
}

CDate& CDate::operator+=(unsigned days)
{
	m_timestamp += days;
	if (!IsValidTimestamp())
		throw std::invalid_argument("ERROR: Result of the operation is an invalid date");
	return *this;
}

CDate& CDate::operator-=(unsigned days)
{
	m_timestamp -= days;
	if (!IsValidTimestamp())
		throw std::invalid_argument("ERROR: Result of the operation is an invalid date");
	return *this;
}

std::ostream& operator<<(std::ostream& out, const CDate& date)
{
	out << date.GetDay() << '.' << static_cast<unsigned>(date.GetMonth()) << '.' << date.GetYear();
	return out;
}

std::istream& operator>>(std::istream& in, CDate& date)
{
	unsigned year;
	unsigned month;
	unsigned day;
	char dot1;
	char dot2;

	in >> day >> dot1 >> month >> dot2 >> year;

	if (dot1 != CDate::SEPARATOR || dot2 != CDate::SEPARATOR)
	{
		in.setstate(std::ios::badbit);
	}

	date = CDate(day, static_cast<Month>(month), year);
	return in;
}