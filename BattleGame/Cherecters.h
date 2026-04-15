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
	virtual int attaked(const Character&, int, int) = 0;
	virtual bool is_alive() { return _health > 0; }
};

class Warrior : public Character {
	int _armor; // For not pure damage only
public:
	Warrior() : Character("Warrior", 150, 15), _armor(5) {}
	Warrior(const std::string& name, int hp, int power, int armor) : 
		Character(name, hp, power){
		_armor = (armor > 0) ? armor : 0;
}
	Warrior(const Warrior& other) : 
		Character(other), 
		_armor(other._armor) { }

	inline int get_armor() const { return _armor; }

	void attack(Character&) override;
	int attaked(const Character&, int, int) override;
};

class Necrolit : public Character {
	bool _second_life = true;
public:
	Necrolit() : 
		Character("Necrolit", 150, 15) {}
	Necrolit(const std::string& name, int hp, int power) :
		Character(name, hp, power) { }
	Necrolit(const Necrolit& other) : 
		Character(other),
		_second_life(other._second_life) { }

	inline bool get_second_life() const { return _second_life; }

	void attack(Character&) override;
	int attaked(const Character&, int, int) override;

private:
	//void move_rand() override; TDB maybe
	void reincarnation() noexcept;
};

class Trickster : public Character {
	size_t _evasion;
	size_t _spiks;
public:
	Trickster() : 
		Character("Trickster", 150, 15),
		_evasion(5),
		_spiks(5) { }
	Trickster(const std::string& name, int hp, int power, size_t evasion, size_t spiks) :
		Character(name, hp, power),
		_evasion(evasion),
		_spiks(spiks) { }
	Trickster(const Trickster& other) :
		Character(other),
		_evasion(other._evasion),
		_spiks(other._spiks) { }

	inline unsigned int evasion() const { return _evasion; }
	inline unsigned int spiks() const { return _spiks; }

	void attack(Character&) override;
	int attaked(const Character&, int, int) override;
};