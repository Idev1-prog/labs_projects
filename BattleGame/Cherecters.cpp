#include <iostream>
#include "Cherecters.h"

void Warrior::attack(Character& other) {
	int total_dmg = _power + RandomNum::get(1, 10);
	int reflected_dmg = other.attaked(*this, total_dmg);

	if (reflected_dmg > 0) {
		_health -= reflected_dmg;
	}
}

int Warrior::attaked(const Character& other, int dmg) {
	int pure_damage = std::max(0, dmg - _armor);
	_health -= pure_damage;
	return 0;
}