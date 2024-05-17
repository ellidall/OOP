#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../date/CDate.h"

SCENARIO("Test get methods")
{
	CDate date;

	WHEN("Test GetYear")
	{
		REQUIRE(date.GetYear() == 1970);
	}

	WHEN("Test GetMonth")
	{
		REQUIRE(date.GetMonth() == Month::JANUARY);
	}

	WHEN("Test GetDay")
	{
		REQUIRE(date.GetDay() == 1);
	}

	WHEN("Test GetWeekDay")
	{
		REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
	}
}

SCENARIO("Test operators")
{
	WHEN("operator ++")
	{
		CDate date;
		++date;
		REQUIRE(date.GetDay() == 2);

		date++;
		REQUIRE(date.GetDay() == 3);
	}
	WHEN("operator --")
	{
		CDate date(3);
		--date;
		REQUIRE(date.GetDay() == 2);

		date--;
		REQUIRE(date.GetDay() == 1);

		REQUIRE_THROWS_AS(date--, std::invalid_argument);
	}
	WHEN("operator +")
	{
		CDate date(30, Month::JANUARY, 2024);
		date = date + 2; 
		REQUIRE((date.GetDay() == 1 && date.GetMonth() == Month::FEBRUARY && date.GetYear() == 2024));

		date = 2 + date;
		REQUIRE((date.GetDay() == 3 && date.GetMonth() == Month::FEBRUARY && date.GetYear() == 2024));
	}
	WHEN("operator -")
	{
		CDate date(30, Month::JANUARY, 2024);
		date = date - 30;
		REQUIRE((date.GetDay() == 31 && date.GetMonth() == Month::DECEMBER && date.GetYear() == 2023));

		CDate date2(1, Month::JANUARY, 2024);
		int result = date - date2;
		REQUIRE(result == -1);
	}
	WHEN("operator +=")
	{
		CDate date;
		date += 30;
		REQUIRE((date.GetDay() == 31 && date.GetMonth() == Month::JANUARY && date.GetYear() == 1970));

		CDate date2(31, Month::DECEMBER, 9999);
		REQUIRE_THROWS_AS(date2 += 1, std::invalid_argument);
	}
	WHEN("operator -=")
	{
		CDate date(31);
		date -= 30;
		REQUIRE((date.GetDay() == 1 && date.GetMonth() == Month::JANUARY && date.GetYear() == 1970));

		REQUIRE_THROWS_AS(date -= 1, std::invalid_argument);
	}
	WHEN("operator <<")
	{
		std::ostringstream out("");
		CDate date;
		out << date;
		REQUIRE(out.str() == "1.1.1970");
	}
	WHEN("operator >>")
	{
		std::istringstream in("1.1.1970");
		CDate date;
		in >> date;
		REQUIRE((date.GetDay() == 1 && date.GetMonth() == Month::JANUARY && date.GetYear() == 1970));

		std::istringstream in2("1.1.1969");
		CDate date2;
		REQUIRE_THROWS_AS(in >> date, std::invalid_argument);
	}
	WHEN("operator ==")
	{
		CDate date1;
		CDate date2;
		REQUIRE(date1 == date2);

		CDate date3(2);
		CDate date4;
		REQUIRE(!(date3 == date4));
	}
	WHEN("operator !=")
	{
		CDate date1;
		CDate date2(2);
		REQUIRE(date1 != date2);

		CDate date3;
		CDate date4;
		REQUIRE(!(date3 != date4));
	}
	WHEN("operator <")
	{
		CDate date1(1);
		CDate date2(2);
		REQUIRE(date1 < date2);

		CDate date3(2);
		CDate date4(1);
		REQUIRE(!(date3 < date4));

		CDate date5;
		CDate date6;
		REQUIRE(!(date5 < date6));
	}
	WHEN("operator >")
	{
		CDate date1(2);
		CDate date2(1);
		REQUIRE(date1 > date2);

		CDate date3(1);
		CDate date4(2);
		REQUIRE(!(date3 > date4));

		CDate date5;
		CDate date6;
		REQUIRE(!(date5 > date6));
	}
	WHEN("operator <=")
	{
		CDate date1(1);
		CDate date2(2);
		REQUIRE(date1 <= date2);

		CDate date3(2);
		CDate date4(1);
		REQUIRE(!(date3 <= date4));

		CDate date5;
		CDate date6;
		REQUIRE(date5 <= date6);
	}
	WHEN("operator >=")
	{
		CDate date1(2);
		CDate date2(1);
		REQUIRE(date1 >= date2);

		CDate date3(1);
		CDate date4(2);
		REQUIRE(!(date3 >= date4));

		CDate date5;
		CDate date6;
		REQUIRE(date5 >= date6);
	}
}

