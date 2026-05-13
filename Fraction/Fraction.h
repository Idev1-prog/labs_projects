#pragma once
#include <string>

class Fraction {
protected:
	int _up, _down;
	virtual void simplify();
	virtual void check_invariant() const;

public:
	Fraction() : _up(0), _down(1) {}
	Fraction(int, int);
	Fraction(int up) : _up(up), _down(1) {}
	Fraction(std::string);
	Fraction(const Fraction& other) : _up(other._up), _down(other._down) {}
	virtual Fraction to_improper() const { return *this; }

	inline int up() const noexcept { return _up; }
	inline int down() const noexcept { return _down; }

	virtual std::string to_string() const;
	std::string mixed_form() const;

	virtual void up(int);
	virtual void down(int);

	virtual void to_improper(int& num, int& den) {
		num = _up;
		den = _down;
	}

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