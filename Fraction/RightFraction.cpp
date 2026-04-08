#include "RightFraction.h"
#include <stdexcept>

void RightFraction::check_invariant() const {
    if (std::abs(_up) >= _down) {
        throw std::invalid_argument("RightFraction must satisfy |numerator| < denominator");
    }
}

RightFraction::RightFraction(int up, int down) : Fraction(up, down) {
    check_invariant();
}

RightFraction::RightFraction(int up) : Fraction(up) {
    check_invariant();
}

RightFraction::RightFraction(const std::string& str) : Fraction(str) {
    check_invariant();
}

RightFraction::RightFraction(const Fraction& other) : Fraction(other) {
    check_invariant();
}

RightFraction& RightFraction::operator=(const RightFraction& other) {
    if (this != &other) {
        Fraction::operator=(other);
    }
    return *this;
}

RightFraction& RightFraction::operator=(const Fraction& other) {
    Fraction::operator=(other);
    return *this;
}

RightFraction& RightFraction::operator+=(const Fraction& other) {
    Fraction::operator+=(other);
    return *this;
}

RightFraction& RightFraction::operator-=(const Fraction& other) {
    Fraction::operator-=(other);
    return *this;
}

RightFraction& RightFraction::operator*=(const Fraction& other) {
    Fraction::operator*=(other);
    return *this;
}

RightFraction& RightFraction::operator/=(const Fraction& other) {
    Fraction::operator/=(other);
    return *this;
}

void RightFraction::up(int up) {
    Fraction::up(up);
}

void RightFraction::down(int down) {
    Fraction::down(down);
}