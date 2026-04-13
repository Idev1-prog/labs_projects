#include "pch.h"
#include "LongNumber.h"

//#define LONG_NUMBER_TEST

#ifdef LONG_NUMBER_TEST


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

#endif // LONG_NUMBER_TEST


//#define LONG_NUMBER_TESTS

#ifdef LONG_NUMBER_TESTS

TEST(ClassLongNumber, can_create_with_default_constructor) {
    LongNumber ln;
    EXPECT_EQ(ln.to_string(), "0");
}

TEST(ClassLongNumber, can_create_with_init_constructor) {
    LongNumber ln("42322");
    EXPECT_EQ(ln.to_string(), "42322");
}

TEST(ClassLongNumber, can_create_with_copy_constructor) {
    LongNumber ln1("45654523");
    LongNumber ln2(ln1);
    EXPECT_EQ(ln2.to_string(), "45654523");
}

TEST(ClassLongNumber, can_copy) {
    LongNumber ln1("45654523");
    LongNumber ln2;

    ln2 = ln1;

    EXPECT_EQ(ln2.to_string(), "45654523");
}

TEST(ClassLongNumber, can_applay_unary_minus) {
    LongNumber ln1("45654523");
    LongNumber ln2, ln3;

    ln2 = -ln1;
    ln3 = -ln2;

    EXPECT_EQ(ln1.to_string(), "45654523");
    EXPECT_EQ(ln2.to_string(), "-45654523");
    EXPECT_EQ(ln3.to_string(), "45654523");
}

TEST(ClassLongNumber, can_compare_grater) {
    LongNumber ln_4463("4463");
    LongNumber ln_7523("7523");
    LongNumber ln_523("523");
    LongNumber ln__563("-563");
    LongNumber ln__265("-265");
    LongNumber ln__425645("-425645");

    EXPECT_TRUE(ln_523 > ln__563);
    EXPECT_TRUE(ln__563 > ln__425645);
    EXPECT_TRUE(ln_7523 > ln_523);
    EXPECT_TRUE(ln_7523 > ln_4463);
    EXPECT_TRUE(ln__265 > ln__563);

    EXPECT_FALSE(ln__563 > ln_523);
    EXPECT_FALSE(ln__425645 > ln__563);
    EXPECT_FALSE(ln_523 > ln_7523);
    EXPECT_FALSE(ln_4463 > ln_7523);
    EXPECT_FALSE(ln__563 > ln__265);
}

TEST(ClassLongNumber, can_compare_eq) {
    LongNumber ln_4463("4463");
    LongNumber ln_124463("124463");
    LongNumber ln__4463("-4463");
    LongNumber ln_523("523");
    LongNumber ln__523("-523");
    LongNumber ln_563("563");
    LongNumber ln__563("-563");

    EXPECT_TRUE(ln_4463 == ln_4463);
    EXPECT_TRUE(ln__4463 == ln__4463);

    EXPECT_FALSE(ln_4463 == ln__4463);
    EXPECT_FALSE(ln__4463 == ln_4463);
    EXPECT_FALSE(ln_4463 == ln_124463);
    EXPECT_FALSE(ln_124463 == ln_4463);
    EXPECT_FALSE(ln_523 == ln_563);
    EXPECT_FALSE(ln__523 == ln__563);
}

TEST(ClassLongNumber, can_add_positive_numbers) {
    LongNumber ln_0;
    LongNumber ln_9663("9663");
    LongNumber ln_4212("4212");
    LongNumber ln_4463("4463");
    LongNumber ln_5693("5693");
    LongNumber ln_523("523");

    LongNumber ln_99999("99999");
    LongNumber ln_1("1");

    LongNumber res;

    res = ln_4212 + ln_4463;
    EXPECT_EQ(res.to_string(), "8675");

    res = ln_4463 + ln_523;
    EXPECT_EQ(res.to_string(), "4986");

    res = ln_4463 + ln_5693;
    EXPECT_EQ(res.to_string(), "10156");

    res = ln_523 + ln_9663;
    EXPECT_EQ(res.to_string(), "10186");

    res = ln_99999 + ln_1;
    EXPECT_EQ(res.to_string(), "100000");

    res = ln_0 + ln_0;
    EXPECT_EQ(res.to_string(), "0");
}

TEST(ClassLongNumber, can_add_negitive_numbers) {
    LongNumber ln__4463("-4463");
    LongNumber ln__6842("-6842");
    LongNumber ln__523("-523");
    LongNumber ln__5242("-5242");

    LongNumber res;

    res = ln__4463 + ln__5242;
    EXPECT_EQ(res.to_string(), "-9705");

    res = ln__4463 + ln__6842;
    EXPECT_EQ(res.to_string(), "-11305");

    res = ln__523 + ln__4463;
    EXPECT_EQ(res.to_string(), "-4986");
}

TEST(ClassLongNumber, can_add_numbers_with_different_sign) {
    LongNumber ln__4463("-4463");
    LongNumber ln_42("42");
    LongNumber ln_6842("6842");
    LongNumber ln__6842("-6842");
    LongNumber ln_6812("6812");
    LongNumber ln_6860("6860");

    LongNumber res;

    res = ln__4463 + ln_6842;
    EXPECT_EQ(res.to_string(), "2379");

    res = ln_6842 + ln__4463;
    EXPECT_EQ(res.to_string(), "2379");

    res = ln_6842 + ln__6842;
    EXPECT_EQ(res.to_string(), "0");

    res = ln__4463 + ln_42;
    EXPECT_EQ(res.to_string(), "-4421");

    res = ln_42 + ln__4463;
    EXPECT_EQ(res.to_string(), "-4421");

    res = ln__6842 + ln_6812;
    EXPECT_EQ(res.to_string(), "-30");

    res = ln_6860 + ln__6842;
    EXPECT_EQ(res.to_string(), "18");
}

TEST(ClassLongNumber, can_mult) {
    LongNumber ln_0;
    LongNumber ln_125("125");
    LongNumber ln_35("35");
    LongNumber ln__125("-125");
    LongNumber ln__35("-35");

    LongNumber res;

    res = ln_125 * ln_35;
    EXPECT_EQ(res.to_string(), "4375");

    res = ln_35 * ln_125;
    EXPECT_EQ(res.to_string(), "4375");

    res = ln__125 * ln__35;
    EXPECT_EQ(res.to_string(), "4375");

    res = ln__125 * ln_35;
    EXPECT_EQ(res.to_string(), "-4375");

    res = ln_125 * ln__35;
    EXPECT_EQ(res.to_string(), "-4375");


    res = ln_125 * ln_0;
    EXPECT_EQ(res.to_string(), "0");
}

TEST(ClassLongNumber, can_increment) {
    LongNumber ln_0;
    LongNumber ln__9660("-9660");
    LongNumber ln_99999("99999");

    ln_0++;
    ln__9660++;
    ln_99999++;

    EXPECT_EQ(ln_0.to_string(), "1");
    EXPECT_EQ(ln__9660.to_string(), "-9659");
    EXPECT_EQ(ln_99999.to_string(), "100000");

    EXPECT_EQ((++ln_0).to_string(), "2");
    EXPECT_EQ((++ln__9660).to_string(), "-9658");
    EXPECT_EQ((++ln_99999).to_string(), "100001");

    EXPECT_EQ(ln_0.to_string(), "2");
    EXPECT_EQ(ln__9660.to_string(), "-9658");
    EXPECT_EQ(ln_99999.to_string(), "100001");

    EXPECT_EQ((ln_0++).to_string(), "2");
    EXPECT_EQ((ln__9660++).to_string(), "-9658");
    EXPECT_EQ((ln_99999++).to_string(), "100001");

    EXPECT_EQ(ln_0.to_string(), "3");
    EXPECT_EQ(ln__9660.to_string(), "-9657");
    EXPECT_EQ(ln_99999.to_string(), "100002");
}

TEST(ClassLongNumber, can_decrement) {
    LongNumber ln_0;
    LongNumber ln__9669("-9669");
    LongNumber ln_10000("10000");

    ln_0--;
    ln__9669--;
    ln_10000--;

    EXPECT_EQ(ln_0.to_string(), "-1");
    EXPECT_EQ(ln__9669.to_string(), "-9670");
    EXPECT_EQ(ln_10000.to_string(), "9999");

    EXPECT_EQ((--ln_0).to_string(), "-2");
    EXPECT_EQ((--ln__9669).to_string(), "-9671");
    EXPECT_EQ((--ln_10000).to_string(), "9998");

    EXPECT_EQ(ln_0.to_string(), "-2");
    EXPECT_EQ(ln__9669.to_string(), "-9671");
    EXPECT_EQ(ln_10000.to_string(), "9998");

    EXPECT_EQ((ln_0--).to_string(), "-2");
    EXPECT_EQ((ln__9669--).to_string(), "-9671");
    EXPECT_EQ((ln_10000--).to_string(), "9998");

    EXPECT_EQ(ln_0.to_string(), "-3");
    EXPECT_EQ(ln__9669.to_string(), "-9672");
    EXPECT_EQ(ln_10000.to_string(), "9997");
}

#endif