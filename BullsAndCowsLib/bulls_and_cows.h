#pragma once
namespace BullsAndCowsGame {

    void GenarateComputerUniqueNumber(int* number, size_t number_range);

    void CalculateBullsAndCows(int& bulls, int& cows, int* number, int* user_input, size_t number_size, size_t input_size);

    void ConvertNumberToMass(int* user_number, int user_input, size_t number_size);

    inline bool CheckWin(size_t number_size, int bulls) {
        return (number_size == bulls) ? true : false;
    }
}