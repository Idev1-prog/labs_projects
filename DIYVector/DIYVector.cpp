#include <iostream>
#include <initializer_list>
#include "DIYVector.h"

void Vector::optimize_mem() noexcept {
	bool reallocated = false;
	size_t new_capacity;

	if (_mem._size == _mem._capacity) {
		new_capacity = calculate_capacity(_mem._size);
		reallocated = true;
	}
	else if ((_mem._capacity - _mem._size) > MEM_STEP && _mem._capacity > MEM_STEP) {
		new_capacity = _mem._capacity - MEM_STEP;
		reallocated = true;
	}

	if (reallocated) {
		_mem.reset_memory(new_capacity, _front);
		_front = 0;
		_back = (_mem._size > 0) ? _mem._size - 1 : 0;
	}
	if (_mem._size == 0) {
		_front = 0;
		_back = 0;
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
	_mem._data[_front] = 0;
	advance_front();
	_mem._size--;
	optimize_mem();
}

void Vector::pop_back() {
	if (_mem._size <= 0) {
		throw std::logic_error("You can't delete something that doesn't exist.");
	}
	_mem._data[_back] = 0;
	retreat_back();
	_mem._size--;
	optimize_mem();
}

void Vector::insert(double num, size_t index) {
	if (index > _mem._size || index < 0) {
		throw std::out_of_range("Insert index out of range");
	}

	optimize_mem();
	if (_mem._size == 0) {
		push_back(num);
		return;
	}

	if (index == 0) {
		push_front(num);
		return;
	}

	if (index == _mem._size) {
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
	if (index >= _mem._size || index < 0) {
		throw std::out_of_range("Erase index out of range");
	}

	if (_mem._size == 0) {
		throw std::logic_error("Cannot erase from empty vector");
	}

	optimize_mem();

	if (_mem._size == 1) {
		pop_back();
		return;
	}
	if (index == 0) {
		pop_front();
		return;
	}
	if (index == (_mem._size - 1)) {
		pop_back();
		return;
	}

	for (size_t i = index; i < _mem._size - 1; ++i) {
		(*this)[i] = (*this)[i + 1];
	}

	_mem._size--;
	retreat_back();
}

void Vector::push_front_few(double* numbers, size_t count) noexcept {
	for (int i = 0; i < count; ++i) {
		push_front(numbers[i]);
	}
}

void Vector::push_back_few(double* numbers, size_t count) noexcept {
	for (int i = 0; i < count; ++i) {
		push_back(numbers[i]);
	}
}

double& Vector::operator[](size_t index) noexcept {
	size_t real_index = (_front + index) % _mem._capacity;
	return _mem._data[real_index];
}

double Vector::operator[](size_t index) const noexcept {
	size_t real_index = (_front + index) % _mem._capacity;
	return _mem._data[real_index];
}

Vector& Vector::operator=(const Vector& other) noexcept {
	if (this != &other) {
		_mem = other._mem;
		_front = other._front;
		_back = other._back;
	}
	return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
	if (this != &other) {
		_mem = std::move(other._mem);
		_front = other._front;
		_back = other._back;

		other._front = 0;
		other._back = 0;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
	out << "{ ";
	size_t size = vector._mem.size();
	for (int i = 0; i < size - 1; ++i) {
		out << vector[i] << "," << " ";
	}
	out << vector[size - 1] << " ";
	out << "}";
	return out;
}

std::istream& operator>>(std::istream& in, Vector& vector) {
	size_t expected_size;
	if (!(in >> expected_size)) {
		return in;
	}

	if (vector.size() > 0) {
		vector._mem.clear_memory();
	}

	double value;
	for (size_t i = 0; i < expected_size && in >> value; ++i) {
		vector.push_back(value);
	}

	return in;
}

void shaker_sort(Vector& vec) noexcept {
	const size_t n = vec.size();
	if (n <= 1) return;
	bool swapped = true;
	size_t start = 0;
	size_t end = n - 1;

	while (swapped) {
		swapped = false;

		for (size_t i = start; i < end; ++i) {
			if (vec[i] > vec[i + 1]) {
				std::swap(vec[i], vec[i + 1]);
				swapped = true;
			}
		}

		if (!swapped) break;
		--end;
		swapped = false;

		for (size_t i = end; i > start; --i) {
			if (vec[i] < vec[i - 1]) {
				std::swap(vec[i], vec[i - 1]);
				swapped = true;
			}
		}
		++start;
	}
}

void shuffle(Vector& vec) noexcept {
	const size_t n = vec.size();
	if (n <= 1) return;

	for (size_t i = n - 1; i > 0; --i) {
		size_t j = static_cast<size_t>(rand() % (i + 1));
		std::swap(vec[i], vec[j]);
	}
}