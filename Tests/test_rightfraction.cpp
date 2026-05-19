#include "pch.h"
#include "RightFraction.h"
#include <stdexcept>
//#define TEST_RIGHT_FRACTION

#ifdef TEST_RIGHT_FRACTION

TEST(RightFractionTest, DefaultConstructor) {
    RightFraction rf;
    EXPECT_EQ(rf.whole(), 0);
    EXPECT_EQ(rf.up(), 0);
    EXPECT_EQ(rf.down(), 1);
}

TEST(RightFractionTest, ConstructorWithUpAndDown) {
    RightFraction rf(3, 4);
    EXPECT_EQ(rf.whole(), 0);
    EXPECT_EQ(rf.up(), 3);
    EXPECT_EQ(rf.down(), 4);
}

TEST(RightFractionTest, ConstructorWithWholeUpDown) {
    RightFraction rf(2, 3, 4);
    EXPECT_EQ(rf.whole(), 2);
    EXPECT_EQ(rf.up(), 3);
    EXPECT_EQ(rf.down(), 4);
}

TEST(RightFractionTest, ConstructorWithImproperFraction) {
    RightFraction rf(5, 2);
    EXPECT_EQ(rf.whole(), 2);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 2);
}

TEST(RightFractionTest, ConstructorWithNegativeImproperFraction) {
    RightFraction rf(-5, 2);
    EXPECT_EQ(rf.whole(), -2);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 2);
}

TEST(RightFractionTest, ConstructorWithNegativeDenominator) {
    RightFraction rf(3, -4);
    EXPECT_EQ(rf.whole(), 0);
    EXPECT_EQ(rf.up(), -3);
    EXPECT_EQ(rf.down(), 4);
}

TEST(RightFractionTest, ConstructorWithStringSimpleFraction) {
    RightFraction rf("3/4");
    EXPECT_EQ(rf.whole(), 0);
    EXPECT_EQ(rf.up(), 3);
    EXPECT_EQ(rf.down(), 4);
}

TEST(RightFractionTest, ConstructorWithStringMixedFraction) {
    RightFraction rf("2 3/4");
    EXPECT_EQ(rf.whole(), 2);
    EXPECT_EQ(rf.up(), 3);
    EXPECT_EQ(rf.down(), 4);
}

TEST(RightFractionTest, ConstructorWithStringInteger) {
    RightFraction rf("5");
    EXPECT_EQ(rf.whole(), 5);
    EXPECT_EQ(rf.up(), 0);
    EXPECT_EQ(rf.down(), 1);
}

TEST(RightFractionTest, SimplifyFraction) {
    RightFraction rf(2, 4, 8);
    EXPECT_EQ(rf.whole(), 2);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 2);
}

TEST(RightFractionTest, WholeExtractionFromImproper) {
    RightFraction rf(7, 3);
    EXPECT_EQ(rf.whole(), 2);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 3);
}

TEST(RightFractionTest, AdditionWithFraction) {
    RightFraction rf1(1, 3, 4);
    RightFraction f2(0, 1, 2);
    rf1 += f2;
    EXPECT_EQ(rf1.whole(), 2);
    EXPECT_EQ(rf1.up(), 1);
    EXPECT_EQ(rf1.down(), 4);
}

TEST(RightFractionTest, SubtractionWithFraction) {
    RightFraction rf1(2, 3, 4);
    RightFraction f2(1, 1, 2);
    rf1 -= f2;
    EXPECT_EQ(rf1.whole(), 1);
    EXPECT_EQ(rf1.up(), 1);
    EXPECT_EQ(rf1.down(), 4);
}

TEST(RightFractionTest, MultiplicationWithFraction) {
    RightFraction rf1(1, 1, 2);
    RightFraction f2(-2, 2, 1);
    rf1 *= f2;
    EXPECT_EQ(rf1.whole(), -6);
    EXPECT_EQ(rf1.up(), 0);
    EXPECT_EQ(rf1.down(), 1);
}

TEST(RightFractionTest, DivisionWithFraction) {
    RightFraction rf1(3, 0, 1);
    Fraction f2(2, 1);
    rf1 /= f2;
    EXPECT_EQ(rf1.whole(), 1);
    EXPECT_EQ(rf1.up(), 1);
    EXPECT_EQ(rf1.down(), 2);
}

TEST(RightFractionTest, EqualityOperator) {
    RightFraction rf1(1, 1, 2);
    Fraction f2(3, 2);
    EXPECT_TRUE(rf1 == f2);
}

TEST(RightFractionTest, InequalityOperator) {
    RightFraction rf1(1, 1, 2);
    Fraction f2(2, 3);
    EXPECT_TRUE(rf1 != f2);
}

TEST(RightFractionTest, LessThanOperator) {
    RightFraction rf1(1, 1, 2);
    Fraction f2(2, 1);
    EXPECT_TRUE(rf1 < f2);
}

TEST(RightFractionTest, GreaterThanOperator) {
    RightFraction rf1(2, 1, 2);
    Fraction f2(2, 1);
    EXPECT_TRUE(rf1 > f2);
}

TEST(RightFractionTest, ToStringWithWholeAndFraction) {
    RightFraction rf(2, 3, 4);
    EXPECT_EQ(rf.to_string(), "2 3/4");
}

TEST(RightFractionTest, ToStringWithFractionOnly) {
    RightFraction rf(0, 3, 4);
    EXPECT_EQ(rf.to_string(), "3/4");
}

TEST(RightFractionTest, ToStringWithWholeOnly) {
    RightFraction rf(5, 0, 1);
    EXPECT_EQ(rf.to_string(), "5");
}

TEST(RightFractionTest, ToStringWithNegativeFraction) {
    RightFraction rf(-1, 3, 4);
    EXPECT_EQ(rf.to_string(), "-1 3/4");
}

TEST(RightFractionTest, SetUpMethod) {
    RightFraction rf(1, 2, 3);
    rf.up(5);
    EXPECT_EQ(rf.whole(), 2);
    EXPECT_EQ(rf.up(), 2);
    EXPECT_EQ(rf.down(), 3);
}

TEST(RightFractionTest, SetDownMethod) {
    RightFraction rf(1, 2, 3);
    rf.down(5);
    EXPECT_EQ(rf.whole(), 1);
    EXPECT_EQ(rf.up(), 2);
    EXPECT_EQ(rf.down(), 5);
}

TEST(RightFractionTest, AssignmentFromFraction) {
    Fraction f(5, 2);
    RightFraction rf = f;
    EXPECT_EQ(rf.whole(), 2);
    EXPECT_EQ(rf.up(), 1);
    EXPECT_EQ(rf.down(), 2);
}

TEST(RightFractionTest, CombinedArithmeticChain) {
    RightFraction a(1, 1, 2);
    RightFraction b(2, 3, 4);
    Fraction c(1, 2);

    a += b;
    a *= c;
    a -= Fraction(1, 4);

    EXPECT_EQ(a.whole(), 1);
    EXPECT_EQ(a.up(), 7);
    EXPECT_EQ(a.down(), 8);
    EXPECT_EQ(a.to_string(), "1 7/8");
}

TEST(RightFractionTest, MixedOperationsWithFraction) {
    RightFraction r1(3, 1, 3);
    Fraction f1(2, 5);

    RightFraction temp1 = r1;
    temp1 += f1;

    RightFraction temp2 = Fraction(1, 1);
    temp2 *= RightFraction(1, 2);

    RightFraction r2 = temp1;
    r2 -= temp2;

    EXPECT_EQ(r2.whole(), 3);
    EXPECT_EQ(r2.up(), 7);
    EXPECT_EQ(r2.down(), 30);
    EXPECT_EQ(r2.to_string(), "3 7/30");
}


#endif // TEST_RIGHT_FRACTION