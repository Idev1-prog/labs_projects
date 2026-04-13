#include <iostream>
#include <initializer_list>
#include "memdata.h"

size_t calculate_capacity(size_t size) {
	if (size == 0) return MEM_STEP; // experement
	return size + MEM_STEP;
}

void MemData::clear_memory() noexcept {
	if (_data != nullptr) {
		delete[] _data;
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}
}

void MemData::set_memory(size_t size) noexcept {
	clear_memory();
	_data = new double[size];
	_capacity = size;
}

MemData::MemData(size_t size) {
	_size = size;
	_capacity = calculate_capacity(_size);
	set_memory(_capacity);
}

MemData::MemData(std::initializer_list<double> ini) {
	_size = ini.size();
	_capacity = calculate_capacity(_size);
	set_memory(_capacity);
	std::copy(ini.begin(), ini.end(), _data);
}

MemData::MemData(double* mass, size_t size) {
	_size = size;
	_capacity = calculate_capacity(_size);
	set_memory(_capacity);
	std::copy(mass, mass + size, _data);
}

MemData::MemData(const MemData& other) : _size(other._size), _capacity(other._capacity) {
	set_memory(_capacity);
	for (size_t i = 0; i < _size; ++i) {
		_data[i] = other._data[i];
	}
}

MemData::MemData(MemData&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(other._data) {
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
}

MemData::~MemData() {
	clear_memory();
}

void MemData::reset_memory(size_t size, size_t start_index) noexcept {
	if (size == _capacity) return;

	double* new_data = new double[size]();

	size_t copy_size = (_size < size) ? _size : size;
	for (size_t i = 0; i < copy_size; ++i) {
		new_data[i] = _data[(start_index + i) % _capacity];
	}

	delete[] _data;

	_data = new_data;
	_capacity = size;
	_size = copy_size; // не факт что надо
}

MemData& MemData::operator=(const MemData& other) noexcept {
	if (this == &other) {
		return *this;
	}

	set_memory(other._capacity);
	_size = other._size;
	_capacity = other._capacity;
	std::copy(other._data, other._data + _size, _data);

	return *this;
}

MemData& MemData::operator=(MemData&& other) noexcept {
	if (this == &other) {
		return *this;
	}

	clear_memory();
	_data = other._data;
	_capacity = other._capacity;
	_size = other._size;

	other._data = nullptr;
	other._capacity = 0;
	other._size = 0;

	return *this;
}
