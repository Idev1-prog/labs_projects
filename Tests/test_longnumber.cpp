#include "pch.h"
#include "LongNumber.h"

TEST(Block1, sets_gets) {
	LongNumber a = LongNumber();
	EXPECT_EQ(a.sign(), true);
	EXPECT_EQ(a.number(), "");

	LongNumber b = LongNumber("-348174617323748185787390136128942647727856893722789562384467");
	EXPECT_EQ(b.number(), "348174617323748185787390136128942647727856893722789562384467");
	EXPECT_EQ(b.sign(), false);

	LongNumber c = LongNumber(b);
	EXPECT_EQ(b.number(), "348174617323748185787390136128942647727856893722789562384467");
	EXPECT_EQ(b.sign(), false);
}

TEST(Block1, opers) {
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

	LongNumber nm4 = LongNumber("11");
	-nm4;
	EXPECT_EQ(nm4.sign(), false);
}
