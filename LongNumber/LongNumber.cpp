#include <iostream>
#include <string>
#include "LongNumber.h"

LongNumber::LongNumber(const LongNumber& other) {
	_number = other._number;
	_sign = other._sign;
}

LongNumber::LongNumber(std::string number) {
	if (number[0] == '-') {
		_sign = false;
		_number = number.substr(1, number.size() - 1);
	}
	else {
		_sign = true;
		_number = number;
	}
}

void LongNumber::sign(char sign) {
	if (sign == '-') _sign = false;
	else _sign = true;
}

void LongNumber::number(std::string number) {
	_number = (number[0] != '-') ? number : number.substr(1, number.size() - 1);
}

//LongNumber& LongNumber::operator+=(const LongNumber& other) {
//}
//
//LongNumber& LongNumber::operator-=(const LongNumber& other) {
//}

bool LongNumber::operator>(const LongNumber& other) {
	if (_sign > other._sign) {
		return true;
	}
	size_t o_size = other._number.size();
	size_t size = _number.size();
	if (size > o_size)
		return true;
	else if (size < o_size) {
		return false;
	}
	for (int i = _number.size(); i > 0; i--) {
		if (_number[i] > other._number[i]) {
			return true;
		}
	}
	return false;
}

bool LongNumber::operator<(const LongNumber& other) {
	if (_sign < other._sign) {
		return true;
	}
	size_t o_size = other._number.size();
	size_t size = _number.size();
	if (size < o_size)
		return true;
	else if (size > o_size) {
		return false;
	}
	for (int i = _number.size(); i > 0; i--) {
		if (_number[i] < other._number[i]) {
			return true;
		}
	}
	return false;
}

bool LongNumber::operator==(const LongNumber& other) {
	return (_number == other._number && _sign == other._sign);
}

bool LongNumber::operator!=(const LongNumber& other) {
	return !(_number == other._number && _sign == other._sign);
}

LongNumber& operator-(LongNumber& input) {
	input._sign = (input._sign == false) ? true : false;
	return input;
}