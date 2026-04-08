#pragma once
#include <string>
class Fraction {
protected:
	int _up, _down;
	void simplify();
	virtual void check_invariant() const;
public:
	Fraction() : _up(0), _down(1) {};
	Fraction(int, int);
	Fraction(int up) : _up(up), _down(1) {}; // thanks to it, the compiler will convert objects to the required type
	Fraction(std::string);
	Fraction(const Fraction& other) : _up(other._up), _down(other._down) {};

	inline int up() const noexcept { return _up; };
	inline int down() const noexcept { return _down; };
	std::string to_string() const;
	std::string mixed_form() const;

	virtual void up(int);
	virtual void down(int);

	virtual Fraction& operator+=(const Fraction&);
	virtual Fraction& operator-=(const Fraction&);
	virtual Fraction& operator*=(const Fraction&);
	virtual Fraction& operator/=(const Fraction&);

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