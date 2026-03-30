#pragma once
#include <initializer_list>

#define MEM_STEP 15

int calculate_capacity(int);

//class Vector;

class MemData {
private:
    double* _data = nullptr;             // хранилище данных
    size_t _size;              // размер заполненной части хранилища
    size_t _capacity;          // вместимость хранилища
public:
    MemData(size_t size = 0);                // конструктор по размеру + по умолчанию
    MemData(std::initializer_list<double>);  // конструктор по списку инициализации
    MemData(double*, size_t);                // конструктор инициализации
    MemData(const MemData& other);           // конструктор копирования
    MemData(MemData&&) noexcept;             // конструктор с move-семантикой
    ~MemData();                              // деструктор

    inline bool is_empty() const noexcept {
        return _size == 0;
    }
    inline bool is_full() const noexcept {
        return _size == _capacity;
    }

    inline size_t size() const noexcept {
        return _size;
    }
    inline size_t capacity() const noexcept {
        return _capacity;
    }
    inline const double* const data() const noexcept {
        return _data;
    }

    void set_memory(size_t) noexcept;                                         // установка памяти без сохранения данных
    //void reset_memory(size_t size, size_t start_index = 0) noexcept;          // перевыделение памяти с сохранением данных
    void clear_memory() noexcept;                                             // очистка памяти

    //MemData& operator=(const MemData&) noexcept;         // оператор присваивания
    //MemData& operator=(MemData&&) noexcept;              // оператор присваивания с move-семантикой

    //friend class Vector;
};
