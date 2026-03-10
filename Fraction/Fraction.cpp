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

Fraction::Fraction(int up, int down) {
	if (down == 0) {
		throw std::invalid_argument("division by zero");
	}
	_up = up;
	_down = down;
	simplify();
}

void Fraction::up(int up) noexcept {
	_up = up;
	simplify();
}

void Fraction::down(int down) {
	if (down == 0) {
		throw std::invalid_argument("division by zero");
	}
	_down = down;
	simplify();
}

std::string Fraction::to_string(){
	if (_down == 1) {
		return std::to_string(_up);
	}
	else {
		return std::to_string(_up) + "/" + std::to_string(_down);
	}
}

Fraction& Fraction::operator+=(const Fraction& other) {
	_up = _up * other._down + other._up * _down;
	_down = _down * other._down;
	simplify();
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
	_up = _up * other._down - other._up * _down;
	_down = _down * other._down;
	simplify();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) {
	_up *= other._up;
	_down *= other._down;
	simplify();
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
	_up *= other._down;
	_down *= other._up;
	simplify();
	return *this;
}

Fraction& Fraction::operator=(const Fraction& other) {
	if (this != &other) {
		_up = other._up;
		_down = other._down;
	}
	simplify();
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