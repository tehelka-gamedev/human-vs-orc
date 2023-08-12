#include "gtest/gtest.h"

#include "../src/Attribute.h"
#include "../src/Bonus.h"

using namespace HumanVSOrc;

class TestAttributes : public ::testing::Test
{
protected:
    void SetUp() override
    {
        attribute = std::make_unique<Attribute>(AttributeType::HEALTH, "Health", 10.0f);
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
    
    // Attribute to test on
    std::unique_ptr<Attribute> attribute;
};



// Test that attributes are correctly initialized
TEST_F(TestAttributes, TestInitialisation)
{
    EXPECT_FLOAT_EQ(attribute->GetValue(), 10);
}



// Test that attributes raw bonuses are correctly applied
TEST_F(TestAttributes, TestRawBonus)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    attribute->AddBonus(bonus);
    EXPECT_FLOAT_EQ(attribute->GetValue(), 15);
}

// Other test with raw bonuses with multiplier bonuses
TEST_F(TestAttributes, TestRawBonusWithMultiplier)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, 0.5f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    attribute->AddBonus(bonus);
    // (10 + 5) * (1 + 0.5) = 22.5
    EXPECT_FLOAT_EQ(attribute->GetValue(), 22.5);
}

// Test that attributes final bonuses are correctly applied
TEST_F(TestAttributes, TestFinalBonus)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);
    attribute->AddBonus(bonus);
    EXPECT_FLOAT_EQ(attribute->GetValue(), 15);
}

// Other test with final bonuses with multiplier bonuses
TEST_F(TestAttributes, TestFinalBonusWithMultiplier)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, 0.5f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);
    attribute->AddBonus(bonus);
    // (10 + 5) * (1 + 0.5) = 22.5
    EXPECT_FLOAT_EQ(attribute->GetValue(), 22.5);
}

// Test that attributes raw bonuses are correctly removed
TEST_F(TestAttributes, TestRemoveRawBonus)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    attribute->AddBonus(bonus);
    EXPECT_FLOAT_EQ(attribute->GetValue(), 15);
    attribute->RemoveBonus(bonus);
    EXPECT_FLOAT_EQ(attribute->GetValue(), 10);
}

// Test that attributes final bonuses are correctly removed
TEST_F(TestAttributes, TestRemoveFinalBonus)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);
    attribute->AddBonus(bonus);
    EXPECT_FLOAT_EQ(attribute->GetValue(), 15);
    attribute->RemoveBonus(bonus);
    EXPECT_FLOAT_EQ(attribute->GetValue(), 10);
}

// Test with multiple raw and final bonuses
TEST_F(TestAttributes, TestMultipleBonuses)
{
    // Start with attribute value of 10
    // Apply +5 and +10% raw bonus
    // apply +3 and +5% final bonus
    attribute->SetBaseValue(10);
    std::shared_ptr<Bonus> bonus1 = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    std::shared_ptr<Bonus> bonus2 = std::make_shared<Bonus>(0.0f, 0.1f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    std::shared_ptr<Bonus> bonus3 = std::make_shared<Bonus>(3.0f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);
    std::shared_ptr<Bonus> bonus4 = std::make_shared<Bonus>(0.0f, 0.05f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);

    // Apply all bonuses
    attribute->AddBonus(bonus1);
    attribute->AddBonus(bonus2);
    attribute->AddBonus(bonus3);
    attribute->AddBonus(bonus4);

    // Test the computed value
    // ((10 + 5) * (1 + 0.1) + 3) * (1 + 0.05) = 20.475
    EXPECT_FLOAT_EQ(attribute->GetValue(), 20.475f);
}