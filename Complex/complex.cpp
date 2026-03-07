#include <iostream>
#include "complex.h"
#include <string>
#include <algorithm>

Complex::Complex() {
	_re = 0;
	_im = 0;
}

Complex::Complex(const Complex& other) :
	_re(other._re), _im(other._im) {}

Complex::Complex(double real, double imaginary) {
	_re = real;
	_im = imaginary;
}

Complex::Complex(std::string input_str) {
	input_str.erase(std::remove(input_str.begin(), input_str.end(), ' '), input_str.end());
	if (!input_str.empty() && input_str.back() == 'i') {
		input_str.pop_back();
	}
	else throw std::invalid_argument("0");
	size_t pos = input_str.find_last_of("+-");
	if (pos != std::string::npos && pos > 0) {
		std::string left = input_str.substr(0, pos);
		std::string right = input_str.substr(pos);
		_re = std::stod(left);
		_im = std::stod(right);
	}
	else throw std::invalid_argument("1");

}

void Complex::re(double real) {
	_re = real;
}

void Complex::im(double imaginary) {
	_im = imaginary;
}

Complex Complex::operator +(const Complex& other) const {
	return Complex(_re + other._re, _im + other._im);
}

Complex Complex::operator -(const Complex& other) const {
	return Complex(_re - other._re, _im - other._im);
}

Complex Complex::operator *(const Complex& other) const {
	return Complex(
		_re * other._re - _im * other._im,
		_re * other._im + _im * other._re
	);
}

Complex& Complex::operator +=(const Complex& other) {
	_re += other._re;
	_im += other._im;
	return *this;
}

Complex& Complex::operator -=(const Complex& other) {
	_re -= other._re;
	_im -= other._im;
	return *this;
}

Complex& Complex::operator=(const Complex& other) {
	if (this != &other) {
		_re = other._re;
		_im = other._im;
	}
	return *this;
}

Complex Complex::operator/(const Complex& other) const {

	double denominator = other._re * other._re + other._im * other._im;

	if (denominator == 0) {
		throw std::runtime_error("Division by zero complex number");
	}

	double real_part = (_re * other._re + _im * other._im) / denominator;
	double imag_part = (_im * other._re - _re * other._im) / denominator;

	return Complex(real_part, imag_part);
}

Complex& Complex::operator/=(const Complex& other) {
	*this = *this / other;
	return *this;
}
