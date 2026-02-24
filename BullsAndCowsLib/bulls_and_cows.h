#pragma once

void genarate_computer_unique_number(int *number, size_t number_range);

void BACAnalyzer(int& bulls, int& cows, int* number, int *user_input, size_t number_size, size_t input_size);

void reformatted_user_number(int* user_number, int user_input, size_t number_size);

inline bool check_win_codition_BAC(size_t number_size, int bulls) {
    return (number_size == bulls) ? true : false;
}