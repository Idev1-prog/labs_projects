#include "pch.h"
#include "RightFraction.h"
#include <stdexcept>
//#define TEST_RIGHT_FRACTION

#ifdef TEST_RIGHT_FRACTION

TEST(RightFractionConstructor, Default) {
    RightFraction rf;
    EXPECT_EQ(rf.up(), 0);
    EXPECT_EQ(rf.down(), 1);
    EXPECT_EQ(rf.to_string(), "0");
}

TEST(RightFractionConstructor, FromNumeratorDenominator) {
    RightFraction rf1(1, 2);
    EXPECT_EQ(rf1.up(), 1);
    EXPECT_EQ(rf1.down(), 2);
    EXPECT_EQ(rf1.to_string(), "1/2");

    RightFraction rf2(3, 4);
    EXPECT_EQ(rf2.up(), 3);
    EXPECT_EQ(rf2.down(), 4);

    RightFraction rf3(2, 4);
    EXPECT_EQ(rf3.up(), 1);
    EXPECT_EQ(rf3.down(), 2);
}

TEST(RightFractionConstructor, FromNumeratorDenominatorInvalid) {
    EXPECT_THROW(RightFraction(5, 2), std::invalid_argument);
    EXPECT_THROW(RightFraction(2, 2), std::invalid_argument);
    EXPECT_THROW(RightFraction(-3, 2), std::invalid_argument);
    EXPECT_THROW(RightFraction(0, 0), std::invalid_argument);
    EXPECT_THROW(RightFraction(1, 0), std::invalid_argument);
}

TEST(RightFractionConstructor, FromInteger) {
    RightFraction rf1(0);
    EXPECT_EQ(rf1.up(), 0);
    EXPECT_EQ(rf1.down(), 1);

    EXPECT_THROW(RightFraction(1), std::invalid_argument);
    EXPECT_THROW(RightFraction(-1), std::invalid_argument);
    EXPECT_THROW(RightFraction(5), std::invalid_argument);
}

TEST(RightFractionConstructor, FromString) {
    // Корректные строки
    RightFraction rf1("1/2");
    EXPECT_EQ(rf1.up(), 1);
    EXPECT_EQ(rf1.down(), 2);

    RightFraction rf2("0/5");
    EXPECT_EQ(rf2.up(), 0);
    EXPECT_EQ(rf2.down(), 1);

    RightFraction rf3("  3 / 4  ");
    EXPECT_EQ(rf3.up(), 3);
    EXPECT_EQ(rf3.down(), 4);

    RightFraction rf4("0");
    EXPECT_EQ(rf4.up(), 0);
    EXPECT_EQ(rf4.down(), 1);
}

TEST(RightFractionConstructor, FromStringInvalid) {
    EXPECT_THROW(RightFraction("5/2"), std::invalid_argument);
    EXPECT_THROW(RightFraction("2/2"), std::invalid_argument);
    EXPECT_THROW(RightFraction("-3/2"), std::invalid_argument);

    EXPECT_THROW(RightFraction(""), std::invalid_argument);
    EXPECT_THROW(RightFraction("/5"), std::invalid_argument);
    EXPECT_THROW(RightFraction("5/"), std::invalid_argument);
    EXPECT_THROW(RightFraction("a/b"), std::invalid_argument);
    EXPECT_THROW(RightFraction("5/0"), std::invalid_argument);
    EXPECT_THROW(RightFraction("1"), std::invalid_argument);
    EXPECT_THROW(RightFraction("42"), std::invalid_argument);
}

TEST(RightFractionConstructor, Copy) {
    RightFraction rf1(1, 2);
    RightFraction rf2(rf1);
    EXPECT_EQ(rf2.up(), 1);
    EXPECT_EQ(rf2.down(), 2);
}

TEST(RightFractionConstructor, FromFraction) {
    Fraction f1(1, 2);
    RightFraction rf1(f1);
    EXPECT_EQ(rf1.up(), 1);
    EXPECT_EQ(rf1.down(), 2);

    Fraction f2(5, 2);
    EXPECT_THROW(RightFraction rf2(f2), std::invalid_argument);
}


TEST(RightFractionAssignment, CopyAssignment) {
    RightFraction rf1(1, 2);
    RightFraction rf2;
    rf2 = rf1;
    EXPECT_EQ(rf2.up(), 1);
    EXPECT_EQ(rf2.down(), 2);
}

TEST(RightFractionAssignment, FromFraction) {
    RightFraction rf;
    Fraction f1(1, 3);
    rf = f1;
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 3);

    Fraction f2(5, 2);
    EXPECT_THROW(rf = f2, std::invalid_argument);
}


TEST(RightFractionArithmeticAssign, PlusEqual) {
    RightFraction rf(1, 4);
    rf += Fraction(1, 4);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 2);

    EXPECT_THROW(rf += Fraction(2, 3), std::invalid_argument);
}

TEST(RightFractionArithmeticAssign, MinusEqual) {
    RightFraction rf(1, 2);
    rf -= Fraction(1, 4);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 4);

    RightFraction rf2(1, 4);
    EXPECT_THROW(rf2 -= Fraction(2, 1), std::invalid_argument);
}

TEST(RightFractionArithmeticAssign, MultiplyEqual) {
    RightFraction rf(1, 2);
    rf *= Fraction(1, 2);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 4);

    rf *= Fraction(3, 2);
    EXPECT_EQ(rf.up(), 3);
    EXPECT_EQ(rf.down(), 8);

    RightFraction rf2(1, 2);
    EXPECT_THROW(rf2 *= Fraction(2, 1), std::invalid_argument);
}

TEST(RightFractionArithmeticAssign, DivideEqual) {
    RightFraction rf(1, 2);
    rf /= Fraction(2, 1);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 4);

    RightFraction rf2(1, 2);
    EXPECT_THROW(rf2 /= Fraction(1, 2), std::invalid_argument);
}


TEST(RightFractionArithmetic, Plus) {
    RightFraction rf1(1, 3);
    RightFraction rf2(1, 6);
    Fraction sum = rf1 + rf2;
    EXPECT_EQ(sum.up(), 1);
    EXPECT_EQ(sum.down(), 2);
}

TEST(RightFractionArithmetic, Minus) {
    RightFraction rf1(2, 3);
    RightFraction rf2(1, 3);
    Fraction diff = rf1 - rf2;
    EXPECT_EQ(diff.up(), 1);
    EXPECT_EQ(diff.down(), 3);
}

TEST(RightFractionArithmetic, Multiply) {
    RightFraction rf1(1, 2);
    RightFraction rf2(1, 2);
    Fraction prod = rf1 * rf2;
    EXPECT_EQ(prod.up(), 1);
    EXPECT_EQ(prod.down(), 4);
}

TEST(RightFractionArithmetic, Divide) {
    RightFraction rf1(1, 2);
    RightFraction rf2(1, 4);
    Fraction quot = rf1 / rf2;
    EXPECT_EQ(quot.up(), 2);
    EXPECT_EQ(quot.down(), 1);
}


TEST(RightFractionSetters, SetUp) {
    RightFraction rf(1, 3);
    rf.up(2);
    EXPECT_EQ(rf.up(), 2);
    EXPECT_EQ(rf.down(), 3);

    EXPECT_THROW(rf.up(3), std::invalid_argument);
    EXPECT_EQ(rf.up(), 2);
    EXPECT_EQ(rf.down(), 3);
}

TEST(RightFractionSetters, SetDown) {
    RightFraction rf(2, 5);
    rf.down(7);
    EXPECT_EQ(rf.up(), 2);
    EXPECT_EQ(rf.down(), 7);

    EXPECT_THROW(rf.down(2), std::invalid_argument);
    EXPECT_THROW(rf.down(0), std::invalid_argument);
    EXPECT_EQ(rf.up(), 2);
    EXPECT_EQ(rf.down(), 7);
}

TEST(RightFractionComparisons, Equality) {
    RightFraction rf1(1, 2);
    RightFraction rf2(2, 4);
    RightFraction rf3(1, 3);

    EXPECT_TRUE(rf1 == rf2);
    EXPECT_FALSE(rf1 == rf3);
    EXPECT_TRUE(rf1 != rf3);
}

TEST(RightFractionComparisons, Relational) {
    RightFraction rf1(1, 2);
    RightFraction rf2(2, 3);

    EXPECT_TRUE(rf1 < rf2);
    EXPECT_TRUE(rf1 <= rf2);
    EXPECT_FALSE(rf1 > rf2);
    EXPECT_FALSE(rf1 >= rf2);
    EXPECT_TRUE(rf2 > rf1);
    EXPECT_TRUE(rf2 >= rf1);
}


TEST(RightFractionToString, Representation) {
    RightFraction rf1(1, 2);
    EXPECT_EQ(rf1.to_string(), "1/2");

    RightFraction rf2(0, 5);
    EXPECT_EQ(rf2.to_string(), "0");

    RightFraction rf3(2, 4);
    EXPECT_EQ(rf3.to_string(), "1/2");
}


TEST(RightFractionChaining, MultipleOperations) {
    RightFraction rf(1, 2);
    rf += RightFraction(1, 4); 
    rf -= RightFraction(1, 8);  
    rf *= RightFraction(1, 2);   
    rf /= RightFraction(5, 4);   
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 4);
}


TEST(RightFractionEdgeCases, NegativeFractions) {
    RightFraction rf1(-1, 2);
    EXPECT_EQ(rf1.up(), -1);
    EXPECT_EQ(rf1.down(), 2);

    RightFraction rf2(1, -2);  
    EXPECT_EQ(rf2.up(), -1);
    EXPECT_EQ(rf2.down(), 2);

    rf1 += RightFraction(1, 2);
    EXPECT_EQ(rf1.up(), 0);
    EXPECT_EQ(rf1.down(), 1);
}

TEST(RightFractionEdgeCases, ZeroNumerator) {
    RightFraction rf(0, 3);
    EXPECT_EQ(rf.up(), 0);
    EXPECT_EQ(rf.down(), 1);
}


TEST(RightFractionExceptions, DivisionByZeroInConstructor) {
    EXPECT_THROW(RightFraction(1, 0), std::invalid_argument);
    EXPECT_THROW(RightFraction(0, 0), std::invalid_argument);
    EXPECT_THROW(RightFraction("1/0"), std::invalid_argument);
}

TEST(RightFractionExceptions, SetDownToZero) {
    RightFraction rf(1, 2);
    EXPECT_THROW(rf.down(0), std::invalid_argument);
}

#endif // TEST_RIGHT_FRACTION