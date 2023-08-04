#include "gtest/gtest.h"

#include "../src/Unit.h"

class TestUnit : public ::testing::Test
{
protected:
  void SetUp() override
  {
    unit.SetName("dummy");
  }

  void TearDown() override
  {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }

  Unit unit{"dummy"};
};

// Test a dummy unit taking damage and surviving
TEST_F(TestUnit, TestTakeDamage)
{
  // Create a unit with 100 health
  // Take 75 damage
  // Check that the unit has 25 health left
  std::cout << "unit has " << unit.GetLifeComponentValue(AttributeType::HEALTH) << " health" << std::endl;
  unit.AddLifeComponent(AttributeType::HEALTH, "health", 100);
  unit.TakeDamage(75);
  EXPECT_FLOAT_EQ(unit.GetLifeComponentValue(AttributeType::HEALTH), 25);
  EXPECT_EQ(unit.IsAlive(), true);
}

// Test a dummy unit taking damage and dying
TEST_F(TestUnit, TestTakeDamageToDeath)
{
  // Create a unit with 100 health
  // Take 150 damage
  // Check that the unit has 0 health left
  std::cout << "unit has " << unit.GetLifeComponentValue(AttributeType::HEALTH) << " health" << std::endl;
  unit.AddLifeComponent(AttributeType::HEALTH, "health", 100);
  unit.TakeDamage(150);
  EXPECT_FLOAT_EQ(unit.GetLifeComponentValue(AttributeType::HEALTH), 0);
  EXPECT_EQ(unit.IsAlive(), false);

  // Create another unit taking two hit to die
  Unit unit2("dummy");
  unit2.AddLifeComponent(AttributeType::HEALTH,  "health", 100);
  unit2.TakeDamage(50);
  EXPECT_FLOAT_EQ(unit2.GetLifeComponentValue(AttributeType::HEALTH), 50);
  EXPECT_EQ(unit2.IsAlive(), true);
  unit2.TakeDamage(50);
  EXPECT_FLOAT_EQ(unit2.GetLifeComponentValue(AttributeType::HEALTH), 0);
  EXPECT_EQ(unit2.IsAlive(), false);
}

// Test a unit taking damage then getting a bonus to health
TEST_F(TestUnit, TestTakeDamageThenBonus)
{
  // Create a unit with 100 health
  // Take 75 damage
  // Check that the unit has 25 health left
  // Give it a bonus of 50 health
  // Check that the unit has 25 health left
  unit.AddLifeComponent(AttributeType::HEALTH,  "health", 100);
  unit.TakeDamage(75);
  EXPECT_FLOAT_EQ(unit.GetLifeComponentValue(AttributeType::HEALTH), 25);
  EXPECT_EQ(unit.IsAlive(), true);
  std::cout << "1" << std::endl;
  std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(50.0f, 0.0f, AttributeType::HEALTH, Bonus::Type::RAW);
  std::cout << "2" << std::endl;
  unit.AddBonus(bonus);
  std::cout << "3" << std::endl;
  EXPECT_FLOAT_EQ(unit.GetLifeComponentMaxValue(AttributeType::HEALTH), 150);
  EXPECT_FLOAT_EQ(unit.GetLifeComponentValue(AttributeType::HEALTH), 25);
  EXPECT_EQ(unit.IsAlive(), true);
}