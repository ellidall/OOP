#pragma once

#include <iostream>
#include <stdexcept>

enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE,
	JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
	static char SEPARATOR;

	CDate(unsigned day, Month month, unsigned year)
	{
		if (!IsValidDate(day, month, year))
			throw std::invalid_argument("ERROR: Invalid date");
		m_timestamp = DateToTimestamp(day, month, year);
	}

	CDate(unsigned timestamp) : m_timestamp(timestamp) 
	{
		if (!IsValidTimestamp())
			throw std::invalid_argument("ERROR: Invalid date");
	}

	CDate() : m_timestamp(MIN_DAY) {}

	unsigned GetTimestamp() const;
	unsigned GetYear() const;
	Month GetMonth() const;
	unsigned GetDay() const;
	WeekDay GetWeekDay() const;

	CDate& operator++();
	CDate operator++(int);
	CDate& operator--();
	CDate operator--(int);
	CDate operator-(unsigned days) const;
	int operator-(const CDate& date2) const;
	CDate& operator+=(unsigned days);
	CDate& operator-=(unsigned days);

	friend std::ostream& operator<<(std::ostream& out, const CDate& date);
	friend std::istream& operator>>(std::istream& in, CDate& date);
	
	auto operator<=>(const CDate& other) const = default;

private:
	constexpr static const unsigned MIN_YEAR = 1970;
	constexpr static const unsigned MAX_YEAR = 9999;
	constexpr static const unsigned DAYS_OFFSET_FOR_START_DATE = 4;
	constexpr static const unsigned MIN_MONTH = 1;
	constexpr static const unsigned MAX_MONTH = 12;
	constexpr static const unsigned MIN_DAY = 1;
	constexpr static const unsigned DAYS_OF_WEEK = 7;

	unsigned m_timestamp;

	bool IsLeapYear(unsigned year) const;
	unsigned GetDaysInMonth(Month month, unsigned year) const;
	bool IsValidDate(unsigned day, Month month, unsigned year) const;
	// убрать метод, не позволять создавать объект с невалидным значением
	bool IsValidTimestamp() const;
	unsigned DateToTimestamp(unsigned day, Month month, unsigned year) const;
};

CDate operator+(const CDate& date1, const CDate& date2);