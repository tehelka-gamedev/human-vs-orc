#include "gtest/gtest.h"

#include "../src/Attribute.h"
#include "../src/DependentAttribute.h"
#include "../src/AttributeGauge.h"
#include "../src/Bonus.h"

using namespace HumanVSOrc;

class TestAttributes : public ::testing::Test
{
protected:
    void SetUp() override
    {
        damage = std::make_unique<Attribute>(AttributeType::HEALTH, "Health", 10.0f);

        // Define a dependent attribute that depends on the agility
        // It will gain +1 for each 5 agility point
        agility = std::make_shared<Attribute>(AttributeType::AGILITY, "Agility", 10.0f);
        critical_chance = std::make_unique<DependentAttribute>(AttributeType::CRITICAL_CHANCE, "Critical chance", 1.0f, std::vector{ DependentAttribute::Dependency(agility, 1.0f, 5.0f) });

        // Define a health AttributeGauge
        health = std::make_shared<AttributeGauge>(AttributeType::HEALTH, "Health", 100.0f);
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
    
    // Attributes to test on
    std::unique_ptr<Attribute> damage;

    // Dependency attributes testing
    std::shared_ptr<Attribute> agility;
    std::unique_ptr<DependentAttribute> critical_chance;

    // AttributeGauge testing
    std::shared_ptr<AttributeGauge> health;
};



// Test that attributes are correctly initialized
TEST_F(TestAttributes, TestInitialisation)
{
    EXPECT_FLOAT_EQ(damage->GetValue(), 10);
}



// Test that attributes raw bonuses are correctly applied
TEST_F(TestAttributes, TestRawBonus)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    damage->AddBonus(bonus);
    EXPECT_FLOAT_EQ(damage->GetValue(), 15);
}

// Other test with raw bonuses with multiplier bonuses
TEST_F(TestAttributes, TestRawBonusWithMultiplier)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, 0.5f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    damage->AddBonus(bonus);
    // (10 + 5) * (1 + 0.5) = 22.5
    EXPECT_FLOAT_EQ(damage->GetValue(), 22.5);
}

// Test that attributes final bonuses are correctly applied
TEST_F(TestAttributes, TestFinalBonus)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);
    damage->AddBonus(bonus);
    EXPECT_FLOAT_EQ(damage->GetValue(), 15);
}

// Other test with final bonuses with multiplier bonuses
TEST_F(TestAttributes, TestFinalBonusWithMultiplier)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, 0.5f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);
    damage->AddBonus(bonus);
    // (10 + 5) * (1 + 0.5) = 22.5
    EXPECT_FLOAT_EQ(damage->GetValue(), 22.5);
}

// Test that attributes raw bonuses are correctly removed
TEST_F(TestAttributes, TestRemoveRawBonus)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    damage->AddBonus(bonus);
    EXPECT_FLOAT_EQ(damage->GetValue(), 15);
    damage->RemoveBonus(bonus);
    EXPECT_FLOAT_EQ(damage->GetValue(), 10);
}

// Test that attributes final bonuses are correctly removed
TEST_F(TestAttributes, TestRemoveFinalBonus)
{
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);
    damage->AddBonus(bonus);
    EXPECT_FLOAT_EQ(damage->GetValue(), 15);
    damage->RemoveBonus(bonus);
    EXPECT_FLOAT_EQ(damage->GetValue(), 10);
}

// Test with multiple raw and final bonuses
TEST_F(TestAttributes, TestMultipleBonuses)
{
    // Start with attribute value of 10
    // Apply +5 and +10% raw bonus
    // apply +3 and +5% final bonus
    damage->SetBaseValue(10);
    std::shared_ptr<Bonus> bonus1 = std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    std::shared_ptr<Bonus> bonus2 = std::make_shared<Bonus>(0.0f, 0.1f, AttributeType::HEALTH, Bonus::Type::RAW, 5);
    std::shared_ptr<Bonus> bonus3 = std::make_shared<Bonus>(3.0f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);
    std::shared_ptr<Bonus> bonus4 = std::make_shared<Bonus>(0.0f, 0.05f, AttributeType::HEALTH, Bonus::Type::FINAL, 5);

    // Apply all bonuses
    damage->AddBonus(bonus1);
    damage->AddBonus(bonus2);
    damage->AddBonus(bonus3);
    damage->AddBonus(bonus4);

    // Test the computed value
    // ((10 + 5) * (1 + 0.1) + 3) * (1 + 0.05) = 20.475
    EXPECT_FLOAT_EQ(damage->GetValue(), 20.475f);
}

// Test dependent attribute
// Test the final value is correctly computed with no bonus
TEST_F(TestAttributes, TestDependentAttribute)
{
    // Start with 10 agility and 1 critical chance
    agility->SetBaseValue(10.0f);
    critical_chance->SetBaseValue(1.0f);

    std::cout << "now\n";
    EXPECT_FLOAT_EQ(agility->GetValue(), 10.0f);
    

    // Test the computed value
    // 1 + 10 / 5 = 1 + 2 = 3
    EXPECT_FLOAT_EQ(critical_chance->GetValue(), 3.0f);
}

// Test that the final value is correctly computed when the attribute we depend on is modified
TEST_F(TestAttributes, TestDependentAttributeWithBonus)
{
    // Start with 10 agility and 1 critical chance
    agility->SetBaseValue(10.0f);
    critical_chance->SetBaseValue(1.0f);

    // Test the computed value
    // 1 + 10 / 5 = 1 + 2 = 3
    EXPECT_FLOAT_EQ(critical_chance->GetValue(), 3.0f);
    
    // Apply a bonus of +5 agility
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(5.0f, AttributeType::AGILITY, Bonus::Type::RAW, 5);
    agility->AddBonus(bonus);

    // Test the computed value
    // 1 + (10 + 5) / 5 = 1 + 3 = 4
    EXPECT_FLOAT_EQ(critical_chance->GetValue(), 4.0f);

    // Remove the bonus
    agility->RemoveBonus(bonus);

    // Test the computed value
    // 1 + 10 / 5 = 1 + 2 = 3
    EXPECT_FLOAT_EQ(critical_chance->GetValue(), 3.0f);
}

// Test AttributeGauge health
TEST_F(TestAttributes, TestHealthGauge)
{
    // Test that it is full at the beginning
    EXPECT_EQ(health->IsFull(), true);

    // Decrease the health by twice the max value
    const float max_value = health->GetMaxValue();
    health->DecreaseCurrentValue(max_value * 2);

    // Test that it is depleted, and exactly zero
    EXPECT_EQ(health->IsDepleted(), true);
    EXPECT_FLOAT_EQ(health->GetCurrentValue(), 0.0f);

    // Increase the health by twice max value (overheal)
    health->IncreaseCurrentValue(max_value * 2);

    // Test that it is full, and exactly max value
    EXPECT_EQ(health->IsFull(), true);
    EXPECT_FLOAT_EQ(health->GetCurrentValue(), max_value);
    
}