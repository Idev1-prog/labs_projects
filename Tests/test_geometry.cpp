#include "pch.h"
#include "geometry.h"
/*
TEST(DistanceTest, example_test) {
    Circle c1 = { {3, 2}, 3 }, c2 = { {4, 1}, 3 };
    double dist = calculate_points_distance(c1, c2);
    EXPECT_NEAR(dist, 1.414, 1e-3);
}

TEST(NotRelatedTest, example_test) {
    Circle c1 = { {0, 0}, 2 };
    Circle c2 = { {10, 10}, 3 };
    EXPECT_EQ(not_related_check(c1, c2), NOT_RELATED);
}

TEST(MatchTest, example_test) {
    Circle c1 = { {3, 4}, 5 };
    Circle c2 = { {3, 4}, 5 };
    EXPECT_EQ(match_check(c1, c2), MATCH);
}

TEST(ConsernTest, example_test) {
    Circle c1 = { {0, 0}, 3 };
    Circle c2 = { {3, 4}, 2 };
    EXPECT_EQ(consern_check(c1, c2), CONSERN);
}

TEST(InsideTest, one_in_two) {
    Circle c1 = { {0, 0}, 1 };
    Circle c2 = { {1, 1}, 6 };
    EXPECT_EQ(inside_check(c1, c2), INSIDE);
}

TEST(InsideTest, two_in_one) {
    Circle c1 = { {1, 1}, 4 };
    Circle c2 = { {1, 2}, 2 };
    EXPECT_EQ(inside_check(c1, c2), INSIDE);
}

TEST(IntersectTest, intersect) {
    Circle c1 = { {0, 0}, 10 };
    Circle c2 = { {8, 0}, 3 };
    EXPECT_EQ(intersect_check(c1, c2), INTERSECT);
}

TEST(IntersectTest, not_intersect) {
    Circle c1 = { {0, 0}, 10 };
    Circle c2 = { {2, 2}, 3 };
    EXPECT_EQ(intersect_check(c1, c2), NO_INFO);
}



//AI TESTS
static bool has_status(Posision_status* results, Posision_status status) {
    for (int i = 0; i < 5; i++) {
        if (results[i] == status) return true;
    }
    return false;
}

static int count_statuses(Posision_status* results) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (results[i] != NO_INFO) count++;
    }
    return count;
}

// Test 1: Checking all basic functions
TEST(debug_plus, BasicFunctionsTest) {
    Circle c1 = { {0, 0}, 5 };
    Circle c2 = { {0, 0}, 5 };

    EXPECT_EQ(match_check(c1, c2), MATCH);
    EXPECT_EQ(inside_check(c1, c2), INSIDE);

    double d = calculate_points_distance(c1, c2);
    EXPECT_DOUBLE_EQ(d, 0.0);
}

// Test 2: Matching circles (3 statuses)
TEST(debug_plus, MatchingCircles_ThreeStatuses) {
    Circle c1 = { {0, 0}, 10 };
    Circle c2 = { {0, 0}, 10 };

    Posision_status* results = code_status(c1, c2);

    // Should have 3 statuses
    EXPECT_EQ(count_statuses(results), 3);

    // Check presence of each status
    EXPECT_TRUE(has_status(results, MATCH));
    EXPECT_TRUE(has_status(results, INSIDE));
    EXPECT_TRUE(has_status(results, CONSERN));

    // Check absence of other statuses
    EXPECT_FALSE(has_status(results, INTERSECT));
    EXPECT_FALSE(has_status(results, NOT_RELATED));
}

// Test 3: Internal tangency (2 statuses)
TEST(debug_plus, InternalTangency_TwoStatuses) {
    // Horizontal internal tangency
    Circle big = { {0, 0}, 10 };
    Circle small = { {5, 0}, 5 };

    Posision_status* results = code_status(big, small);

    EXPECT_EQ(count_statuses(results), 2);
    EXPECT_TRUE(has_status(results, INSIDE));
    EXPECT_TRUE(has_status(results, CONSERN));
    EXPECT_FALSE(has_status(results, MATCH));
}

// Test 4: Internal tangency - vertical
TEST(debug_plus, InternalTangency_Vertical) {
    Circle big = { {0, 0}, 12 };
    Circle small = { {0, 7}, 5 };  // 7 + 5 = 12

    Posision_status* results = code_status(big, small);

    EXPECT_EQ(count_statuses(results), 2);
    EXPECT_TRUE(has_status(results, INSIDE));
    EXPECT_TRUE(has_status(results, CONSERN));
}

// Test 5: Internal tangency - diagonal (3-4-5 triangle)
TEST(debug_plus, InternalTangency_Diagonal) {
    Circle big = { {0, 0}, 10 };
    Circle small = { {3, 4}, 5 };  // d = 5, 5 + 5 = 10

    Posision_status* results = code_status(big, small);

    EXPECT_EQ(count_statuses(results), 2);
    EXPECT_TRUE(has_status(results, INSIDE));
    EXPECT_TRUE(has_status(results, CONSERN));
}

// Test 6: External tangency (1 status)
TEST(debug_plus, ExternalTangency_OneStatus) {
    Circle c1 = { {0, 0}, 5 };
    Circle c2 = { {10, 0}, 5 };

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, CONSERN));
    EXPECT_FALSE(has_status(results, INSIDE));
}

// Test 7: One inside the other (without tangency)
TEST(debug_plus, InsideWithoutTangency) {
    Circle big = { {0, 0}, 10 };
    Circle small = { {2, 3}, 4 };  // d + 4 = 7.21 < 10

    Posision_status* results = code_status(big, small);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, INSIDE));
    EXPECT_FALSE(has_status(results, CONSERN));
}

// Test 8: Intersection (1 status)
TEST(debug_plus, Intersection_OneStatus) {
    Circle c1 = { {0, 0}, 5 };
    Circle c2 = { {7, 0}, 5 };  // d = 7, between 0 and 10

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, INTERSECT));
}

// Test 9: Not related (1 status)
TEST(debug_plus, NotRelated_OneStatus) {
    Circle c1 = { {0, 0}, 5 };
    Circle c2 = { {15, 0}, 5 };  // d = 15 > 10

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, NOT_RELATED));
}

// Test 10: Concentric circles (1 status - INSIDE)
TEST(debug_plus, ConcentricCircles) {
    Circle big = { {0, 0}, 10 };
    Circle small = { {0, 0}, 5 };

    Posision_status* results = code_status(big, small);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, INSIDE));
    EXPECT_FALSE(has_status(results, CONSERN));  // Don't touch
}

// Test 11: Very small inside huge
TEST(debug_plus, TinyInsideHuge) {
    Circle big = { {0, 0}, 100 };
    Circle small = { {30, 40}, 20 };  // d = 50, 50+20=70 < 100

    Posision_status* results = code_status(big, small);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, INSIDE));
}

// Test 12: Almost tangency (should be INSIDE, not CONSERN)
TEST(debug_plus, AlmostTangency_InsideOnly) {
    Circle big = { {0, 0}, 10 };
    Circle small = { {4.9, 0}, 5 };  // 4.9 + 5 = 9.9 < 10

    Posision_status* results = code_status(big, small);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, INSIDE));
    EXPECT_FALSE(has_status(results, CONSERN));
}

// Test 13: Almost intersection (should be INTERSECT)
TEST(debug_plus, AlmostIntersection) {
    Circle c1 = { {0, 0}, 5 };
    Circle c2 = { {9.9, 0}, 5 };  // 9.9 < 10, but > 0

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, INTERSECT));
}

// Test 14: Equal radii, centers close (intersection)
TEST(debug_plus, EqualRadii_Intersection) {
    Circle c1 = { {0, 0}, 5 };
    Circle c2 = { {6, 0}, 5 };  // d = 6, between 0 and 10

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, INTERSECT));
}

// Test 15: Equal radii, external tangency
TEST(debug_plus, EqualRadii_Tangency) {
    Circle c1 = { {0, 0}, 5 };
    Circle c2 = { {10, 0}, 5 };  // d = 10 = 5+5

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, CONSERN));
}

// Test 16: Different radii, external tangency
TEST(debug_plus, DifferentRadii_Tangency) {
    Circle c1 = { {0, 0}, 3 };
    Circle c2 = { {7, 0}, 4 };  // d = 7 = 3+4

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, CONSERN));
}

// Test 17: Very small circle far away
TEST(debug_plus, TinyCircleFarAway) {
    Circle c1 = { {0, 0}, 100 };
    Circle c2 = { {200, 0}, 1 };  // d = 200 > 101

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, NOT_RELATED));
}

// Test 18: Negative coordinates
TEST(debug_plus, NegativeCoordinates) {
    Circle c1 = { {-5, -5}, 5 };
    Circle c2 = { {5, 5}, 5 };  // d = 14.14 > 10

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 1);
    EXPECT_TRUE(has_status(results, NOT_RELATED));
}

// Test 19: Zero radii (points)
TEST(debug_plus, ZeroRadii_Points) {
    Circle c1 = { {0, 0}, 0 };
    Circle c2 = { {0, 0}, 0 };

    Posision_status* results = code_status(c1, c2);

    EXPECT_EQ(count_statuses(results), 3);  // MATCH, INSIDE, CONSERN
    EXPECT_TRUE(has_status(results, MATCH));
    EXPECT_TRUE(has_status(results, INSIDE));
    EXPECT_TRUE(has_status(results, CONSERN));
}

// Test 20: Circle touches another internally and externally? (impossible)
TEST(debug_plus, Impossible_InternalAndExternalTangency) {
    Circle c1 = { {0, 0}, 10 };
    Circle c2 = { {0, 0}, 10 };  // Only coincidence gives "tangency everywhere"

    Posision_status* results = code_status(c1, c2);

    // This is a special case - matching circles
    EXPECT_EQ(count_statuses(results), 3);
}

// Test 21: Stress test - many random values
TEST(debug_plus, StressTest) {
    for (int x = -10; x <= 10; x += 5) {
        for (int y = -10; y <= 10; y += 5) {
            Circle c1 = { {0, 0}, 10 };
            Circle c2 = { {x, y}, 5 };

            Posision_status* results = code_status(c1, c2);
            int count = count_statuses(results);

            // Number of statuses should be from 1 to 3
            EXPECT_GE(count, 1);
            EXPECT_LE(count, 3);
        }
    }
}

// Test 22: Checking boundary values
TEST(debug_plus, BoundaryValues) {
    // INSIDE + CONSERN
    Circle c1 = { {0, 0}, 10 };
    Circle c2 = { {3, 4}, 5 };  // d=5, 5+5=10

    Posision_status* results1 = code_status(c1, c2);
    EXPECT_EQ(count_statuses(results1), 2);

    // Only INSIDE
    Circle c3 = { {3, 4}, 4 };  // d=5, 5+4=9 < 10
    Posision_status* results2 = code_status(c1, c3);
    EXPECT_EQ(count_statuses(results2), 1);
    EXPECT_TRUE(has_status(results2, INSIDE));

    // Only CONSERN (external)
    Circle c4 = { {0, 0}, 5 };
    Circle c5 = { {10, 0}, 5 };
    Posision_status* results3 = code_status(c4, c5);
    EXPECT_EQ(count_statuses(results3), 1);
    EXPECT_TRUE(has_status(results3, CONSERN));
}

// Test 23: Checking all functions separately
TEST(debug_plus, IndividualFunctionTest) {
    Circle c1 = { {0, 0}, 10 };
    Circle c2 = { {5, 0}, 5 };  // Internal tangency

    EXPECT_EQ(not_related_check(c1, c2), NO_INFO);
    EXPECT_EQ(match_check(c1, c2), NO_INFO);
    EXPECT_EQ(consern_check(c1, c2), CONSERN);
    EXPECT_EQ(inside_check(c1, c2), INSIDE);
    EXPECT_EQ(intersect_check(c1, c2), NO_INFO);
}

// Test 24: Checking distance calculation
TEST(debug_plus, DistanceCalculationTest) {
    Circle c1 = { {0, 0}, 1 };
    Circle c2 = { {3, 4}, 1 };

    double dist = calculate_points_distance(c1, c2);
    EXPECT_DOUBLE_EQ(dist, 5.0);

    Circle c3 = { {-2, -3}, 1 };
    Circle c4 = { {-2, -3}, 1 };
    dist = calculate_points_distance(c3, c4);
    EXPECT_DOUBLE_EQ(dist, 0.0);
}

// Test 25: Comprehensive test for all cases
TEST(debug_plus, ComprehensiveTest) {
    struct TestCase {
        Circle c1;
        Circle c2;
        int expected_count;
        bool expect_match;
        bool expect_consern;
        bool expect_inside;
        bool expect_intersect;
        bool expect_not_related;
    };

    TestCase tests[] = {
        // Matching
        {{{0,0},10}, {{0,0},10}, 3, true, true, true, false, false},
        // Internal tangency
        {{{0,0},10}, {{5,0},5}, 2, false, true, true, false, false},
        // External tangency
        {{{0,0},5}, {{10,0},5}, 1, false, true, false, false, false},
        // Inside without tangency
        {{{0,0},10}, {{2,3},4}, 1, false, false, true, false, false},
        // Intersection
        {{{0,0},5}, {{7,0},5}, 1, false, false, false, true, false},
        // Not related
        {{{0,0},5}, {{15,0},5}, 1, false, false, false, false, true},
        // Concentric
        {{{0,0},10}, {{0,0},5}, 1, false, false, true, false, false},
        // Zero radii
        {{{0,0},0}, {{0,0},0}, 3, true, true, true, false, false},
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_tests; i++) {
        TestCase& t = tests[i];
        Posision_status* results = code_status(t.c1, t.c2);

        EXPECT_EQ(count_statuses(results), t.expected_count) << "Failed on test case " << i;
        EXPECT_EQ(has_status(results, MATCH), t.expect_match) << "MATCH failed on test " << i;
        EXPECT_EQ(has_status(results, CONSERN), t.expect_consern) << "CONSERN failed on test " << i;
        EXPECT_EQ(has_status(results, INSIDE), t.expect_inside) << "INSIDE failed on test " << i;
        EXPECT_EQ(has_status(results, INTERSECT), t.expect_intersect) << "INTERSECT failed on test " << i;
        EXPECT_EQ(has_status(results, NOT_RELATED), t.expect_not_related) << "NOT_RELATED failed on test " << i;
    }
}

*/