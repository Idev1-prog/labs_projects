#pragma once
#include <string>
class Fraction {
private:
	int _up, _down;
	void simplify();
public:
	Fraction() : _up(0), _down(1) {};
	Fraction(int, int);
	Fraction(int up) : _up(up), _down(1) {}; // thanks to it, the compiler will convert objects to the required type
	//Fraction(std::string) TBD;
	Fraction(const Fraction& other) : _up(other._up), _down(other._down) {};

	inline int up() const noexcept { return _up; };
	inline int down() const noexcept { return _down; };
	std::string to_string();

	void up(int) noexcept;
	void down(int);

	Fraction& operator+=(const Fraction&);
	Fraction& operator-=(const Fraction&);
	Fraction& operator*=(const Fraction&);
	Fraction& operator/=(const Fraction&);

	Fraction& operator=(const Fraction&);

	Fraction operator+(const Fraction&) const;
	Fraction operator-(const Fraction&) const;
	Fraction operator*(const Fraction&) const;
	Fraction operator/(const Fraction&) const;

	bool operator==(const Fraction&) const;
	bool operator!=(const Fraction&) const;
	bool operator>(const Fraction&) const;
	bool operator<(const Fraction&) const;
	bool operator<=(const Fraction&) const;
	bool operator>=(const Fraction&) const;
};