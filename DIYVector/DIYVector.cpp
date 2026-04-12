#include <iostream>
#include <initializer_list>
#include "DIYVector.h"

void Vector::optimize_mem() noexcept {
	bool reallocated = false;

	if (_mem._size == _mem._capacity) {
		_mem.reset_memory(calculate_capacity(_mem._size));
		reallocated = true;
	}
	else if ((_mem._capacity - _mem._size) > MEM_STEP) {
		_mem.reset_memory(_mem._capacity - MEM_STEP);
		reallocated = true;
	}

	if (reallocated) {
		_front = 0;
		_back = (_mem._size > 0) ? _mem._size - 1 : 0;
	}
}

void Vector::advance_front() noexcept {
	_front = (_front + 1) % _mem.capacity();
}

void Vector::retreat_front() noexcept {
	_front = (_front == 0) ? _mem.capacity() - 1 : _front - 1;
}

void Vector::advance_back() noexcept {
	_back = (_back + 1) % _mem.capacity();
}

void Vector::retreat_back() noexcept {
	_back = (_back == 0) ? _mem.capacity() - 1 : _back - 1;
}

size_t Vector::get_index(size_t logical_index) const noexcept {
	return (logical_index + _front) % _mem.capacity();
}

Vector::Vector(Vector&& other) : _mem(std::move(other._mem)), _front(other._front), _back(other._back) {
	other._front = 0;
	other._back = 0;
}

void Vector::push_front(double num) noexcept {
	optimize_mem();
	retreat_front();
	_mem._data[_front] = num;
	_mem._size++;
}

void Vector::push_back(double num) noexcept {
	optimize_mem();
	if (_mem._size > 0) {
		advance_back();
	}
	_mem._data[_back] = num;
	_mem._size++;
}

void Vector::pop_front() {
	if (_mem._size <= 0) {
		throw std::logic_error("You can't delete something that doesn't exist.");
	}
	optimize_mem();
	_mem._data[_front] = 0;
	advance_front();
	_mem._size--;
}

void Vector::pop_back() {
	if (_mem._size <= 0) {
		throw std::logic_error("You can't delete something that doesn't exist.");
	}
	optimize_mem();
	_mem._data[_back] = 0;
	retreat_back();
	_mem._size--;
}

void Vector::insert(double num, size_t index) {
	if (index > _mem._size) {
		throw std::out_of_range("Insert index out of range");
	}

	optimize_mem();
	if (_mem._size == 0) {
		push_back(num);
		return;
	}

	advance_back();
	_mem._size++;

	size_t logical_end = _mem._size - 1;
	// It is possible to add optimization in the form of automatic selection of the shift direction
	for (size_t i = logical_end; i > index; --i) {
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[index] = num;
}

void Vector::erase(size_t index) {
	if (index >= _mem._size) {
		throw std::out_of_range("Erase index out of range");
	}

	if (_mem._size == 0) {
		throw std::logic_error("Cannot erase from empty vector");
	}

	optimize_mem();

	if (_mem._size == 1) {
		_mem._size = 0;
		return;
	}

	for (size_t i = index; i < _mem._size - 1; ++i) {
		(*this)[i] = (*this)[i + 1];
	}

	_mem._size--;
	retreat_back();
}

double& Vector::operator[](size_t index) noexcept {
	size_t real_index = (_front + index) % _mem._capacity;
	return _mem._data[real_index];
}

double Vector::operator[](size_t index) const noexcept {
	size_t real_index = (_front + index) % _mem._capacity;
	return _mem._data[real_index];
}