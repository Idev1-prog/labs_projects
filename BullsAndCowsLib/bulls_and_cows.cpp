#include <iostream>
#include "bulls_and_cows.h"

//void main() {
//    srand(time(0));
//    int mass[5];
//    genarate_computer_unique_number(mass, 5);
//    for (int i =0; i < 5; i++)
//        std::cout << mass[i];
//}

void genarate_computer_unique_number(int *number, size_t number_size) {
    if (number_size == 0 || number_size > 10) {
        throw std::invalid_argument("A unique number of this size cannot be created.");
    }
    for (int n, i = 0; i < number_size; ++i)
    {
        bool ok;
        do {
            ok = true;
            n = (i == 0)? (rand() % 9) + 1 : rand() % 9;
            for (int j = 0; j < i; ++j)
                if (number[j] == n) { ok = false; break; }
        } while (!ok);
        number[i] = n;
    }
}

void BACAnalyzer(int& bulls, int& cows, int* number, int* user_number, size_t number_size, size_t input_size) {
    bulls = 0;
    cows = 0;
    if (number == nullptr) {
        throw std::invalid_argument("number: nullptr");
    }
    if (user_number == nullptr) {
        throw std::invalid_argument("user_number: nullptr");
    }
    if (number_size <= 0) {
        throw std::invalid_argument("number_size must be positive");
    }
    if (number_size != input_size) {
        throw std::invalid_argument("arrays are not equal");
    }

    bool* number_used = new bool[number_size]();
    bool* user_used = new bool[number_size]();

    for (int i = 0; i < number_size; i++) {
        if (number[i] == user_number[i]) {
            bulls++;
            number_used[i] = true;
            user_used[i] = true;
        }
    }

    for (int i = 0; i < number_size; i++) {
        if (user_used[i]) continue;

        for (int j = 0; j < number_size; j++) {
            if (number_used[j]) continue;

            if (user_number[i] == number[j] && i != j) {
                cows++;
                number_used[j] = true;
                break;
            }
        }
    }

    delete[] number_used;
    delete[] user_used;
}

void reformatted_user_number(int* user_number, int user_input, size_t number_size) {
    for (int i = 0; i < number_size; i++) {
        user_number[i] = user_input % 10;
        user_input /= 10;
    }

    for (int i = 0; i < number_size / 2; i++) {
        int temp = user_number[i];
        user_number[i] = user_number[number_size - 1 - i];
        user_number[number_size - 1 - i] = temp;
    }
}


