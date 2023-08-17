#include "gtest/gtest.h"

#include "../src/Unit.h"
#include "../src/Skill/Command.h"
#include "../src/Skill/DealDamageCommand.h"
#include "../src/Skill/Skill.h"

using namespace HumanVSOrc;

class TestUnit : public ::testing::Test
{
protected:
  void SetUp() override
  {

    // Add Health and damage to unit
    unit->AddLifeComponent(AttributeType::HEALTH, "health", 100);
    unit->AddAttribute(AttributeType::DAMAGE, "damage", 10.0f);
    
    // Add Health to target unit
    target->AddLifeComponent(AttributeType::HEALTH, "health", 100);
  }

  void TearDown() override
  {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }

  std::shared_ptr<Unit> unit = std::make_shared<Unit>("dummy unit");
  std::shared_ptr<Unit> target = std::make_shared<Unit>("dummy target");
};

// Test a dummy unit taking damage and surviving
TEST_F(TestUnit, TestTakeDamage)
{
  // Create a unit with 100 health
  // Take 75 damage
  // Check that the unit has 25 health left
  std::cout << "unit has " << unit->GetLifeComponentValue(AttributeType::HEALTH) << " health" << std::endl;
  unit->AddLifeComponent(AttributeType::HEALTH, "health", 100);
  unit->TakeDamage(75);
  EXPECT_FLOAT_EQ(unit->GetLifeComponentValue(AttributeType::HEALTH), 25);
  EXPECT_EQ(unit->IsAlive(), true);
}

// Test a dummy unit taking damage and dying
TEST_F(TestUnit, TestTakeDamageToDeath)
{
  // Create a unit with 100 health
  // Take 150 damage
  // Check that the unit has 0 health left
  std::cout << "unit has " << unit->GetLifeComponentValue(AttributeType::HEALTH) << " health" << std::endl;
  unit->AddLifeComponent(AttributeType::HEALTH, "health", 100);
  unit->TakeDamage(150);
  EXPECT_FLOAT_EQ(unit->GetLifeComponentValue(AttributeType::HEALTH), 0);
  EXPECT_EQ(unit->IsAlive(), false);

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
  // Check that the unit has 25 health left and 150 max health
  unit->AddLifeComponent(AttributeType::HEALTH,  "health", 100);
  unit->TakeDamage(75);
  EXPECT_FLOAT_EQ(unit->GetLifeComponentValue(AttributeType::HEALTH), 25);
  EXPECT_EQ(unit->IsAlive(), true);
  std::cout << "1" << std::endl;
  std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(50.0f, 0.0f, AttributeType::HEALTH, Bonus::Type::RAW);
  std::cout << "2" << std::endl;
  unit->AddBonus(bonus);
  std::cout << "3" << std::endl;
  EXPECT_FLOAT_EQ(unit->GetLifeComponentMaxValue(AttributeType::HEALTH), 150);
  EXPECT_FLOAT_EQ(unit->GetLifeComponentValue(AttributeType::HEALTH), 25);
  EXPECT_EQ(unit->IsAlive(), true);
}

// Test the unit attacking the target
TEST_F(TestUnit, TestAttack)
{
  float target_health = target->GetLifeComponentValue(AttributeType::HEALTH);
  float unit_damage = unit->GetAttributeValue(AttributeType::DAMAGE);
  
  unit->SetTarget(target);
  
  unit->Attack();
  EXPECT_FLOAT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), target_health - unit_damage);
  EXPECT_EQ(target->IsAlive(), true);
}

// Test the unit being stunned then trying to attack the target
// Resulting in no damage being done
TEST_F(TestUnit, TestStun)  
{
  float target_health = target->GetLifeComponentValue(AttributeType::HEALTH);
  float unit_damage = unit->GetAttributeValue(AttributeType::DAMAGE);
  
  unit->SetTarget(target);

  unit->AddStatusEffect(std::make_unique<StatusEffect>("Stun", 1, StatusEffectType::STUNNED));
  
  unit->Attack();
  EXPECT_FLOAT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), target_health);
  EXPECT_EQ(target->IsAlive(), true);
}

// Test the Unit::TickAllStatusEffects method
TEST_F(TestUnit, TestTickAllStatusEffects)
{
  unit->AddStatusEffect(std::make_unique<StatusEffect>("Stun", 1, StatusEffectType::STUNNED));
  unit->AddStatusEffect(std::make_unique<StatusEffect>("Bleed", 2, StatusEffectType::BLEEDING));


  EXPECT_EQ(unit->HasStatusEffect(StatusEffectType::STUNNED), true);
  EXPECT_EQ(unit->HasStatusEffect(StatusEffectType::BLEEDING), true);
  
  unit->TickAllStatusEffects();

  // Test the unit has no stun but still bleeding
  EXPECT_EQ(unit->HasStatusEffect(StatusEffectType::STUNNED), false);
  EXPECT_EQ(unit->HasStatusEffect(StatusEffectType::BLEEDING), true);

  // Tick again to remove the bleed
  unit->TickAllStatusEffects();
  EXPECT_EQ(unit->HasStatusEffect(StatusEffectType::STUNNED), false);
  EXPECT_EQ(unit->HasStatusEffect(StatusEffectType::BLEEDING), false);
  

  
}


// Test the Unit::CastAllSkills method
TEST_F(TestUnit, TestCastAllSkills)
{
  float target_health = target->GetLifeComponentValue(AttributeType::HEALTH);
  
  // Create a skill that does 10 damage
  unit->AddSkill(std::make_unique<skills::Skill>("Skill1", 5, 1.0f, std::make_unique<skills::DealDamageCommand>(10.0f)));

  // Create another skill that does 20 damage
  unit->AddSkill(std::make_unique<skills::Skill>("Skill2", 5, 1.0f, std::make_unique<skills::DealDamageCommand>(20.0f)));
  
  unit->SetTarget(target);

  // Cast all skills
  unit->CastAllSkills();

  // Check that the target has lost 10 + 20 = 30 health
  EXPECT_FLOAT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), target_health - 30);
  EXPECT_EQ(target->IsAlive(), true);


}

// Test adding a dependant attribute to a unit
TEST_F(TestUnit, TestAddDependantAttribute)
{
  // Add an attribute AGILITY to the unit with value 12
  unit->AddAttribute(AttributeType::AGILITY, "agility", 12);

  auto agility = unit->GetAttribute(AttributeType::AGILITY);

  std::vector<DependentAttribute::Dependency> dependencies{
    DependentAttribute::Dependency(agility, 1.0f, 5.0f)
  };
  // Add a dependant attribute CRITICAL_CHANCE with a base value 1.0f and gaining 1 for every 5 points of AGILITY
  unit->AddDependentAttribute(AttributeType::CRITICAL_CHANCE, "critical chance", 1.0f, dependencies);
  
  // Check that the unit has 1.0f + round(12 / 5) = 3.0f critical chance
  EXPECT_FLOAT_EQ(unit->GetAttributeValue(AttributeType::CRITICAL_CHANCE), 3.0f);

}