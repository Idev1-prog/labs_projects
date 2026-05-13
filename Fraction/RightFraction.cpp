#include "RightFraction.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <cmath>

void RightFraction::extract_whole() {
    if (_down == 0) return;

    if (_down < 0) {
        _down = -_down;
        _up = -_up;
        _whole = -_whole;
    }

    int total_up;
    if (_whole >= 0) {
        total_up = _whole * _down + _up;
    }
    else {
        total_up = _whole * _down - _up;
    }

    _whole = total_up / _down;
    _up = std::abs(total_up % _down);

    if (_whole == 0 && total_up < 0) {
        _up = -_up;
    }
}

void RightFraction::simplify() {
    extract_whole();
    Fraction::simplify();
}

void RightFraction::check_invariant() const {}

void RightFraction::to_improper(int& num, int& den) {
    num = (_whole >= 0) ? (_whole * _down + _up) : (_whole * _down - _up);
    den = _down;
    _whole = 0;
}

Fraction RightFraction::to_improper() const {
    int num = (_whole >= 0) ? (_whole * _down + _up) : (_whole * _down - _up);
    int den = _down;
    return Fraction(num, den);
}

RightFraction::RightFraction(int whole, int up, int down)
    : Fraction(0, 1), _whole(whole) {
    if (down == 0) throw std::invalid_argument("division by zero");
    _up = up;
    _down = down;
    simplify();
}

RightFraction::RightFraction(int up, int down)
    : Fraction(0, 1), _whole(0) {
    if (down == 0) throw std::invalid_argument("division by zero");
    _up = up;
    _down = down;
    simplify();
}

RightFraction::RightFraction(int up)
    : Fraction(0, 1), _whole(0) {
    _up = up;
    _down = 1;
    simplify();
}

RightFraction::RightFraction(const std::string& str)
    : Fraction(0, 1), _whole(0) {
    std::string s = str;
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    if (s.empty()) throw std::invalid_argument("Empty string");

    size_t space_pos = str.find(' ');
    if (space_pos != std::string::npos) {
        std::string whole_str = str.substr(0, space_pos);
        std::string frac_str = str.substr(space_pos + 1);
        _whole = std::stoi(whole_str);
        size_t slash = frac_str.find('/');
        if (slash != std::string::npos) {
            _up = std::stoi(frac_str.substr(0, slash));
            _down = std::stoi(frac_str.substr(slash + 1));
        }
        else {
            _up = std::stoi(frac_str);
            _down = 1;
        }
    }
    else {
        size_t slash = str.find('/');
        if (slash != std::string::npos) {
            _up = std::stoi(str.substr(0, slash));
            _down = std::stoi(str.substr(slash + 1));
        }
        else {
            _up = std::stoi(str);
            _down = 1;
        }
    }
    if (_down == 0) throw std::invalid_argument("division by zero");
    simplify();
}

RightFraction::RightFraction(const Fraction& other)
    : Fraction(0, 1), _whole(0) {
    _up = other.up();
    _down = other.down();
    simplify();
}

std::string RightFraction::to_string() const {
    if (_whole == 0) {
        return Fraction::to_string();
    }
    if (_up == 0) {
        return std::to_string(_whole);
    }
    return std::to_string(_whole) + " " + std::to_string(_up) + "/" + std::to_string(_down);
}

RightFraction& RightFraction::operator=(const Fraction& other) {
    _up = other.up();
    _down = other.down();
    _whole = 0;
    simplify();
    return *this;
}

//RightFraction& RightFraction::operator+=(const Fraction& other) {
//    int num1, den1, num2, den2;
//    this->to_improper(num1, den1);
//    other.to_improper(num2, den2);
//
//    _up = num1 * den2 + num2 * den1;
//    _down = den1 * den2;
//    _whole = 0;
//
//    simplify();
//    extract_whole();
//    return *this;
//}

//RightFraction& RightFraction::operator-=(const Fraction& other) {
//    int num1, den1, num2, den2;
//    this->to_improper(num1, den1);
//    other.to_improper(num2, den2);
//
//    _up = num1 * den2 - num2 * den1;
//    _down = den1 * den2;
//    _whole = 0;
//
//    simplify();
//    //extract_whole();
//    return *this;
//}
//
//RightFraction& RightFraction::operator*=(const Fraction& other) {
//    int num1, den1, num2, den2;
//    this->to_improper(num1, den1);
//    other.to_improper(num2, den2);
//
//    _up = num1 * num2;
//    _down = den1 * den2;
//    _whole = 0;
//
//    simplify();
//    //extract_whole();
//    return *this;
//}
//
//RightFraction& RightFraction::operator/=(const Fraction& other) {
//    int num1, den1, num2, den2;
//    this->to_improper(num1, den1);
//    other.to_improper(num2, den2);
//
//    _up = num1 * den2;
//    _down = den1 * num2;
//    _whole = 0;
//
//    simplify();
//    //extract_whole();
//    return *this;
//}

void RightFraction::up(int up_val) {
    _up = up_val;
    simplify();
}

void RightFraction::down(int down_val) {
    Fraction::down(down_val);
}

//bool RightFraction::operator==(const Fraction& other) const {
//    int num1, den1, num2, den2;
//    this->to_improper(num1, den1);
//    other.to_improper(num2, den2);
//    return num1 * den2 == num2 * den1;
//}

//bool RightFraction::operator!=(const Fraction& other) const {
//    return !(*this == other);
//}

//bool RightFraction::operator<(const Fraction& other) const {
//    int num1, den1, num2, den2;
//    this->to_improper(num1, den1);
//    other.to_improper(num2, den2);
//    return num1 * den2 < num2 * den1;
//}
//
//bool RightFraction::operator>(const Fraction& other) const {
//    int num1, den1, num2, den2;
//    this->to_improper(num1, den1);
//    other.to_improper(num2, den2);
//    return num1 * den2 > num2 * den1;
//}

//bool RightFraction::operator<=(const Fraction& other) const {
//    return !(other < *this);
//}
//
//bool RightFraction::operator>=(const Fraction& other) const {
//    return !(*this < other);
//}