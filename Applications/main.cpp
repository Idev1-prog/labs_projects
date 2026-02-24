#include <iostream>
#include "geometry.h"
#include "bulls_and_cows.h"
#define BULLS_AND_COWS
using std::cout;
using std::cin;
using std::endl;

#ifdef GEOMETRY
int main()
{
	Circle c1, c2;
	setlocale(LC_ALL, "Rus");
	cout << "Enter data for the 1st circle (format x, y, rad): ";
	cin >> c1.centre.x >> c1.centre.y >> c1.r;
	cout << "Enter data for the 2nd circle (format x, y, rad): ";
	std::cin >> c2.centre.x >> c2.centre.y >> c2.r;
	Posision_status* results4 = code_status(c1, c2);
	encode_status(results4);
}
#endif // GEOMETRY

#ifdef BULLS_AND_COWS
int main() {
	try {
		size_t user_dif_choice;
		int bulls = 0;
		int cows = 0;
		cout << "Select an arbitrary number of digits from 1 to 9: ";
		cin >> user_dif_choice;
		while (user_dif_choice < 1 || user_dif_choice > 9) {
			cout << "The selected number does not meet the criteria, enter a new number from 1 to 9: ";
			cin >> user_dif_choice;
		}
		int* computer_number = new int[user_dif_choice];
		int user_input;
		genarate_computer_unique_number(computer_number, user_dif_choice);
		cout << "The number is hidden" << endl;
		while (!check_win_codition_BAC(user_dif_choice, bulls)) {
			int* user_number = new int[user_dif_choice];
			cout << "Enter the number you want to guess (the size of the number is " << user_dif_choice << " )" << endl;
			cin >> user_input;
			reformatted_user_number(user_number, user_input, user_dif_choice);
			BACAnalyzer(bulls, cows, computer_number, user_number, user_dif_choice, user_dif_choice);
			cout << "Bulls: " << bulls << " Cows: " << cows << endl;
			delete[] user_number;
		}
		cout << "The number is guessed!";
		delete[] computer_number;
	}
	catch (const std::exception& e) {
		cout << "Fatal error: " << e.what() << "\nIt is recommended to check the built-in testing mechanisms." << endl;
		return 1;
	}
	return 0;
}
#endif // BULLS_AND_COWS
