#include "pch.h"
#include "bulls_and_cows.h"
//#define BAC_TEST
#ifdef BAC_TEST

TEST(CheckGeneratorCase, NonDynamicInputData) {
	int mass[6];
	genarate_computer_unique_number(mass, 6);
	for (int i = 0; i < 6; i++) {
		for (int j = i - 1; j > 0; j--) {
			EXPECT_TRUE(mass[i] != mass[j]);
		}
	}
	EXPECT_TRUE(mass[0] != 0);
}

TEST(CheckGeneratorCase, DynamicInputData) {
	int* mass = new int[8];
	genarate_computer_unique_number(mass, 8);
	for (int i = 0; i < 8; i++) {
		for (int j = i - 1; j > 0; j--) {
			EXPECT_TRUE(mass[i] != mass[j]);
		}
	}
	EXPECT_TRUE(mass[0] != 0);
	delete []mass;
}

TEST(CheckGeneratorCase, ZeroInputData) {
	int* mass = new int[0];
	ASSERT_ANY_THROW(genarate_computer_unique_number(mass, 0));
	delete []mass;
}

TEST(CheckGeneratorCase, OverbuffInputData) {
	int* mass = new int[15];
	EXPECT_THROW(genarate_computer_unique_number(mass, 15), std::invalid_argument);
	delete []mass;
}

TEST(CheckGeneratorCase, MultiDimensionalInputData) {
	for (int i = 1; i < 9; i++) {
		size_t size = i;
		int* mass = new int[size];
		genarate_computer_unique_number(mass, size);
		for (int i = 0; i < size; i++) {
			for (int j = i - 1; j > 0; j--) {
				EXPECT_TRUE(mass[i] != mass[j]);
			}
		}
		EXPECT_TRUE(mass[0] != 0);
		delete []mass;
	}
}

TEST(CheckBACAnalyzer, StandardData) {
	int a = 0;
	int b = 0;
	int mass[5] = { 1, 5, 3, 8, 9 };
	int user_data[5] = { 1, 3, 2, 9, 7 };
	BACAnalyzer(a, b, mass, user_data, 5, 5);
	EXPECT_EQ(a, 1);
	EXPECT_EQ(b, 2);
}

TEST(CheckBACAnalyzer, IdentlyUserInput) {
	int a = NULL;
	int b = NULL;
	int mass[5] = { 1, 5, 3, 8, 9 };
	int user_data[5] = { 1, 1, 1, 1, 1 };
	BACAnalyzer(a, b, mass, user_data, 5, 5);
	EXPECT_EQ(a, 1);
	EXPECT_EQ(b, 0);
}

TEST(CheckBACAnalyzer, WithRepeatingDigits) {
	int number[] = { 1, 2, 2, 3 };
	int user_number[] = { 2, 2, 1, 4 };
	int bulls = 0, cows = 0;
	size_t size = 4;

	BACAnalyzer(bulls, cows, number, user_number, size, size);
	EXPECT_EQ(bulls, 1);
	EXPECT_EQ(cows, 2);
}

TEST(CheckBACAnalyzer, IncorrectUserInput) {
	int a = NULL;
	int b = NULL;
	int mass[5] = { 1, 5, 3, 8, 9 };
	int user_data[3] = { 1, 3, 2 };
	EXPECT_THROW(BACAnalyzer(a, b, mass, user_data, 5, 3), std::invalid_argument);
}

TEST(CheckBACAnalyzer, IncorrectComputerInput) {
	int a = NULL;
	int b = NULL;
	int mass[6] = { 1, 5, 3, 8, 9, 4 };
	int user_data[5] = { 1, 3, 2, 2, 8 };
	EXPECT_THROW(BACAnalyzer(a, b, mass, user_data, 6, 5), std::invalid_argument);
}

TEST(CheckTools, StandardData) {
	int* mass = new int[6];
	reformatted_user_number(mass, 441261, 6);
	EXPECT_EQ(mass[0], 4);
	EXPECT_EQ(mass[1], 4);
	EXPECT_EQ(mass[2], 1);
	EXPECT_EQ(mass[3], 2);
	EXPECT_EQ(mass[4], 6);
	EXPECT_EQ(mass[5], 1);
}

#endif // BAC_TEST