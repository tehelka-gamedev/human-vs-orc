#include "gtest/gtest.h"

#include "../src/Unit.h"

// Test a dummy unit taking damage and surviving
TEST(TestUnit, TestTakeDamage)
{
  // Create a unit with 100 health
  // Take 75 damage
  // Check that the unit has 25 health left
  Unit unit("dummy");
  unit.AddLifeComponent("health", 100);
  unit.TakeDamage(75);
  EXPECT_FLOAT_EQ(unit.GetLifeComponentValue("health"), 25);
  EXPECT_EQ(unit.IsAlive(), true);
}

// Test a dummy unit taking damage and dying
TEST(TestUnit, TestTakeDamageToDeath)
{
  // Create a unit with 100 health
  // Take 150 damage
  // Check that the unit has 0 health left
  Unit unit("dummy");
  unit.AddLifeComponent("health", 100);
  unit.TakeDamage(150);
  EXPECT_FLOAT_EQ(unit.GetLifeComponentValue("health"), 0);
  EXPECT_EQ(unit.IsAlive(), false);

  // Create another unit taking two hit to die
  Unit unit2("dummy");
  unit2.AddLifeComponent("health", 100);
  unit2.TakeDamage(50);
  EXPECT_FLOAT_EQ(unit2.GetLifeComponentValue("health"), 50);
  EXPECT_EQ(unit2.IsAlive(), true);
  unit2.TakeDamage(50);
  EXPECT_FLOAT_EQ(unit2.GetLifeComponentValue("health"), 0);
  EXPECT_EQ(unit2.IsAlive(), false);
}

// Test a unit taking damage then getting a bonus to health
TEST(TestUnit, TestTakeDamageThenBonus)
{
  // Create a unit with 100 health
  // Take 75 damage
  // Check that the unit has 25 health left
  // Give it a bonus of 50 health
  // Check that the unit has 75 health left
  Unit unit("dummy");
  unit.AddLifeComponent("health", 100);
  unit.TakeDamage(75);
  EXPECT_FLOAT_EQ(unit.GetLifeComponentValue("health"), 25);
  EXPECT_EQ(unit.IsAlive(), true);
  // TODO : should get rid of strings and use enums everywhere
  unit.AddBonus(std::make_shared<Bonus>(50, 0, BonusType::HEALTH));
  EXPECT_FLOAT_EQ(unit.GetLifeComponentValue("health"), 75);
  EXPECT_EQ(unit.IsAlive(), true);
}