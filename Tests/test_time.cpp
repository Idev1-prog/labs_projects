#include "pch.h"

#include "CTime.h"
TEST(Base, BaseTest) {
	CTime c1;
	EXPECT_EQ(c1.second(), 4);
	EXPECT_EQ(c1.minute(), 3);
	EXPECT_EQ(c1.hour(), 1);
}

TEST(Base, BaseTest1) {
	CTime c1(10, 5, 3);
	EXPECT_EQ(c1.second(), 3);
	EXPECT_EQ(c1.minute(), 5);
	EXPECT_EQ(c1.hour(), 10);
}

TEST(Base, BaseTest2) {
	CTime c1(10, 5, 3);
	CTime c2(c1);
	EXPECT_EQ(c2.second(), 3);
	EXPECT_EQ(c2.minute(), 5);
	EXPECT_EQ(c2.hour(), 10);
}

TEST(Base, BaseTest3) {
	CTime c1(10, 5, 3);
	CTime c2(c1);
	c2.second(10);
	EXPECT_EQ(c2.second(), 10);
	EXPECT_EQ(c2.minute(), 5);
	EXPECT_EQ(c2.hour(), 10);
}

TEST(Base, BaseTest4) {
	CTime c1(10, 5, 3);
	CTime c2(c1);
	c2.minute(7);
	EXPECT_EQ(c2.second(), 3);
	EXPECT_EQ(c2.minute(), 7);
	EXPECT_EQ(c2.hour(), 10);
}

TEST(Base, BaseTest5) {
	CTime c1(10, 5, 3);
	CTime c2(c1);
	c2.hour(11);
	EXPECT_EQ(c2.second(), 3);
	EXPECT_EQ(c2.minute(), 5);
	EXPECT_EQ(c2.hour(), 11);
}