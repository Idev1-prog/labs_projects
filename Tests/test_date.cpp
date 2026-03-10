#include "pch.h"
#include "CDate.h"
//#define DATE_TEST

#ifdef DATE_TEST

TEST(ClassDate, check_default_constructor) {
    CDate d1;
    EXPECT_EQ(d1.day(), 1);
    EXPECT_EQ(d1.month(), 1);
    EXPECT_EQ(d1.year(), 1970);
}

TEST(ClassDate, check_init_constructor) {
    CDate d1(15, 6, 2023);
    EXPECT_EQ(d1.day(), 15);
    EXPECT_EQ(d1.month(), 6);
    EXPECT_EQ(d1.year(), 2023);
}

TEST(ClassDate, check_copy_constructor) {
    CDate d1(15, 6, 2023);
    CDate d2(d1);
    EXPECT_EQ(d2.day(), 15);
    EXPECT_EQ(d2.month(), 6);
    EXPECT_EQ(d2.year(), 2023);
}

TEST(ClassDate, check_another_constructor) {
    CDate d1(15, 6);
    EXPECT_EQ(d1.day(), 15);
    EXPECT_EQ(d1.month(), 6);
    EXPECT_EQ(d1.year(), 1970);
}

TEST(ClassDate, test_invalid_day) {
    EXPECT_THROW(CDate(32, 1, 2023), std::out_of_range);
    EXPECT_THROW(CDate(0, 1, 2023), std::out_of_range);
    EXPECT_THROW(CDate(29, 2, 2023), std::out_of_range);

    CDate d1(15, 6, 2023);
    EXPECT_THROW(d1.day(32), std::out_of_range);
    EXPECT_THROW(d1.day(0), std::out_of_range);
}

TEST(ClassDate, test_invalid_month) {
    EXPECT_THROW(CDate(15, 13, 2023), std::out_of_range);
    EXPECT_THROW(CDate(15, 0, 2023), std::out_of_range);

    CDate d1(15, 6, 2023);
    EXPECT_THROW(d1.month(13), std::out_of_range);
    EXPECT_THROW(d1.month(0), std::out_of_range);
}

TEST(ClassDate, test_invalid_year) {
    EXPECT_THROW(CDate(15, 6, 0), std::out_of_range);
    EXPECT_THROW(CDate(15, 6, -1), std::out_of_range);

    CDate d1(15, 6, 2023);
    EXPECT_THROW(d1.year(0), std::out_of_range);
    EXPECT_THROW(d1.year(-5), std::out_of_range);
}

TEST(ClassDate, test_leap_year) {
    EXPECT_NO_THROW(CDate(29, 2, 2020));
    EXPECT_NO_THROW(CDate(29, 2, 2000));
    EXPECT_THROW(CDate(29, 2, 2021), std::out_of_range);
    EXPECT_THROW(CDate(29, 2, 1900), std::out_of_range);
}

TEST(ClassDate, check_set_day) {
    CDate d1(15, 6, 2023);
    d1.day(20);
    EXPECT_EQ(d1.day(), 20);
    EXPECT_EQ(d1.month(), 6);
    EXPECT_EQ(d1.year(), 2023);
}

TEST(ClassDate, check_set_month) {
    CDate d1(15, 6, 2023);
    d1.month(12);
    EXPECT_EQ(d1.day(), 15);
    EXPECT_EQ(d1.month(), 12);
    EXPECT_EQ(d1.year(), 2023);

    CDate d2(31, 1, 2023);
    d2.month(2);
    EXPECT_EQ(d2.day(), 28);
}

TEST(ClassDate, check_set_year) {
    CDate d1(15, 6, 2023);
    d1.year(2025);
    EXPECT_EQ(d1.day(), 15);
    EXPECT_EQ(d1.month(), 6);
    EXPECT_EQ(d1.year(), 2025);

    CDate d2(29, 2, 2020);
    d2.year(2021);
    EXPECT_EQ(d2.day(), 28);
}

TEST(ClassDate, check_add_days) {
    CDate d1(28, 2, 2023);
    CDate d2 = d1.add_days(2);
    EXPECT_EQ(d2.day(), 2);
    EXPECT_EQ(d2.month(), 3);
    EXPECT_EQ(d2.year(), 2023);

    CDate d5(1, 1, 2023);
    CDate d6 = d5.add_days(365);
    EXPECT_EQ(d6.day(), 1);
    EXPECT_EQ(d6.month(), 1);
    EXPECT_EQ(d6.year(), 2024);
}

TEST(ClassDate, check_add_months) {
    CDate d1(15, 6, 2023);
    CDate d2 = d1.add_months(3);
    EXPECT_EQ(d2.day(), 15);
    EXPECT_EQ(d2.month(), 9);
    EXPECT_EQ(d2.year(), 2023);

    CDate d4(31, 1, 2023);
    CDate d5 = d4.add_months(1);
    EXPECT_EQ(d5.day(), 28);
}

TEST(ClassDate, check_add_years) {
    CDate d1(15, 6, 2023);
    CDate d2 = d1.add_years(5);
    EXPECT_EQ(d2.day(), 15);
    EXPECT_EQ(d2.month(), 6);
    EXPECT_EQ(d2.year(), 2028);

    CDate d5(29, 2, 2020);
    CDate d6 = d5.add_years(1);
    EXPECT_EQ(d6.day(), 28);
}

#endif // DATE_TEST