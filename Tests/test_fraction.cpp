#include "pch.h"
#include "Fraction.h"

TEST(FractionTest, Constructors) {
    Fraction f1;
    EXPECT_EQ(f1.up(), 0);
    EXPECT_EQ(f1.down(), 1);

    Fraction f2(5);
    EXPECT_EQ(f2.up(), 5);
    EXPECT_EQ(f2.down(), 1);

    // Checking for automatic shortening when creating
    Fraction f4(4, 8);
    EXPECT_EQ(f4.up(), 1);
    EXPECT_EQ(f4.down(), 2);

    //AI+
    Fraction f3(3, 4);
    EXPECT_EQ(f3.up(), 3);
    EXPECT_EQ(f3.down(), 4);

    Fraction f5(-6, 9);
    EXPECT_EQ(f5.up(), -2);
    EXPECT_EQ(f5.down(), 3);

    Fraction f6(0, 5);
    EXPECT_EQ(f6.up(), 0);
    EXPECT_EQ(f6.down(), 1);

    EXPECT_THROW(Fraction(1, 0), std::invalid_argument);
}

TEST(FractionTest, Setters) {
    Fraction f;
    f.up(7);
    f.down(8);
    EXPECT_EQ(f.up(), 7);
    EXPECT_EQ(f.down(), 8);

    Fraction f2(2, 4);
    EXPECT_EQ(f2.up(), 1);
    EXPECT_EQ(f2.down(), 2);

    EXPECT_THROW(f.down(0), std::invalid_argument);
}

TEST(FractionTest, ToString) {
    Fraction f1(3, 4);
    EXPECT_EQ(f1.to_string(), "3/4");

    Fraction f2(5, 1);
    EXPECT_EQ(f2.to_string(), "5");

    Fraction f3(-2, 3);
    EXPECT_EQ(f3.to_string(), "-2/3");

    Fraction f4(4, 8);
    EXPECT_EQ(f4.to_string(), "1/2");
}

TEST(FractionTest, CompoundAssignment) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);

    f1 += f2;
    EXPECT_EQ(f1.up(), 5);
    EXPECT_EQ(f1.down(), 6);

    Fraction f3(3, 4);
    Fraction f4(1, 4);
    f3 -= f4;
    EXPECT_EQ(f3.up(), 1);
    EXPECT_EQ(f3.down(), 2);

    Fraction f5(2, 3);
    Fraction f6(3, 4);
    f5 *= f6;
    EXPECT_EQ(f5.up(), 1);
    EXPECT_EQ(f5.down(), 2);

    Fraction f7(1, 2);
    Fraction f8(1, 4);
    f7 /= f8;
    EXPECT_EQ(f7.up(), 2);
    EXPECT_EQ(f7.down(), 1);
}

TEST(FractionTest, Arithmetic) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);

    Fraction sum = f1 + f2;
    EXPECT_EQ(sum.up(), 5);
    EXPECT_EQ(sum.down(), 6);

    Fraction diff = f1 - f2;
    EXPECT_EQ(diff.up(), 1);
    EXPECT_EQ(diff.down(), 6);

    Fraction prod = f1 * f2;
    EXPECT_EQ(prod.up(), 1);
    EXPECT_EQ(prod.down(), 6);

    Fraction quot = f1 / f2;
    EXPECT_EQ(quot.up(), 3);
    EXPECT_EQ(quot.down(), 2);
}

TEST(FractionTest, Assignment) {
    Fraction f1(3, 4);
    Fraction f2;
    f2 = f1;
    EXPECT_EQ(f2.up(), 3);
    EXPECT_EQ(f2.down(), 4);

    f2 = f2;
    EXPECT_EQ(f2.up(), 3);
    EXPECT_EQ(f2.down(), 4);

    Fraction f3(4, 8);
    Fraction f4;
    f4 = f3;
    EXPECT_EQ(f4.up(), 1);
    EXPECT_EQ(f4.down(), 2);
}

TEST(FractionTest, Comparison) {
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    Fraction f3(2, 3);
    Fraction f4(1, 3);

    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);

    EXPECT_TRUE(f1 != f3);
    EXPECT_FALSE(f1 != f2);

    EXPECT_TRUE(f1 < f3);
    EXPECT_FALSE(f1 < f4);

    EXPECT_TRUE(f3 > f1);
    EXPECT_FALSE(f4 > f1);

    EXPECT_TRUE(f1 <= f2);
    EXPECT_TRUE(f1 <= f3);
    EXPECT_FALSE(f3 <= f1);

    EXPECT_TRUE(f1 >= f2);
    EXPECT_TRUE(f3 >= f1);
    EXPECT_FALSE(f4 >= f1);
}

TEST(FractionTest, WithIntegers) {
    Fraction f(1, 2);

     EXPECT_TRUE(f < 1);
     EXPECT_TRUE(f > 0);

     Fraction sum = f + 1;
     EXPECT_EQ(sum.up(), 3);
     EXPECT_EQ(sum.down(), 2);
}

//AI test group
TEST(FractionTest, NegativeNumbers) {
    Fraction f1(-3, 4);
    EXPECT_EQ(f1.up(), -3);
    EXPECT_EQ(f1.down(), 4);

    Fraction f3(-3, -4);
    EXPECT_EQ(f3.up(), 3);
    EXPECT_EQ(f3.down(), 4);

    Fraction f4(-4, 8);
    EXPECT_EQ(f4.up(), -1);
    EXPECT_EQ(f4.down(), 2);
}


TEST(FractionTest, ArithmeticWithNegatives) {
    Fraction f1(1, 2);
    Fraction f2(-1, 3);

    Fraction sum = f1 + f2;
    EXPECT_EQ(sum.up(), 1);
    EXPECT_EQ(sum.down(), 6);

    Fraction f3(-2, 3);
    Fraction f4(3, 4);
    Fraction prod = f3 * f4;
    EXPECT_EQ(prod.up(), -1);
    EXPECT_EQ(prod.down(), 2);
}
