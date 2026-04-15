#pragma once
#include <iostream>

class RandomNum {
private:
	static void init() {
		static bool initialized = false;
		if (!initialized) {
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			initialized = true;
		}
	}
public:
	static int get(int min, int max) {
		init();
		return min + (std::rand() % (max - min + 1));
	}
};

class Character {
protected:
	std::string _name;
	int _health;
	int _power;
public:
	Character() : _health(100), _power(10), _name("Unknown") {}
	Character(const Character& other) :
		_health(other._health),
		_power(other._power),
		_name(other._name) {}
	Character(const std::string& name, int hp, int power) :
		_name(name), 
		_health(hp), 
		_power(power) {}

	inline int health() const noexcept { return _health; }
	inline int power() const noexcept { return _power; }
	inline std::string name() const noexcept { return _name; }

	virtual void attack(Character&) = 0;
	virtual int attaked(const Character&, int) = 0;
	virtual bool is_alive() { return _health > 0; }
};

class Warrior : public Character {
	int _armor; // For direct damage only
public:
	Warrior() : Character("Warrior", 150, 15), _armor(5) {}
	Warrior(const std::string& name, int hp, int power, int armor)
		: Character(name, hp, power), _armor(armor) {
	}
	Warrior(const Warrior& other)
		: Character(other), _armor(other._armor) {
	}

	inline int get_armor() const { return _armor; }

	void attack(Character&) override;
	int attaked(const Character&, int) override;
};