#pragma once
#include <string>

class Complex {
	double _re, _im;
public:
	Complex();
	Complex(double, double);
	Complex(const Complex&);
	Complex(std::string);

	inline double re() const noexcept;
	inline double im() const noexcept;

	void re(double);
	void im(double);

	Complex operator + (const Complex&);
	Complex operator - (const Complex&);
	Complex operator * (const Complex&);
	//Complex operator / (const Complex&); TBD
	Complex operator += (const Complex&);
	Complex operator -= (const Complex&);

};


inline double Complex::re() const noexcept {
	return _re;
}

inline double Complex::im() const noexcept {
	return _im;
}

