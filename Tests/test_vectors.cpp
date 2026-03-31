#include "pch.h"
#include "memdata.h"
#define AI_TEST
#define AI_TEST_PLUS

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
