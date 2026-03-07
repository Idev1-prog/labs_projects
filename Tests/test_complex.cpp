#include "pch.h"
#include "complex.h"
//#define COMPLEX

#ifdef COMPLEX

TEST(BaseTest, BaseInitTest) {
	Complex c1;
	Complex c2(11, 11);
	Complex c3("132 + 13i");
	Complex c4(c2);

	EXPECT_DOUBLE_EQ(c1.im(), 0);
	EXPECT_DOUBLE_EQ(c1.re(), 0);

	EXPECT_DOUBLE_EQ(c2.im(), 11);
	EXPECT_DOUBLE_EQ(c2.re(), 11);

	EXPECT_DOUBLE_EQ(c3.im(), 13);
	EXPECT_DOUBLE_EQ(c3.re(), 132);

	EXPECT_DOUBLE_EQ(c4.im(), 11);
	EXPECT_DOUBLE_EQ(c4.re(), 11);
}

TEST(BaseTest, BaseOperTest) {
	Complex c1(1, 2);
	Complex c2(1, 1);
	Complex t1 = c1 + c2;

	EXPECT_DOUBLE_EQ(t1.re(), 2);
	EXPECT_DOUBLE_EQ(t1.im(), 3);

	Complex c11(1, 2);
	Complex c22(1, 1);
	Complex t2 = c11 - c22;
	EXPECT_DOUBLE_EQ(t2.re(), 0);
	EXPECT_DOUBLE_EQ(t2.im(), 1);
}

TEST(AssertTests, AssertTest) {
	EXPECT_ANY_THROW(Complex c1("132+133"));
	EXPECT_ANY_THROW(Complex c2("132133"));
}

TEST(ComplexTest, AssignmentTest) {
    Complex c1(1, 2);
    Complex c2;

    c2 = c1;
    EXPECT_DOUBLE_EQ(c2.re(), 1);
    EXPECT_DOUBLE_EQ(c2.im(), 2);

    c1 = c1;
    EXPECT_DOUBLE_EQ(c1.re(), 1);
    EXPECT_DOUBLE_EQ(c1.im(), 2);
}

TEST(ComplexTest, DivisionTest) {
    Complex c1(1, 2);
    Complex c2(1, 1);
    Complex result = c1 / c2;

    EXPECT_NEAR(result.re(), 1.5, 1e-10);
    EXPECT_NEAR(result.im(), 0.5, 1e-10);

    Complex c3(3, 4);
    Complex c4(1, 0);
    Complex result2 = c3 / c4;

    EXPECT_DOUBLE_EQ(result2.re(), 3);
    EXPECT_DOUBLE_EQ(result2.im(), 4);
}

#endif