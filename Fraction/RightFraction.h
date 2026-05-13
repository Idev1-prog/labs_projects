#pragma once
#include "Fraction.h"

class RightFraction : public Fraction {
private:
    int _whole;
    void extract_whole();

protected:
    void check_invariant() const override;
    void simplify() override;

public:
    RightFraction() : Fraction(), _whole(0) {}
    RightFraction(int whole, int up, int down);
    RightFraction(int up, int down);
    explicit RightFraction(int up);
    explicit RightFraction(const std::string&);
    RightFraction(const Fraction&);

    inline int whole() const noexcept { return _whole; }
    inline int up()    const noexcept { return _up; }
    inline int down()  const noexcept { return _down; }

    void to_improper(int& num, int& den) override;
    Fraction to_improper() const override;

    std::string to_string() const override;
    std::string mixed_form() const = delete;

    RightFraction& operator=(const Fraction&);

    //RightFraction& operator+=(const Fraction& other) override;
    //RightFraction& operator-=(const Fraction& other) override;
    //RightFraction& operator*=(const Fraction& other) override;
    //RightFraction& operator/=(const Fraction& other) override;

    void up(int up_val) override;
    void down(int down_val) override;

    //bool operator==(const Fraction& other) const;
    //bool operator!=(const Fraction& other) const;
    //bool operator< (const Fraction& other) const;
    //bool operator> (const Fraction& other) const;
    //bool operator<=(const Fraction& other) const;
    //bool operator>=(const Fraction& other) const;
};