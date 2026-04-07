#pragma once
#include "Fraction.h"

class RightFraction : public Fraction {
protected:
	void check_invariant() const override;
public:
	RightFraction() : Fraction() {};
	RightFraction(int, int);
	RightFraction(int);
	RightFraction(const std::string&);
	RightFraction(const RightFraction& other) : Fraction(other) {};
	RightFraction(const Fraction&);

	RightFraction& operator=(const RightFraction&);
	RightFraction& operator=(const Fraction&);

	RightFraction& operator+=(const Fraction& other) override;
	RightFraction& operator-=(const Fraction& other) override;
	RightFraction& operator*=(const Fraction& other) override;
	RightFraction& operator/=(const Fraction& other) override;

	inline int up() const noexcept { return _up; };
	inline int down() const noexcept { return _down; };

	void up(int up) noexcept override;
	void down(int down) override;
};