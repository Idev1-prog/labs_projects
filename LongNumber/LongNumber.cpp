#include <iostream>
#include <string>
#include "LongNumber.h"

void LongNumber::normalize() {
	size_t first_non_zero = _number.find_first_not_of('0');
	if (first_non_zero == std::string::npos) {
		_number = "0";
		_sign = true;
	}
	else {
		_number = _number.substr(first_non_zero);
	}
}

int LongNumber::cmp_abs(const std::string& a, const std::string& b) const {
	if (a.length() != b.length()) {
		return a.length() > b.length() ? 1 : -1;
	}
	if (a == b) return 0;
	return a > b ? 1 : -1;
}

std::string LongNumber::add_abs(const std::string& a, const std::string& b) const {
	std::string res = "";
	int carry = 0;
	int i = a.length() - 1, j = b.length() - 1;

	while (i >= 0 || j >= 0 || carry) {
		int sum = carry;
		if (i >= 0) sum += a[i--] - '0';
		if (j >= 0) sum += b[j--] - '0';
		res.push_back((sum % 10) + '0');
		carry = sum / 10;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

std::string LongNumber::sub_abs(const std::string& a, const std::string& b) const {
	std::string res = "";
	int borrow = 0;
	int i = a.length() - 1, j = b.length() - 1;

	while (i >= 0) {
		int diff = (a[i--] - '0') - borrow;
		if (j >= 0) diff -= (b[j--] - '0');

		if (diff < 0) {
			diff += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}
		res.push_back(diff + '0');
	}
	std::reverse(res.begin(), res.end());
	return res;
}

LongNumber::LongNumber(const LongNumber& other) {
	_number = other._number;
	_sign = other._sign;
}

LongNumber::LongNumber(std::string number) {
	if (number.empty()) {
		_number = "0";
		_sign = true;
		return;
	}
	if (number[0] == '-') {
		_sign = false;
		_number = number.substr(1, number.size() - 1);
	}
	else {
		_sign = true;
		_number = number;
	}
	normalize();
}

void LongNumber::sign(char sign) {
	if (sign == '-' && _number != "0") _sign = false;
	else _sign = true;
}

void LongNumber::number(std::string number) {
	_number = (number[0] != '-') ? number : number.substr(1, number.size() - 1);
}

std::string LongNumber::to_string() const {
	std::string s1 = (!_sign) ? "-" : "";
	std::string s2 = _number;
	return s1 + s2;
}

LongNumber& LongNumber::operator=(const LongNumber& other) {
	if (this != &other) {
		_number = other._number;
		_sign = other._sign;
	}
	return *this;
}

LongNumber operator-(LongNumber input) {
	if (input.number() != "0") {
		input.sign(input.sign() ? '-' : '+');
	}
	return input;
}

LongNumber LongNumber::operator+(const LongNumber& other) const {
	LongNumber result;
	if (_sign == other._sign) {
		result._number = add_abs(_number, other._number);
		result._sign = _sign;
	}
	else {
		int cmp = cmp_abs(_number, other._number);
		if (cmp >= 0) {
			result._number = sub_abs(_number, other._number);
			result._sign = _sign;
		}
		else {
			result._number = sub_abs(other._number, _number);
			result._sign = other._sign;
		}
	}
	result.normalize();
	return result;
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
	return *this + (-other);
}

LongNumber LongNumber::operator*(const LongNumber& other) const { // Comments in Russian have been temporarily left for clarity
	if (_number == "0" || other._number == "0") return LongNumber("0");

	LongNumber final_res("0");
	std::string n2 = other._number;

	// Идем по цифрам второго числа справа налево
	for (int i = n2.size() - 1; i >= 0; --i) {
		int digit2 = n2[i] - '0';

		if (digit2 == 0) continue;

		// Умножаем всё первое число на одну цифру второго
		std::string current_digit = "";
		int carry = 0;
		for (int j = _number.size() - 1; j >= 0; --j) {
			int prod = (_number[j] - '0') * digit2 + carry;
			current_digit.push_back((prod % 10) + '0');
			carry = prod / 10;
		}
		if (carry) current_digit.push_back(carry + '0');
		std::reverse(current_digit.begin(), current_digit.end());

		// Добавляем нули в конец
		// Количество нулей зависит от того, какой это разряд
		int shift = n2.size() - 1 - i;
		for (int s = 0; s < shift; ++s) {
			current_digit.push_back('0');
		}

		// Суммируем с общим результатом
		final_res = final_res + LongNumber(current_digit);
	}

	// Определяем итоговый знак
	final_res._sign = (this->_sign == other._sign);

	final_res.normalize();

	return final_res;
}


LongNumber& LongNumber::operator+=(const LongNumber& other) {
	*this = *this + other;
	return *this;
}

LongNumber& LongNumber::operator-=(const LongNumber& other) {
	*this = *this - other;
	return *this;
}

LongNumber& LongNumber::operator*=(const LongNumber& other) {
	*this = *this * other;
	return *this;
}

bool LongNumber::operator<(const LongNumber& other) const {
	if (_sign != other._sign) return !_sign;

	int cmp = cmp_abs(_number, other._number);
	if (cmp == 0) return false;

	if (_sign) return cmp < 0;
	return cmp > 0;
}

bool LongNumber::operator>(const LongNumber& other) const {
	return other < *this;
}

bool LongNumber::operator==(const LongNumber& other) const {
	return (_number == other._number && _sign == other._sign);
}

bool LongNumber::operator!=(const LongNumber& other) const {
	return !(_number == other._number && _sign == other._sign);
}

bool LongNumber::operator<=(const LongNumber& other) const {
	return !(*this > other);
}

bool LongNumber::operator>=(const LongNumber& other) const {
	return !(*this < other);
}

char LongNumber::operator[](const size_t i) const noexcept{
	if (_sign) return _number[i];
	else {
		return (i != 0) ? _number[i - 1] : '-';
	}
}

LongNumber LongNumber::operator++(int) noexcept {
	LongNumber ex(*this);
	*this += LongNumber("1");
	return ex;
}

LongNumber LongNumber::operator--(int) noexcept {
	LongNumber ex(*this);
	*this -= LongNumber("1");
	return ex;
}

LongNumber& LongNumber::operator++() noexcept {
	*this += LongNumber("1");
	return *this;
}

LongNumber& LongNumber::operator--() noexcept {
	*this -= LongNumber("1");
	return *this;
}

std::ostream& operator<<(std::ostream& out, const LongNumber& num) {
	out << num.number();
	return out;
}

std::istream& operator>>(std::istream& in, LongNumber& num) {
	std::string str;
	std::getline(in, str);
	num.number(str);
	return in;
}