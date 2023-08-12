#include "gtest/gtest.h"


#include "../src/Skill/Skill.h"
#include "../src/Skill/Command.h"
#include "../src/Unit.h"
#include "../src/Skill/DealDamageCommand.h"
#include "../src/Skill/ApplyBonusToCasterCommand.h"
#include "../src/Skill/ApplyStatusEffectCommand.h"


using namespace skills;

class TestCommand : public ::testing::Test
{
protected:
    void SetUp() override
    {
        
        caster->AddLifeComponent(AttributeType::HEALTH, "health", 100);
        caster->AddAttribute(AttributeType::DAMAGE, "damage", 10.0f);

        target->AddLifeComponent(AttributeType::HEALTH, "health", 100);
        target->AddAttribute(AttributeType::DAMAGE, "damage", 10.0f);
        
        // caster_weak = caster;
        // target_weak = target;
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }

   
    std::shared_ptr<Unit> caster = std::make_shared<Unit>("dummy caster");
    std::shared_ptr<Unit> target = std::make_shared<Unit>("dummy target");
    // std::weak_ptr<Unit> caster_weak;
    // std::weak_ptr<Unit> target_weak;
};

// Test that commands are correctly applied

// Test DealDamageCommand
// Deal 10 damage to dummy unit
TEST_F(TestCommand, TestDealDamageCommand)
{
    auto health_before = target->GetLifeComponentValue(AttributeType::HEALTH);
    auto command = std::make_unique<DealDamageCommand>(10.0f);
    command->Execute(caster, target);
    EXPECT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), health_before - 10.0f);
}

// Test ApplyBonusToCasterCommand
// Apply a bonus that boost damage by 10% to dummy unit
TEST_F(TestCommand, TestApplyBonusToCasterCommand)
{
    const float damage_before = caster->GetAttributeValue(AttributeType::DAMAGE);
    auto command = std::make_unique<ApplyBonusToCasterCommand>(std::make_shared<Bonus>(0.0f, 0.10f, AttributeType::DAMAGE, Bonus::Type::RAW));
    command->Execute(caster, target);
    EXPECT_EQ(caster->GetAttributeValue(AttributeType::DAMAGE), damage_before * 1.1f);
}

// Test ApplyStatusEffectCommand
// Apply a status effect that stuns the target
TEST_F(TestCommand, TestApplyStatusEffectCommand)
{
    auto command = std::make_unique<ApplyStatusEffectCommand>(std::make_unique<StatusEffect>("stun", 1, StatusEffect::Type::STUNNED));
    command->Execute(caster, target);
    EXPECT_EQ(target->HasStatusEffect(StatusEffect::Type::STUNNED), true);
}

