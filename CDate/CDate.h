#pragma once
class CDate {
private:
	int _day;
	int _month;
	int _year;

	bool isLeapYear(int year) const;

public:
	CDate();
	CDate(int, int, int);
	CDate(const CDate&);
	CDate(int, int);

	int day() const noexcept;
	int month() const noexcept;
	int year() const noexcept;

	void day(int);
	void month(int);
	void year(int);

	CDate add_days(int days);
	CDate add_months(int months);
	CDate add_years(int years);

	int daysInMonth(int month, int year) const;
};