#include "gtest/gtest.h"

#include "../src/Bonus.h"

// Test that attributes are correctly initialized
TEST(TestBonuses, TestInitialisation)
{
    Bonus bonus(10, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    EXPECT_FLOAT_EQ(bonus.GetValue(), 10);
    EXPECT_FLOAT_EQ(bonus.GetMultiplier(), 0);
    EXPECT_EQ(bonus.GetTargetAttribute(), AttributeType::HEALTH);
    EXPECT_EQ(bonus.GetTimeLeft(), 5);
    EXPECT_EQ(bonus.IsOver(), false);
}

// Test that attributes decay correctly
TEST(TestBonuses, TestDecay)
{
    Bonus bonus(10, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    bonus.Tick();
    EXPECT_EQ(bonus.GetTimeLeft(), 4);
    bonus.Tick();
    EXPECT_EQ(bonus.GetTimeLeft(), 3);
    bonus.Tick();
    EXPECT_EQ(bonus.GetTimeLeft(), 2);
    bonus.Tick();
    EXPECT_EQ(bonus.GetTimeLeft(), 1);
    bonus.Tick();
    EXPECT_EQ(bonus.GetTimeLeft(), 0);
    EXPECT_EQ(bonus.IsOver(), true);
    bonus.Tick();
    EXPECT_EQ(bonus.GetTimeLeft(), 0);
    EXPECT_EQ(bonus.IsOver(), true);
}