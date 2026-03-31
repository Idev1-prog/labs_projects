#include "pch.h"
#include "memdata.h"
//#define AI_TEST
//#define AI_TEST_PLUS
#define MEMDATA_TESTS

#ifdef MEMDATA_TESTS

TEST(FunctionsForMemData, calculate_capacity) {
    EXPECT_EQ(calculate_capacity(10), 25);
    EXPECT_EQ(calculate_capacity(0), 0);
}

TEST(ClassMemData, can_create_with_default_constructor) {
    MemData md;
    EXPECT_EQ(md.size(), 0);
}

TEST(ClassMemData, can_create_with_constructor_by_size) {
    MemData md(5);
    EXPECT_EQ(md.size(), 5);
    EXPECT_EQ(md.capacity(), 20);
}

TEST(ClassMemData, can_create_with_constructor_by_initializer_list) {
    MemData md = { 1.0, 3.4, 1.1 };
    EXPECT_EQ(md.size(), 3);
    EXPECT_EQ(md.capacity(), 18);
    EXPECT_DOUBLE_EQ(md.data()[1], 3.4);
}

TEST(ClassMemData, can_create_with_init_constructor) {
    double a[] = { 3.5, 11, 2.2 };
    MemData md(a, 3);
    EXPECT_EQ(md.size(), 3);
    EXPECT_EQ(md.capacity(), 18);
    EXPECT_DOUBLE_EQ(md.data()[1], 11.0);
}

TEST(ClassMemData, can_create_with_copy_constructor) {
    MemData md1 = { 1.0, 3.4, 1.1 };
    MemData md2(md1);
    EXPECT_EQ(md1.data()[1], md2.data()[1]);
    EXPECT_EQ(md2.size(), 3);
}

TEST(ClassMemData, can_create_with_move_constructor) {
    MemData md1 = { 1.0, 3.4, 1.1 };
    MemData md2(std::move(md1));

    EXPECT_EQ(md1.data(), nullptr);
    EXPECT_DOUBLE_EQ(md2.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md2.data()[1], 3.4);
    EXPECT_DOUBLE_EQ(md2.data()[2], 1.1);
    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.capacity(), 18);

    EXPECT_TRUE(md1.is_empty());
}

TEST(ClassMemData, can_is_empty) {
    MemData md;
    EXPECT_TRUE(md.is_empty());
}

TEST(ClassMemData, can_is_full) {
    MemData md1;
    EXPECT_TRUE(md1.is_full());

    MemData md2 = { 1.0, 2.0, 3.0 };
    md2.clear_memory();
    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.capacity(), calculate_capacity(3));
    EXPECT_FALSE(md2.is_full());
}

TEST(ClassMemData, can_set_memory_for_empty) {
    MemData md1;
    EXPECT_NO_THROW(md1.set_memory(md1.size()));
    EXPECT_NE(md1.data(), nullptr);
}

TEST(ClassMemData, can_set_memory_for_not_empty) {
    MemData md1(5);
    EXPECT_NO_THROW(md1.set_memory(md1.size()));
    EXPECT_NE(md1.data(), nullptr);
}

TEST(ClassMemData, can_set_memory_without_reallocation) {
    MemData md1 = { 1.0, 2.0, 3.0 };
    EXPECT_NO_THROW(md1.set_memory(md1.size()));
    EXPECT_NE(md1.data(), nullptr);
}

TEST(ClassMemData, can_reset_memory_for_empty) {
    MemData md;

    md.reset_memory(10);

    EXPECT_EQ(md.capacity(), 10);
    EXPECT_NE(md.data(), nullptr);
}

TEST(ClassMemData, can_reset_memory_for_not_empty_increase) {
    MemData md = { 1.0, 2.0, 3.0 };
    const double* old_data = md.data();

    md.reset_memory(10);

    EXPECT_EQ(md.capacity(), 10);
    EXPECT_EQ(md.size(), 3);
    EXPECT_NE(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}

TEST(ClassMemData, can_reset_memory_for_not_empty_decrease) {
    MemData md = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    const double* old_data = md.data();

    md.reset_memory(3);

    EXPECT_EQ(md.capacity(), 3);
    EXPECT_EQ(md.size(), 3);
    EXPECT_NE(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}

TEST(ClassMemData, can_reset_memory_without_reallocation) {
    MemData md = { 1.0, 2.0, 3.0 };
    const double* old_data = md.data();
    size_t old_capacity = md.capacity();

    md.reset_memory(old_capacity);

    EXPECT_EQ(md.capacity(), old_capacity);
    EXPECT_EQ(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}

TEST(ClassMemData, can_reset_memory_with_shift) {
    MemData md = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    const double* old_data = md.data();

    md.reset_memory(5, 2);  // start_index = 2

    EXPECT_EQ(md.capacity(), 5);
    EXPECT_EQ(md.size(), 5);
    EXPECT_NE(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 3.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 4.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 5.0);
}

TEST(ClassMemData, can_clear_memory_for_empty) {
    MemData md1;
    md1.clear_memory();
    EXPECT_EQ(md1.data(), nullptr);
}

TEST(ClassMemData, can_clear_memory_for_not_empty) {
    MemData md1 = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    md1.clear_memory();
    EXPECT_EQ(md1.data(), nullptr);
}

TEST(ClassMemData, can_assigment) {
    MemData md1 = { 1.0, 2.0, 3.0 };
    MemData md2;

    md2 = md1;

    EXPECT_EQ(md2.size(), 3);
    EXPECT_NE(md2.data(), md1.data());
    EXPECT_DOUBLE_EQ(md2.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md2.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md2.data()[2], 3.0);
}

TEST(ClassMemData, can_move_assigment) {
    MemData md1 = { 1.0, 2.0, 3.0 };
    const double* md1_data = md1.data();
    MemData md2;

    md2 = std::move(md1);

    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.data(), md1_data);
    EXPECT_DOUBLE_EQ(md2.data()[0], 1.0);

    EXPECT_EQ(md1.size(), 0);
    EXPECT_EQ(md1.data(), nullptr);
}

#endif

#ifdef AI_TEST
TEST(MemDataTest, DefaultConstructor) {
    MemData md;

    EXPECT_EQ(md.size(), 0);
    EXPECT_TRUE(md.is_empty());
}

TEST(MemDataTest, ConstructorWithSize) {
    MemData md(10);

    EXPECT_EQ(md.size(), 10);
    EXPECT_GE(md.capacity(), 10);
    EXPECT_NE(md.data(), nullptr);
}

TEST(MemDataTest, ConstructorWithInitializerList) {
    MemData md = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    EXPECT_EQ(md.size(), 5);
    EXPECT_FALSE(md.is_empty());

    const double* data = md.data();
    EXPECT_DOUBLE_EQ(data[0], 1.0);
    EXPECT_DOUBLE_EQ(data[1], 2.0);
    EXPECT_DOUBLE_EQ(data[2], 3.0);
    EXPECT_DOUBLE_EQ(data[3], 4.0);
    EXPECT_DOUBLE_EQ(data[4], 5.0);
}

TEST(MemDataTest, ConstructorWithArray) {
    double arr[] = { 1.1, 2.2, 3.3 };
    MemData md(arr, 3);

    EXPECT_EQ(md.size(), 3);
    const double* data = md.data();
    EXPECT_DOUBLE_EQ(data[0], 1.1);
    EXPECT_DOUBLE_EQ(data[1], 2.2);
    EXPECT_DOUBLE_EQ(data[2], 3.3);
}

TEST(MemDataTest, CopyConstructor) {
    MemData original = { 1.0, 2.0, 3.0 };
    MemData copy(original);

    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.capacity(), original.capacity());
    EXPECT_NE(copy.data(), original.data()); // Разные указатели

    // Данные совпадают
    for (size_t i = 0; i < original.size(); ++i) {
        EXPECT_DOUBLE_EQ(copy.data()[i], original.data()[i]);
    }
}

TEST(MemDataTest, MoveConstructor) {
    MemData original = { 1.0, 2.0, 3.0 };
    const double* original_ptr = original.data();
    size_t original_size = original.size();

    MemData moved(std::move(original));

    // Проверяем перемещенный объект
    EXPECT_EQ(moved.size(), original_size);
    EXPECT_EQ(moved.data(), original_ptr);

    // Проверяем исходный объект (должен быть пуст)
    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.data(), nullptr);
    EXPECT_TRUE(original.is_empty());
}
TEST(MemDataTest, ClearMemory) {
    MemData md = { 1.0, 2.0, 3.0 };
    md.clear_memory();

    EXPECT_EQ(md.data(), nullptr);
}
TEST(MemDataTest, SetMemory) {
    MemData md(5);

    // Проверяем начальное состояние
    size_t old_capacity = md.capacity();
    EXPECT_EQ(old_capacity, calculate_capacity(5));

    // Вызываем set_memory
    md.set_memory(20);

    // Проверяем результат
    EXPECT_EQ(md.capacity(), 20);
    EXPECT_NE(md.data(), nullptr);

    // память выделена и работает
    double* data = const_cast<double*>(md.data()); // снимаем const
    data[0] = 42.0;
    EXPECT_DOUBLE_EQ(data[0], 42.0);
}

#ifdef AI_TEST_PLUS
TEST(MemDataTest, IsEmpty) {
    MemData md1;
    EXPECT_TRUE(md1.is_empty());

    MemData md2(5);
    EXPECT_FALSE(md2.is_empty());
}

TEST(MemDataTest, Getters) {
    MemData md(15);

    EXPECT_EQ(md.size(), 15);
    EXPECT_EQ(md.capacity(), calculate_capacity(15));
    EXPECT_NE(md.data(), nullptr);
}


TEST(MemDataTest, ResetMemory) {
    MemData md = { 1.0, 2.0, 3.0 };
    const double* old_data = md.data();

    md.reset_memory(10);

    EXPECT_EQ(md.capacity(), 10);
    EXPECT_NE(md.data(), old_data);

    // Данные сохранились
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}


// ==================== ТЕСТЫ ОПЕРАТОРОВ ====================

TEST(MemDataTest, CopyAssignment) {
    MemData original = { 1.0, 2.0, 3.0 };
    MemData copy;

    copy = original;

    EXPECT_EQ(copy.size(), original.size());
    EXPECT_NE(copy.data(), original.data());

    for (size_t i = 0; i < original.size(); ++i) {
        EXPECT_DOUBLE_EQ(copy.data()[i], original.data()[i]);
    }
}

TEST(MemDataTest, MoveAssignment) {
    MemData original = { 1.0, 2.0, 3.0 };
    const double* original_ptr = original.data();

    MemData target;
    target = std::move(original);

    EXPECT_EQ(target.size(), 3);
    EXPECT_EQ(target.data(), original_ptr);

    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.data(), nullptr);
}

#endif // AI_TEST_PLUS

#endif // AI_TEST
