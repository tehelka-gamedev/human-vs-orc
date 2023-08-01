#include "gtest/gtest.h"

#include "../src/Attribute.h"
#include "../src/Bonus.h"

// Test that attributes are correctly initialized
TEST(TestAttributes, TestInitialisation)
{
    Attribute attribute(10);
    EXPECT_FLOAT_EQ(attribute.GetValue(), 10);
}

// Test that attributes raw bonuses are correctly applied
TEST(TestAttributes, TestRawBonus)
{
    Attribute attribute(10);
    attribute.AddRawBonus(std::make_shared<Bonus>(5, BonusType::HEALTH, 5));
    EXPECT_FLOAT_EQ(attribute.GetValue(), 15);
}

// Other test with raw bonuses with multiplier bonuses
TEST(TestAttributes, TestRawBonusWithMultiplier)
{
    Attribute attribute(10);
    attribute.AddRawBonus(std::make_shared<Bonus>(5, 0.5, BonusType::HEALTH, 5));
    // (10 + 5) * (1 + 0.5) = 22.5
    EXPECT_FLOAT_EQ(attribute.GetValue(), 22.5);
}

// Test that attributes final bonuses are correctly applied
TEST(TestAttributes, TestFinalBonus)
{
    Attribute attribute(10);
    attribute.AddFinalBonus(std::make_shared<Bonus>(5, BonusType::HEALTH, 5));
    EXPECT_FLOAT_EQ(attribute.GetValue(), 15);
}

// Other test with final bonuses with multiplier bonuses
TEST(TestAttributes, TestFinalBonusWithMultiplier)
{
    Attribute attribute(10);
    attribute.AddFinalBonus(std::make_shared<Bonus>(5, 0.5, BonusType::HEALTH, 5));
    // (10 + 5) * (1 + 0.5) = 22.5
    EXPECT_FLOAT_EQ(attribute.GetValue(), 22.5);
}

// Test that attributes raw bonuses are correctly removed
TEST(TestAttributes, TestRemoveRawBonus)
{
    Attribute attribute(10);
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5, BonusType::HEALTH, 5);
    attribute.AddRawBonus(bonus);
    EXPECT_FLOAT_EQ(attribute.GetValue(), 15);
    attribute.RemoveRawBonus(bonus);
    EXPECT_FLOAT_EQ(attribute.GetValue(), 10);
}

// Test that attributes final bonuses are correctly removed
TEST(TestAttributes, TestRemoveFinalBonus)
{
    Attribute attribute(10);
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5, BonusType::HEALTH, 5);
    attribute.AddFinalBonus(bonus);
    EXPECT_FLOAT_EQ(attribute.GetValue(), 15);
    attribute.RemoveFinalBonus(bonus);
    EXPECT_FLOAT_EQ(attribute.GetValue(), 10);
}

// Test with multiple raw and final bonuses
TEST(TestAttributes, TestMultipleBonuses)
{
    // Start with attribute value of 10
    // Apply +5 and +10% raw bonus
    // apply +3 and +5% final bonus
    Attribute attribute(10);
    std::shared_ptr<Bonus> bonus1 = std::make_shared<Bonus>(5, BonusType::HEALTH, 5);
    std::shared_ptr<Bonus> bonus2 = std::make_shared<Bonus>(0, 0.1, BonusType::HEALTH, 5);
    std::shared_ptr<Bonus> bonus3 = std::make_shared<Bonus>(3, BonusType::HEALTH, 5);
    std::shared_ptr<Bonus> bonus4 = std::make_shared<Bonus>(0, 0.05, BonusType::HEALTH, 5);

    // Apply all bonuses
    attribute.AddRawBonus(bonus1);
    attribute.AddRawBonus(bonus2);
    attribute.AddFinalBonus(bonus3);
    attribute.AddFinalBonus(bonus4);

    // Test the computed value
    // ((10 + 5) * (1 + 0.1) + 3) * (1 + 0.05) = 20.475
    EXPECT_FLOAT_EQ(attribute.GetValue(), 20.475);
}