#pragma once
#include <string>

class LongNumber {
private:
	bool _sign; // true = "+", false = "-"
	std::string _number;
public:
	LongNumber() : _number(""), _sign(true) {};
	LongNumber(const LongNumber&);
	LongNumber(std::string);
	
	inline bool sign() const noexcept { return _sign; }
	inline std::string number() const noexcept { return _number; }

	void sign(char);
	void number(std::string);

	//LongNumber& operator+=(const LongNumber&);
	//LongNumber& operator-=(const LongNumber&);

	bool operator<(const LongNumber&);
	bool operator>(const LongNumber&);
	bool operator==(const LongNumber&);
	bool operator!=(const LongNumber&);
	friend LongNumber& operator-(LongNumber&);
};