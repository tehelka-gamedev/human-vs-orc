#include "gtest/gtest.h"
#include "../src/LifeSystem.h"
#include "../src/LifeComponent.h"


using namespace HumanVSOrc;

// Test LifeSystem::TakeDamage
TEST(TestLifeSystem, TestTakeDamage)
{
  // Create a LifeSystem with 2 LifeComponents
  // One "health" with 100 max value, the other "shield" with 50 max value
  // Take 75 damage
  // Check that the shield LifeComponent has 0 value
  // Check that the health LifeComponent has 75 value
  LifeSystem life_system;
  life_system.AddComponent(AttributeType::HEALTH, "health", 100);
  life_system.AddComponent(AttributeType::SHIELD, "shield", 50);
  EXPECT_FLOAT_EQ(life_system.GetComponentValue(AttributeType::SHIELD), 50);
  EXPECT_FLOAT_EQ(life_system.GetComponentValue(AttributeType::HEALTH), 100);
  life_system.TakeDamage(75);
  EXPECT_FLOAT_EQ(life_system.GetComponentValue(AttributeType::SHIELD), 0);
  EXPECT_FLOAT_EQ(life_system.GetComponentValue(AttributeType::HEALTH), 75);
  EXPECT_EQ(life_system.IsDepleted(), false);
}

// Test LifeSystem::TakeDamage to kill the unit
TEST(TestLifeSystem, TestTakeDamageToDeath)
{
  // Create a LifeSystem with 1 LifeComponents
  // "health" with 100 max value
  // Take 150 damage
  // Check that the health LifeComponent has 0 value
  LifeSystem life_system;
  life_system.AddComponent(AttributeType::HEALTH, "health", 100);
  life_system.TakeDamage(150);
  EXPECT_FLOAT_EQ(life_system.GetComponentValue(AttributeType::HEALTH), 0);
  EXPECT_EQ(life_system.IsDepleted(), true);
}


