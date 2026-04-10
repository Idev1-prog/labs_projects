#include <iostream>
#include <initializer_list>
#include "DIYVector.h"

void Vector::advance_front() {
	_front = (_front + 1) % _mem.capacity();
}

void Vector::retreat_front() {
	_front = (_front == 0) ? _mem.capacity() - 1 : _front - 1;
}

void Vector::advance_back() {
	_back = (_back + 1) % _mem.capacity();
}

void Vector::retreat_back() {
	_back = (_back == 0) ? _mem.capacity() - 1 : _back - 1;
}

size_t Vector::get_index(size_t logical_index) const noexcept {
	return (logical_index + _front) % _mem.capacity();
}

Vector::Vector(Vector&& other) : _mem(std::move(other._mem)), _front(other._front), _back(other._back) {
	other._front = 0;
	other._back = 0;
}

