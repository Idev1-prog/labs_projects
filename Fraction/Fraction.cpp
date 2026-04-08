#include <iostream>
#include "Fraction.h"
#include <string>
#include <algorithm>

//Euclidean Algorithm for GCD(Revised Approach)
int gcd(int a, int b) {
	a = std::abs(a);
	b = std::abs(b);

	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}

	return a;
}

void Fraction::simplify() {
	if (_up == 0) {
		_down = 1;
		return;
	}

	int greatest_common_divisor = gcd(_up, _down);

	_up /= greatest_common_divisor;
	_down /= greatest_common_divisor;

	if (_down < 0) {
		_up = -_up;
		_down = -_down;
	}
}

void Fraction::check_invariant() const {}

Fraction::Fraction(int up, int down) {
	if (down == 0) {
		throw std::invalid_argument("division by zero");
	}
	_up = up;
	_down = down;
	simplify();
	check_invariant();
}

Fraction::Fraction(std::string input_str) {
	input_str.erase(std::remove(input_str.begin(), input_str.end(), ' '), input_str.end());

	if (input_str.empty()) {
		throw std::invalid_argument("Empty string");
	}

	size_t pos = input_str.find('/');

	if (pos == std::string::npos) { // npos - separator not found
		try {
			_up = std::stoi(input_str);
			_down = 1;
			simplify();
			check_invariant();
		}
		catch (const std::exception& e) {
			throw std::invalid_argument("Invalid number format");
		}
	}
	else {
		std::string left = input_str.substr(0, pos);
		std::string right = input_str.substr(pos + 1);

		if (left.empty() || right.empty()) {
			throw std::invalid_argument("Invalid fraction format");
		}

		try {
			_up = std::stoi(left);
			_down = std::stoi(right);

			if (_down == 0) {
				throw std::invalid_argument("division by zero");
			}

			simplify();
			check_invariant();
		}
		catch (const std::exception& e) {
			throw std::invalid_argument("Invalid number format");
		}
	}
}

void Fraction::up(int up) {
	_up = up;
	simplify();
	check_invariant();
}

void Fraction::down(int down) {
	if (down == 0) {
		throw std::invalid_argument("division by zero");
	}
	_down = down;
	simplify();
	check_invariant();
}

std::string Fraction::to_string() const {
	if (_down == 1) {
		return std::to_string(_up);
	}
	else {
		return std::to_string(_up) + "/" + std::to_string(_down);
	}
}

std::string Fraction::mixed_form() const {
	int whole = _up / _down;
	int remainder = std::abs(_up % _down);
	if (whole == 0) {
		return to_string();
	}
	else if (remainder == 0) {
		return std::to_string(whole);
	}
	else {
		return std::to_string(whole) + " " + std::to_string(remainder) + "/" + std::to_string(_down);
	}
}

Fraction& Fraction::operator+=(const Fraction& other) {
	_up = _up * other._down + other._up * _down;
	_down = _down * other._down;
	simplify();
	check_invariant();
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
	_up = _up * other._down - other._up * _down;
	_down = _down * other._down;
	simplify();
	check_invariant();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) {
	_up *= other._up;
	_down *= other._down;
	simplify();
	check_invariant();
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
	_up *= other._down;
	_down *= other._up;
	simplify();
	check_invariant();
	return *this;
}

Fraction& Fraction::operator=(const Fraction& other) {
	if (this != &other) {
		_up = other._up;
		_down = other._down;
	}
	simplify();
	check_invariant();
	return *this;
}

Fraction Fraction::operator+(const Fraction& other) const {
	Fraction result(*this);
	result += other;
	return result;
}

Fraction Fraction::operator-(const Fraction& other) const {
	Fraction result(*this);
	result -= other;
	return result;
}

Fraction Fraction::operator*(const Fraction& other) const {
	Fraction result(*this);
	result *= other;
	return result;
}

Fraction Fraction::operator/(const Fraction& other) const {
	Fraction result(*this);
	result /= other;
	return result;
}

bool Fraction::operator==(const Fraction& other) const {
	return (_up * other._down) == (_down * other._up);
}

bool Fraction::operator!=(const Fraction& other) const {
	return !(*this == other);
}

bool Fraction::operator<(const Fraction& other) const {
	return (_up * other._down) < (_down * other._up);
}

bool Fraction::operator>(const Fraction& other) const {
	return (_up * other._down) > (_down * other._up);
}

bool Fraction::operator<=(const Fraction& other) const {
	return !(other < *this);
}

bool Fraction::operator>=(const Fraction& other) const {
	return !(other > *this);
}