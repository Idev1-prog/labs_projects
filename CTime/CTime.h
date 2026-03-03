#pragma once
#define HOURS_ERR_MESSAGE "Hours should be between 0 and 23"
#define MINUTES_ERR_MESSAGE "Minutes must be between 0 and 59"
#define SECONDS_ERR_MESSAGE "Seconds should be between 0 and 59"

class CTime {
	char _hour;
	char _minute;
	char _second;
public:
	// default constructor !!!
	CTime();
	// initialization constructor
	CTime(char, char, char);
	// copy constructor !!!
	CTime(const CTime&);
	// additional constructors
	CTime(char, char);

	// getters
	char hour() const noexcept;
	char minute() const noexcept;
	char second() const noexcept;

	// setters
	void hour(char);
	void minute(char);
	void second(char);

	// addition methods
	CTime add_hours(char hours);
	CTime add_minutes(char minutes);
	CTime add_seconds(char seconds);
};

CTime::CTime() {
	_hour = 1;
	_minute = 3;
	_second = 4;
}

char CTime::hour() const noexcept {
	return _hour;
}

char CTime::minute() const noexcept {
	return _minute;
}

char CTime::second() const noexcept {
	return _second;
}

CTime::CTime(char hour, char minute, char second) {
	if (hour < 0 || hour > 23) throw std::out_of_range(HOURS_ERR_MESSAGE);
	if (minute < 0 || minute > 59) throw std::out_of_range(MINUTES_ERR_MESSAGE);
	if (second < 0 || second > 59) throw std::out_of_range(SECONDS_ERR_MESSAGE);
	_hour = hour;
	_minute = minute;
	_second = second;
}

CTime::CTime(const CTime& other) {
	_hour = other._hour;
	_minute = other._minute;
	_second = other._second;
}

CTime::CTime(char hour, char minute) {
	if (hour < 0 || hour > 23) throw std::out_of_range(HOURS_ERR_MESSAGE);
	if (minute < 0 || minute > 59) throw std::out_of_range(MINUTES_ERR_MESSAGE);
	_hour = hour;
	_minute = minute;
	_second = 0;
}

void CTime::hour(char hour) {
	if (hour < 0 || hour > 23) throw std::out_of_range(HOURS_ERR_MESSAGE);
	this->_hour = hour;
}

void CTime::minute(char minute) {
	if (minute < 0 || minute > 59) throw std::out_of_range(MINUTES_ERR_MESSAGE);
	this->_minute = minute;
}

void CTime::second(char second) {
	if (second < 0 || second > 59) throw std::out_of_range(SECONDS_ERR_MESSAGE);
	this->_second = second;
}

CTime CTime::add_hours(char hours) {
	CTime res(*this);
	res._hour = (res._hour + hours) % 24;
	return res;
}

CTime CTime::add_minutes(char minutes) {
	CTime res(*this);
	int total_minutes = res._minute + minutes;
	int extra_hours = total_minutes / 60;
	res._minute = total_minutes % 60;
	res._hour = (res._hour + extra_hours) % 24;
	return res;
}

CTime CTime::add_seconds(char seconds) {
	CTime res(*this);
	int total_seconds = res._second + seconds;
	int extra_minutes = total_seconds / 60;
	res._second = total_seconds % 60;

	if (extra_minutes > 0) {
		res = res.add_minutes(extra_minutes);
	}
	return res;
}