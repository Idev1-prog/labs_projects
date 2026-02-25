#pragma once
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
	_hour = hour;
	_minute = minute;
	_second = 0;
}

void CTime::hour(char hour) {
	this->_hour = hour;
}

void CTime::minute(char minute) {
	this->_minute = minute;
}

void CTime::second(char second) {
	this->_second = second;
}