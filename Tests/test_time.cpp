#include "pch.h"
#include "CTime.h"
#define TIME_TEST

#ifdef TIME_TEST


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


TEST(ExceptionTest, ConstructorsInvalidValues) {
    EXPECT_THROW(CTime(25, 10, 10), std::out_of_range);
    EXPECT_THROW(CTime(10, 60, 10), std::out_of_range);
    EXPECT_THROW(CTime(10, 10, 60), std::out_of_range);
    EXPECT_THROW(CTime(-1, 10, 10), std::out_of_range);

    EXPECT_THROW(CTime(25, 10), std::out_of_range);
    EXPECT_THROW(CTime(10, 60), std::out_of_range);
}

TEST(ExceptionTest, SettersInvalidValues) {
    CTime c1(10, 10, 10);

    EXPECT_THROW(c1.hour(24), std::out_of_range);
    EXPECT_THROW(c1.hour(-5), std::out_of_range);
    EXPECT_THROW(c1.minute(60), std::out_of_range);
    EXPECT_THROW(c1.minute(-1), std::out_of_range);
    EXPECT_THROW(c1.second(60), std::out_of_range);
    EXPECT_THROW(c1.second(-5), std::out_of_range);
}

TEST(AddTest, AddHours) {
    CTime t1(22, 15, 30);

    // Simple addition within the same day
    CTime t2 = t1.add_hours(2);
    EXPECT_EQ(t2.hour(), 0);
    EXPECT_EQ(t2.minute(), 15);
    EXPECT_EQ(t2.second(), 30);

    // Addition with wrap to next day
    CTime t3 = t1.add_hours(5);
    EXPECT_EQ(t3.hour(), 3);

    // Check that original object remains unchanged
    EXPECT_EQ(t1.hour(), 22);
}

TEST(AddTest, AddMinutes) {
    CTime t1(10, 45, 30);

    // Addition within the same hour
    CTime t2 = t1.add_minutes(10);
    EXPECT_EQ(t2.hour(), 10);
    EXPECT_EQ(t2.minute(), 55);

    // Addition that rolls over to the next hour
    CTime t3 = t1.add_minutes(20);
    EXPECT_EQ(t3.hour(), 11);
    EXPECT_EQ(t3.minute(), 5);

    // Addition that rolls over to the next day
    CTime t4(23, 30, 0);
    CTime t5 = t4.add_minutes(45);
    EXPECT_EQ(t5.hour(), 0);
    EXPECT_EQ(t5.minute(), 15);
}

TEST(AddTest, AddSeconds) {
    CTime t1(10, 30, 45);

    // Addition within the same minute
    CTime t2 = t1.add_seconds(10);
    EXPECT_EQ(t2.second(), 55);

    // Addition that rolls over to the next minute
    CTime t3 = t1.add_seconds(20);
    EXPECT_EQ(t3.minute(), 31);
    EXPECT_EQ(t3.second(), 5);

    // Addition that rolls over to the next hour
    CTime t4(10, 59, 30);
    CTime t5 = t4.add_seconds(40);
    EXPECT_EQ(t5.hour(), 11);
    EXPECT_EQ(t5.minute(), 0);
    EXPECT_EQ(t5.second(), 10);
}

TEST(CTimeTest, AllFunctionalityCheck) {
    CTime t1;
    EXPECT_EQ(t1.hour(), 1);

    CTime t2(15, 25, 35);
    EXPECT_EQ(t2.hour(), 15);

    CTime t3(t2);
    EXPECT_EQ(t3.hour(), 15);
    EXPECT_EQ(t3.minute(), 25);
    EXPECT_EQ(t3.second(), 35);

    t3.hour(10);
    t3.minute(30);
    t3.second(45);
    EXPECT_EQ(t3.hour(), 10);
    EXPECT_EQ(t3.minute(), 30);
    EXPECT_EQ(t3.second(), 45);

    CTime t4 = t3.add_hours(2).add_minutes(40).add_seconds(30);
    EXPECT_EQ(t4.hour(), 13);
    EXPECT_EQ(t4.minute(), 11);
    EXPECT_EQ(t4.second(), 15);

    CTime t5(8, 15);
    EXPECT_EQ(t5.hour(), 8);
    EXPECT_EQ(t5.minute(), 15);
    EXPECT_EQ(t5.second(), 0);
}

#endif // TIME_TEST