#include "pch.h"
#include "LongNumber.h"

TEST(BasicMethods, SetsGets) {
	LongNumber a = LongNumber();
	EXPECT_EQ(a.sign(), true);
	EXPECT_EQ(a.number(), "");

	LongNumber b = LongNumber("-348174617323748185787390136128942647727856893722789562384467");
	EXPECT_EQ(b.number(), "-348174617323748185787390136128942647727856893722789562384467");
	EXPECT_EQ(b.sign(), false);

	LongNumber c = LongNumber(b);
	EXPECT_EQ(b.number(), "-348174617323748185787390136128942647727856893722789562384467");
	EXPECT_EQ(b.sign(), false);
}

TEST(Opers, OpersBool) {
	LongNumber nm1 = LongNumber("31");
	LongNumber nm1_sign = LongNumber("-31");
	LongNumber eq_nm1 = LongNumber(nm1);
	EXPECT_TRUE(nm1 == eq_nm1);
	EXPECT_TRUE(nm1 > nm1_sign);
	EXPECT_FALSE(nm1 < nm1_sign);
	EXPECT_TRUE(nm1 != nm1_sign);

	LongNumber nm2 = LongNumber("21");
	LongNumber nm3 = LongNumber("24");
	EXPECT_TRUE(nm3 > nm2);
	EXPECT_FALSE(nm3 < nm2);
	EXPECT_TRUE(nm3 >= nm2);
	EXPECT_FALSE(nm3 <= nm2);

	LongNumber nm4 = LongNumber("11");
	nm4 = -nm4;
	EXPECT_EQ(nm4.number(), "-11");

	LongNumber nm5 = LongNumber("30");
	LongNumber nm6 = LongNumber("-21");
	LongNumber nm7 = LongNumber("30");
	EXPECT_TRUE(nm5 >= nm7);
	EXPECT_TRUE(nm5 <= nm7);
	EXPECT_TRUE(nm5 >= nm6);
	EXPECT_FALSE(nm5 <= nm6);
}

TEST(Opers, MathAdvanced) {
	LongNumber a("100");
	LongNumber b("50");

	a += b;
	EXPECT_EQ(a.number(), "150");

	a -= LongNumber("70");
	EXPECT_EQ(a.number(), "80");

	LongNumber c("10");
	c *= LongNumber("-5");
	EXPECT_EQ(c.number(), "-50");

	LongNumber d("10");
	d -= LongNumber("20");
	EXPECT_EQ(d.number(), "-10");
}

TEST(SpecialCases, ZeroHandling) {
	LongNumber z1("000");
	LongNumber z2("-0");

	EXPECT_EQ(z1.number(), "0");
	EXPECT_EQ(z2.number(), "0");
	EXPECT_EQ(z1.sign(), true);
	EXPECT_EQ(z2.sign(), true);

	LongNumber a("10");
	LongNumber result = a * LongNumber("0");
	EXPECT_EQ(result.number(), "0");
	EXPECT_EQ(result.sign(), true);
}

TEST(Opers, IndexData) {
	LongNumber nm1("3851");
	LongNumber nm2("-385151");

	EXPECT_EQ(nm1[0], '3');
	EXPECT_EQ(nm2[1], '3');
	EXPECT_EQ(nm2[0], '-');
}

TEST(Opers, PrefPost) {
	LongNumber nm1("30");
	LongNumber nm2("0");
	EXPECT_EQ((++nm1).number(), "31");
	EXPECT_EQ((--nm1).number(), "30");

	EXPECT_EQ((nm1++).number(), "30");
	EXPECT_EQ(nm1.number(), "31");

	EXPECT_EQ((--nm2).sign(), false);
}

TEST(Opers, OutputInput) {
	LongNumber nm1("10");
	LongNumber nm2("-12563");
	EXPECT_NO_THROW(std::cout << nm2 << std::endl);
	EXPECT_NO_THROW(std::cin >> nm1);
}