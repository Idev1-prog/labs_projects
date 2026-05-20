#pragma once

#include <iostream>
#include "memdata.h"

class Vector {
    MemData _mem;         // хранилище данных + размер  + вместимость
    size_t _front;        // индекс первого элемента
    size_t _back;         // индекс последнего элемента
    void optimize_mem() noexcept;
    void advance_front() noexcept; // сдвиг вперед _front
    void retreat_front() noexcept; // сдвиг назад _front
    void advance_back() noexcept; // сдвиг вперед _back
    void retreat_back() noexcept; // сдвиг назад _back
    size_t get_index(size_t) const noexcept;
public:
    Vector(size_t size = 0): // конструктор по размеру + по умолчанию
        _mem(size), 
        _front(0), 
        _back((size > 0) ? size - 1 : 0) {}
    Vector(std::initializer_list<double> ini) : // конструктор по списку инициализации
        _mem(ini),
        _front(0),
        _back((ini.size() > 0) ? ini.size() - 1 : 0) {}
    Vector(double* data, size_t size) : // конструктор инициализации
        _mem(data, size),
        _front(0),
        _back((size > 0) ? size - 1 : 0) {}
    Vector(const Vector& other) : // конструктор копирования
        _mem(other._mem),
        _front(other._front),
        _back(other._back) {}
    Vector(Vector&&);                        // конструктор с move-семантикой
    ~Vector() = default;                     // деструктор

    inline bool is_empty()  const noexcept { return _mem.is_empty(); }          // проверка на пустоту
    inline bool is_full() const noexcept { return _mem.is_full(); }           // проверка на переполнение

    inline size_t size() const noexcept { return _mem.size(); }            // геттер размера
    inline size_t capacity() const noexcept { return _mem.capacity(); }        // геттер вместимости
    inline double front() const { 
        if (!_mem._size) throw std::out_of_range("Attempting to work with an empty array element");
        return _mem._data[_front]; 
    }                    // геттер первого элемента
    inline double back() const {
        if (!_mem._size) throw std::out_of_range("Attempting to work with an empty array element");
        return _mem._data[_back]; 
    }                     // геттер последнего элемента

    inline double& front() { 
        if (!_mem._size) throw std::out_of_range("Attempting to work with an empty array element");
        return _mem._data[_front]; 
    }                         // сеттер первого элемента
    inline double& back() { 
        if (!_mem._size) throw std::out_of_range("Attempting to work with an empty array element");
        return _mem._data[_back]; 
    };                          // сеттер последнего элемента

    void push_front(double) noexcept;               // вставка элемента в начало
    void push_back(double) noexcept;                // вставка элемента в конец
    void insert(double, size_t);                    // вставка элемента по позиции
    void pop_front();                               // удаление элемента из начала
    void pop_back();                                // удаление элемента из конца
    void erase(size_t);                             // удаление элемента по позиции
    void pop_front_few(size_t count) { for (int i = 0; i < count; ++i) pop_front(); }
    void pop_back_few(size_t count) { for (int i = 0; i < count; ++i) pop_back(); }
    void push_front_few(double*, size_t) noexcept; //It inserts elements from the input array one by one
    void push_back_few(double*, size_t) noexcept; //It inserts elements from the input array one by one
    void insert_few(double* elem, size_t index, size_t count);
    /*
    @param slice -> (first index, last index), the element at the last index is not deleted
    */
    void erase_few(std::pair<size_t, size_t> slice);

    Vector& operator=(const Vector&) noexcept;      // оператор присваивания
    Vector& operator=(Vector&&) noexcept;         // оператор присваивания с move-семантикой

    double operator[](size_t) const noexcept;       // оператор обращения по индексу константный
    double& operator[](size_t) noexcept;            // оператор обращения по индексу

    friend std::ostream& operator<<(std::ostream&, const Vector&);     // вывод
    friend std::istream& operator>>(std::istream&, Vector&);           // ввод

    friend void shaker_sort(Vector& vec) noexcept;   // шейкерная сортировка
    friend void shuffle(Vector& vec) noexcept;       // перемешивание
};


