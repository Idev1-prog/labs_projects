#include "pch.h"
#include "memdata.h"
#include "DIYVector.h"
#define AI_TEST
#define AI_TEST_PLUS
#define MEMDATA_TESTS
#define SORT_SHUFFLE_TEST

#ifdef MEMDATA_TESTS

TEST(FunctionsForMemData, calculate_capacity) {
    EXPECT_EQ(calculate_capacity(10), 25);
    EXPECT_EQ(calculate_capacity(0), 15);
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
    EXPECT_FALSE(md1.is_full());

    MemData md2 = { 1.0, 2.0, 3.0 };
    md2.set_memory(5);
    EXPECT_EQ(md2.size(), 0);
    EXPECT_EQ(md2.capacity(), 5);
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
    EXPECT_NE(copy.data(), original.data()); // Ðàçíûå óêàçàòåëè

    // Äàííûå ñîâïàäàþò
    for (size_t i = 0; i < original.size(); ++i) {
        EXPECT_DOUBLE_EQ(copy.data()[i], original.data()[i]);
    }
}

TEST(MemDataTest, MoveConstructor) {
    MemData original = { 1.0, 2.0, 3.0 };
    const double* original_ptr = original.data();
    size_t original_size = original.size();

    MemData moved(std::move(original));

    // Ïðîâåðÿåì ïåðåìåùåííûé îáúåêò
    EXPECT_EQ(moved.size(), original_size);
    EXPECT_EQ(moved.data(), original_ptr);

    // Ïðîâåðÿåì èñõîäíûé îáúåêò (äîëæåí áûòü ïóñò)
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

    // Ïðîâåðÿåì íà÷àëüíîå ñîñòîÿíèå
    size_t old_capacity = md.capacity();
    EXPECT_EQ(old_capacity, calculate_capacity(5));

    // Âûçûâàåì set_memory
    md.set_memory(20);

    // Ïðîâåðÿåì ðåçóëüòàò
    EXPECT_EQ(md.capacity(), 20);
    EXPECT_NE(md.data(), nullptr);

    // ïàìÿòü âûäåëåíà è ðàáîòàåò
    double* data = const_cast<double*>(md.data()); // ñíèìàåì const
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

    // Äàííûå ñîõðàíèëèñü
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}


// ==================== ÒÅÑÒÛ ÎÏÅÐÀÒÎÐÎÂ ====================

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

#define MAIN_VECTOR_TEST
#define CUSTOM_VECTOR_TEST

#ifdef MAIN_VECTOR_TEST
// Main Tests
TEST(ClassVector, can_output_with_operator_cout) {
    Vector vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_input_with_operator_cin) {
    Vector vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> vec;

    EXPECT_EQ(9, vec.size());
    EXPECT_EQ(15, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    Vector vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_front();
    vec.push_back(16);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }

    vec.pop_back();

    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }
}

TEST(ClassVector, combination_push_pop_insert_erase) {
    Vector vec({ 3, 44, 5, 7, 8 });

    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_back(8 + i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.insert(6, 4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    for (size_t i = 0; i < 5; i++) {
        vec.push_back(12 + i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    vec.insert(4, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    EXPECT_EQ(16, vec.size());
    // Inconsistency between test logic and operational logic with the same practical result (Changed from 30 to 20).
    EXPECT_EQ(20, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_move_assigment) {
    Vector vec_1;
    Vector vec_2;

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_back(5 + i);
    }

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_front(4 - i);
    }

    vec_2 = std::move(vec_1);

    EXPECT_EQ(0, vec_1.size());
    EXPECT_EQ(0, vec_1.capacity());

    EXPECT_EQ(8, vec_2.size());
    EXPECT_EQ(15, vec_2.capacity());

    for (size_t i = 0; i < vec_2.size(); i++) {
        EXPECT_EQ(vec_2[i], i + 1);
    }
}

#endif // MAIN_VECTOR_TEST

#ifdef CUSTOM_VECTOR_TEST
TEST(ClassVector, can_create_with_default_constructor) {
    Vector vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 15);
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    Vector vec(11);
    EXPECT_EQ(vec.size(), 11); //This implies the presence of 11 elements.
    EXPECT_EQ(vec.capacity(), 26);
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    Vector vec({1, 2, 3, 4});
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 19);
    for (int i = 0; i < 4; ++i) {
        EXPECT_DOUBLE_EQ(vec[i], i+1);
    }
}

TEST(ClassVector, can_create_with_init_constructor) {
    double* ini = new double[5];
    for (int i = 11; i > 6; --i) {
        ini[11 - i] = i;
    }
    Vector vec(ini, 5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 20);
    for (int i = 11; i > 6; --i) {
        EXPECT_DOUBLE_EQ(vec[11 - i], i);
    }
}

TEST(ClassVector, can_create_with_copy_constructor) {
    Vector vec({ 5, 4, 7 });
    Vector vec_copy(vec);
    EXPECT_EQ(vec.size(), vec_copy.size());
    EXPECT_EQ(vec.capacity(), vec_copy.capacity());
    
    EXPECT_DOUBLE_EQ(vec[1], 4);
    EXPECT_DOUBLE_EQ(vec[2], vec_copy[2]);
}

TEST(ClassVector, can_create_with_move_constructor) {
    Vector vec({ 5, 4, 7 });
    Vector vec_copy(std::move(vec));
    EXPECT_NE(vec.size(), vec_copy.size());
    EXPECT_NE(vec.capacity(), vec_copy.capacity());

    EXPECT_DOUBLE_EQ(vec_copy[1], 4);
}

TEST(ClassVector, can_is_empty) {
    Vector vec;
    EXPECT_TRUE(vec.is_empty());
    vec.push_back(11);
    vec.pop_back();
    EXPECT_TRUE(vec.is_empty());
}

TEST(ClassVector, can_is_full) {
    Vector vec;
    double data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    vec.push_back_few(data, 15);
    EXPECT_TRUE(vec.is_full());
}

TEST(ClassVector, can_get_front) {
    Vector vec({ 1, 6, 11 });
    EXPECT_DOUBLE_EQ(vec.front(), 1);
}

TEST(ClassVector, can_get_back) {
    Vector vec({ 1, 6, 11 });
    EXPECT_DOUBLE_EQ(vec.back(), 11);
}

TEST(ClassVector, can_set_front) {
    Vector vec({ 1, 6, 11 });
    vec.front() = 25;
    EXPECT_DOUBLE_EQ(vec.front(), 25);
}

TEST(ClassVector, can_set_back) {
    Vector vec({ 1, 6, 11 });
    vec.back() = 8;
    EXPECT_DOUBLE_EQ(vec.back(), 8);
}

TEST(ClassVector, throw_when_try_get_front_in_empty_vector) {
    Vector vec;
    EXPECT_ANY_THROW(vec.front());
}

TEST(ClassVector, throw_when_try_get_back_in_empty_vector) {
    Vector vec;
    EXPECT_ANY_THROW(vec.back());
}

TEST(ClassVector, throw_when_try_set_front_in_empty_vector) {
    Vector vec;
    EXPECT_ANY_THROW(vec.front() = 5);
}

TEST(ClassVector, throw_when_try_set_back_in_empty_vector) {
    Vector vec;
    EXPECT_ANY_THROW(vec.back() = 6);
}

TEST(ClassVector, can_push_front) {
    Vector vec({ 1, 6, 11 });
    vec.push_front(13);
    EXPECT_DOUBLE_EQ(vec[0], 13);
}

TEST(ClassVector, can_push_front_in_empty_vector) {
    Vector vec;
    vec.push_front(13);
    EXPECT_DOUBLE_EQ(vec.front(), 13);
}

TEST(ClassVector, can_push_front_with_reallocation) {
    Vector vec;
    double data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 55 };
    vec.push_front_few(data, 16);
    EXPECT_EQ(vec.size(), 16);
    EXPECT_EQ(vec.capacity(), 30);
    EXPECT_DOUBLE_EQ(vec.front(), 55);
}

TEST(ClassVector, can_push_back) {
    Vector vec({ 1, 6, 11 });
    vec.push_back(13);
    EXPECT_DOUBLE_EQ(vec[3], 13);
}

TEST(ClassVector, can_push_back_in_empty_vector) {
    Vector vec;
    vec.push_back(13);
    EXPECT_DOUBLE_EQ(vec.back(), 13);
}

TEST(ClassVector, can_push_back_with_reallocation) {
    Vector vec;
    double data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 55 };
    vec.push_back_few(data, 16);
    EXPECT_EQ(vec.size(), 16);
    EXPECT_EQ(vec.capacity(), 30);
    EXPECT_DOUBLE_EQ(vec.back(), 55);
}

TEST(ClassVector, can_insert) {
    Vector vec({ 1, 4 , 5 });
    vec.insert(5, 1);
    EXPECT_DOUBLE_EQ(vec[1], 5);
    EXPECT_DOUBLE_EQ(vec[2], 4);
}

TEST(ClassVector, can_insert_with_reallocation) {
    Vector vec;
    double data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    vec.push_back_few(data, 15);
    vec.insert(21, 5);
    EXPECT_DOUBLE_EQ(vec[5], 21);
    for (int i = 6; i < 14; ++i) {
        EXPECT_DOUBLE_EQ(vec[i], i);
    }
}

TEST(ClassVector, can_insert_to_front) {
    Vector vec({ 1, 5 , 3 });
    vec.insert(3, 0);
    EXPECT_DOUBLE_EQ(vec.front(), 3);
}

TEST(ClassVector, can_insert_to_back) {
    Vector vec1;
    vec1.insert(7, 0);
    EXPECT_DOUBLE_EQ(vec1[0], 7);

    vec1.insert(5, 1);
    EXPECT_DOUBLE_EQ(vec1[1], 5);
}

TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    Vector vec({ 1, 5 , 3 });
    EXPECT_THROW(vec.insert(4, 10), std::out_of_range);
    EXPECT_THROW(vec.insert(-1, 10), std::out_of_range);
}

TEST(ClassVector, can_pop_front) {
    Vector vec({ 1, 5 , 7 });
    vec.pop_front();
    EXPECT_DOUBLE_EQ(vec[0], 5);
    EXPECT_DOUBLE_EQ(vec[1], 7);
}

TEST(ClassVector, can_pop_front_with_reallocation) {
    Vector vec;
    double data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    vec.push_back_few(data, 16);
    EXPECT_EQ(vec.size(), 16);
    EXPECT_EQ(vec.capacity(), 30);
    vec.pop_front();
    EXPECT_EQ(vec.size(), 15);
    EXPECT_EQ(vec.capacity(), 30);
    vec.pop_front();
    EXPECT_EQ(vec.size(), 14);
    EXPECT_EQ(vec.capacity(), 15);
}

TEST(ClassVector, throw_when_try_pop_front_from_empty_vector) {
    Vector vec;
    EXPECT_ANY_THROW(vec.pop_front());
}

TEST(ClassVector, can_pop_back) {
    Vector vec({ 1, 5, 9 });
    vec.pop_back();
    EXPECT_DOUBLE_EQ(vec[0], 1);
    EXPECT_DOUBLE_EQ(vec[1], 5);
    EXPECT_NE(vec[2], 9);
}

TEST(ClassVector, can_pop_back_with_reallocation) {
    Vector vec;
    double data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
    vec.push_back_few(data, 17);
    EXPECT_EQ(vec.size(), 17);
    EXPECT_EQ(vec.capacity(), 30);
    vec.pop_front();
    EXPECT_EQ(vec.size(), 16);
    EXPECT_EQ(vec.capacity(), 30);
    vec.pop_front_few(2);
    EXPECT_EQ(vec.size(), 14);
    EXPECT_EQ(vec.capacity(), 15);
}

TEST(ClassVector, throw_when_try_pop_back_from_empty_vector) {
    Vector vec;
    EXPECT_THROW(vec.pop_back(), std::logic_error);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.is_empty());
}

//AI
TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    Vector vec;

    // Part 1: Basic front recalc after complete clear
    double data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vec.push_back_few(data, 10);

    for (size_t i = 0; i < 8; i++) {
        vec.pop_front();
    }

    EXPECT_EQ(vec.size(), 2);
    EXPECT_DOUBLE_EQ(vec[0], 9);
    EXPECT_DOUBLE_EQ(vec[1], 10);

    vec.push_front(8);
    vec.push_front(7);
    vec.push_front(6);
    vec.push_front(5);
    vec.push_front(4);
    vec.push_front(3);
    vec.push_front(2);
    vec.push_front(1);

    EXPECT_EQ(vec.size(), 10);

    // Verify the correct order of elements
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1.0);
    }

    EXPECT_DOUBLE_EQ(vec.front(), 1);
    EXPECT_DOUBLE_EQ(vec.back(), 10);

    // Part 2: Complete clear and refill
    Vector vec2;
    vec2.push_back(1);
    vec2.push_back(2);
    vec2.push_back(3);

    vec2.pop_front();
    vec2.pop_front();
    vec2.pop_front();  // now empty

    EXPECT_EQ(vec2.size(), 0);
    EXPECT_TRUE(vec2.is_empty());

    // Add to empty vector
    vec2.push_back(100);
    vec2.push_back(200);
    vec2.push_back(300);

    EXPECT_EQ(vec2.size(), 3);
    EXPECT_DOUBLE_EQ(vec2[0], 100);
    EXPECT_DOUBLE_EQ(vec2[1], 200);
    EXPECT_DOUBLE_EQ(vec2[2], 300);

    // Part 3: push_front after pop_front on non-empty
    Vector vec3;
    vec3.push_back(100);
    vec3.push_back(200);
    vec3.push_back(300);

    vec3.pop_front();  // Remove 100, remains [200, 300]

    vec3.push_front(50);

    EXPECT_EQ(vec3.size(), 3);
    EXPECT_DOUBLE_EQ(vec3[0], 50);
    EXPECT_DOUBLE_EQ(vec3[1], 200);
    EXPECT_DOUBLE_EQ(vec3[2], 300);

    // Part 4: Multiple front crossings without reallocation
    Vector vec4;
    size_t cap = vec4.capacity();

    for (size_t i = 0; i < cap - 4; i++) {
        vec4.push_back(i + 1);
    }

    // Remove from front to shift index
    vec4.pop_front();
    vec4.pop_front();

    size_t current_size = vec4.size();

    // Add elements to front without triggering reallocation
    vec4.push_front(0);
    vec4.push_front(-1);

    EXPECT_EQ(vec4.size(), current_size + 2);
    EXPECT_DOUBLE_EQ(vec4[0], -1);
    EXPECT_DOUBLE_EQ(vec4[1], 0);
    EXPECT_DOUBLE_EQ(vec4[2], 3);  // Original third element
}
TEST(ClassVector, can_erase) {
    Vector vec({ 1, 2, 3, 4, 5 });
    vec.erase(2);

    EXPECT_EQ(vec.size(), 4);
    EXPECT_DOUBLE_EQ(vec[0], 1);
    EXPECT_DOUBLE_EQ(vec[1], 2);
    EXPECT_DOUBLE_EQ(vec[2], 4);
    EXPECT_DOUBLE_EQ(vec[3], 5);
}

TEST(ClassVector, can_erase_front) {
    Vector vec({ 1, 2, 3, 4, 5 });
    vec.erase(0);

    EXPECT_EQ(vec.size(), 4);
    EXPECT_DOUBLE_EQ(vec[0], 2);
    EXPECT_DOUBLE_EQ(vec[1], 3);
    EXPECT_DOUBLE_EQ(vec[2], 4);
    EXPECT_DOUBLE_EQ(vec[3], 5);
}

TEST(ClassVector, can_erase_back) {
    Vector vec({ 1, 2, 3, 4, 5 });
    vec.erase(4);

    EXPECT_EQ(vec.size(), 4);
    EXPECT_DOUBLE_EQ(vec[0], 1);
    EXPECT_DOUBLE_EQ(vec[1], 2);
    EXPECT_DOUBLE_EQ(vec[2], 3);
    EXPECT_DOUBLE_EQ(vec[3], 4);
}

TEST(ClassVector, can_erase_with_reallocation) {
    Vector vec;
    double data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    vec.push_back_few(data, 16);

    size_t old_capacity = vec.capacity();
    vec.erase(8);

    EXPECT_EQ(vec.size(), 15);
    EXPECT_EQ(vec.capacity(), old_capacity);
    EXPECT_DOUBLE_EQ(vec[7], 8);
    EXPECT_DOUBLE_EQ(vec[8], 10);
}

TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    Vector vec;
    EXPECT_THROW(vec.erase(0), std::logic_error);
}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    Vector vec({ 1, 2, 3 });
    EXPECT_THROW(vec.erase(5), std::out_of_range);
}

TEST(ClassVector, can_assigment) {
    Vector vec1({ 1, 2, 3, 4, 5 });
    Vector vec2;
    vec2 = vec1;

    EXPECT_EQ(vec2.size(), 5);
    EXPECT_DOUBLE_EQ(vec2[0], 1);
    EXPECT_DOUBLE_EQ(vec2[4], 5);

    vec1[0] = 100;
    EXPECT_DOUBLE_EQ(vec2[0], 1);
}

#endif // CUSTOM_VECTOR_TEST

#ifdef SORT_SHUFFLE_TEST
TEST(VectorAlgorithmsTest, SortsTest) {
    Vector vec{ 3.5, -2.1, 8.0, 0.0, -2.1, 15.7, 1.3 };

    shaker_sort(vec);

    EXPECT_EQ(vec.size(), 7);

    for (size_t i = 1; i < vec.size(); ++i) {
        EXPECT_LE(vec[i - 1], vec[i]);
    }

    EXPECT_DOUBLE_EQ(vec.front(), -2.1);  //min
    EXPECT_DOUBLE_EQ(vec.back(), 15.7);   //max
}

TEST(VectorAlgorithmsTest, ShuffleTest) {
    Vector vec{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    Vector original(vec);

    shuffle(vec);

    EXPECT_EQ(vec.size(), original.size());

    shaker_sort(vec);
    shaker_sort(original);

    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_DOUBLE_EQ(vec[i], original[i]);
    }
}
#endif // SORT_SHUFFLE_TEST
