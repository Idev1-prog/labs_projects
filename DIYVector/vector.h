#pragma once
/*
#include <iostream>
#include "memdata.h"

class Vector {
    MemData _mem;         // хранилище данных + размер  + вместимость
    size_t _front;        // индекс первого элемента
    size_t _back;         // индекс последнего элемента
public:
    Vector(size_t size = 0);                 // конструктор по размеру + по умолчанию
    Vector(std::initializer_list<double>);   // конструктор по списку инициализации
    Vector(double*, size_t);                 // конструктор инициализации
    Vector(const Vector&);                   // конструктор копирования
    Vector(Vector&&);                        // конструктор с move-семантикой
    ~Vector() = default;                     // деструктор

    inline bool is_empty() const noexcept;          // проверка на пустоту
    inline bool is_full() const noexcept;           // проверка на переполнение

    inline size_t size() const noexcept;            // геттер размера
    inline size_t capacity() const noexcept;        // геттер вместимости
    inline double front() const;                    // геттер первого элемента
    inline double back() const;                     // геттер последнего элемента

    inline double& front();                         // сеттер первого элемента
    inline double& back();                          // сеттер последнего элемента

    void push_front(double) noexcept;               // вставка элемента в начало
    void push_back(double) noexcept;                // вставка элемента в конец
    void insert(double, size_t);                    // вставка элемента по позиции
    void pop_front();                               // удаление элемента из начала
    void pop_back();                                // удаление элемента из конца
    void erase(size_t);                             // удаление элемента по позиции

    Vector& operator=(const Vector&) noexcept;      // оператор присваивания
    Vector& operator=(Vector&&) noexcept;           // оператор присваивания с move-семантикой

    double operator[](size_t) const noexcept;       // оператор обращения по индексу константный
    double& operator[](size_t) noexcept;            // оператор обращения по индексу

    friend std::ostream& operator<<(std::ostream&, const Vector&);     // вывод
    friend std::istream& operator>>(std::istream&, Vector&);           // ввод
};
*/

