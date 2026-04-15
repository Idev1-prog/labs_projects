#include "pch.h"
#include "Cherecters.h"

TEST(WarriorInit, DefaultConstructor) {
    Warrior w;
    EXPECT_EQ(w.name(), "Warrior");
    EXPECT_EQ(w.health(), 150);
    EXPECT_EQ(w.power(), 15);
    EXPECT_EQ(w.get_armor(), 5);
}

TEST(WarriorInit, ParamConstructor) {
    Warrior w("Conan", 200, 25, 10);
    EXPECT_EQ(w.name(), "Conan");
    EXPECT_EQ(w.health(), 200);
    EXPECT_EQ(w.power(), 25);
    EXPECT_EQ(w.get_armor(), 10);
}

TEST(WarriorInit, CopyConstructor) {
    Warrior original("Thor", 180, 30, 12);
    Warrior copy(original);
    EXPECT_EQ(copy.name(), "Thor");
    EXPECT_EQ(copy.health(), 180);
    EXPECT_EQ(copy.power(), 30);
    EXPECT_EQ(copy.get_armor(), 12);
}

TEST(WarriorCombat, AttakedReducesHealthWithArmor) {
    Warrior w("Tank", 100, 10, 5);
    Warrior dummy("Dummy", 100, 10, 0);

    w.attaked(dummy, 12);
    EXPECT_EQ(w.health(), 93);

    w.attaked(dummy, 3);
    EXPECT_EQ(w.health(), 93);
}

TEST(WarriorCombat, AttackDamageInRange) {
    Warrior attacker("Attacker", 100, 15, 0);
    Warrior defender("Defender", 100, 10, 2);

    int hp_before = defender.health();
    attacker.attack(defender);
    int hp_after = defender.health();

    int damage_dealt = hp_before - hp_after;

    EXPECT_GE(damage_dealt, 14);
    EXPECT_LE(damage_dealt, 23);
}

TEST(WarriorCombat, AttackerHealthUnchanged) {
    Warrior attacker("Attacker", 100, 15, 5);
    Warrior defender("Defender", 100, 10, 2);

    int hp_before = attacker.health();
    attacker.attack(defender);

    EXPECT_EQ(attacker.health(), hp_before);
}

TEST(WarriorCombat, IsAliveWorks) {
    Warrior w("Test", 10, 10, 0);
    Warrior dummy("Dummy", 10, 10, 0);

    EXPECT_TRUE(w.is_alive());

    w.attaked(dummy, 100);
    EXPECT_FALSE(w.is_alive());
}