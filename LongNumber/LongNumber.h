#pragma once
#include <string>

class LongNumber {
private:
	bool _sign; // true = "+", false = "-"
	std::string _number;
	void normalize();
	int cmp_abs(const std::string& a, const std::string& b) const;
	std::string add_abs(const std::string& a, const std::string& b) const;
	std::string sub_abs(const std::string& a, const std::string& b) const;
public:
	LongNumber() : _number("0"), _sign(true) {};
	LongNumber(const LongNumber&);
	LongNumber(std::string);
	
	inline bool sign() const noexcept { return _sign; }
	inline std::string number() const noexcept { return (_sign) ? _number : '-' + _number; }

	void sign(char);
	void number(std::string);

	std::string to_string() const;

	LongNumber& operator=(const LongNumber& other);

	LongNumber operator+(const LongNumber& other) const;
	LongNumber operator-(const LongNumber& other) const;
	LongNumber operator*(const LongNumber& other) const;
	LongNumber& operator+=(const LongNumber& other);
	LongNumber& operator-=(const LongNumber& other);
	LongNumber& operator*=(const LongNumber& other);

	bool operator<(const LongNumber&) const;
	bool operator>(const LongNumber&) const;
	bool operator==(const LongNumber&) const;
	bool operator!=(const LongNumber&) const;
	bool operator>=(const LongNumber&) const;
	bool operator<=(const LongNumber&) const;

	friend LongNumber operator-(LongNumber);

	char operator[](const size_t) const noexcept;
	LongNumber operator++(int) noexcept;
	LongNumber operator--(int) noexcept;

	LongNumber& operator++() noexcept;
	LongNumber& operator--() noexcept;

	friend std::ostream& operator<<(std::ostream&, const LongNumber&);
	friend std::istream& operator>>(std::istream&, LongNumber);
};