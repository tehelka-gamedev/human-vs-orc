#include "gtest/gtest.h"


#include "../src/Unit.h"
#include "../src/StatusEffect.h"
#include "../src/Skill/DealDamageCommand.h"

using namespace HumanVSOrc;


class TestStatusEffect : public ::testing::Test
{
protected:
    void SetUp() override
    {
        
        caster->AddLifeComponent(AttributeType::HEALTH, "health", 100);
        caster->AddAttribute(AttributeType::DAMAGE, "damage", 10.0f);

        target->AddLifeComponent(AttributeType::HEALTH, "health", 100);
        target->AddAttribute(AttributeType::DAMAGE, "damage", 10.0f);
        
        caster->SetTarget(target);
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }

   
    std::shared_ptr<Unit> caster = std::make_shared<Unit>("dummy caster");
    std::shared_ptr<Unit> target = std::make_shared<Unit>("dummy target");

};

// Test that status effects are correctly initialized
TEST_F(TestStatusEffect, TestInitialisation)
{
    constexpr int duration = 3;
    // Create a status effect with no command
    const StatusEffect status_effect("Useless status effect", duration, StatusEffectType::STUNNED);

    // Check that the status effect does not start on cooldown
    EXPECT_EQ(status_effect.IsOver(), false);
    
}

// Test that status effects actions are correctly executed
// Bleeding, dealing 10 damage per tick for 5 ticks
TEST_F(TestStatusEffect, TestAction)
{
    // Target starts with 100 health
    float target_health = target->GetLifeComponentValue(AttributeType::HEALTH);
    
    constexpr float damage = 10.0f;
    constexpr int duration = 5;
    std::unique_ptr<StatusEffect> status_effect = std::make_unique<StatusEffect>("Useless status effect", duration, StatusEffectType::STUNNED);
    status_effect->SetOnUpdateCommand(std::make_unique<skills::DealDamageCommand>(damage))
        .SetCaster(caster)
        .SetTarget(target);
    // Create a status effect bleeding that deals 10 damage per tick for 5 ticks
    // And apply it to the target
    target->AddStatusEffect(std::move(status_effect));


    // Tick the status effect until it is over
    for(int i = 0; i < duration; ++i)
    {
        target->TickAllStatusEffects();
        target_health -= damage;
        EXPECT_FLOAT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), target_health);
    }
    
}


// Test that commands are executed correctly when the status effect is over
TEST_F(TestStatusEffect, TestOnRemoveCommand)
{
    // Target starts with 100 health
    float target_health = target->GetLifeComponentValue(AttributeType::HEALTH);
    
    constexpr float end_damage = 10.0f;
    constexpr int duration = 5;
    std::unique_ptr<StatusEffect> status_effect = std::make_unique<StatusEffect>("Useless status effect", duration, StatusEffectType::STUNNED);
    status_effect->SetOnRemoveCommand(std::make_unique<skills::DealDamageCommand>(end_damage))
        .SetCaster(caster)
        .SetTarget(target);
    // And apply it to the target
    target->AddStatusEffect(std::move(status_effect));

    // Tick the status effect just before it is over
    for(int i = 0; i < duration-1; ++i)
    {
        target->TickAllStatusEffects();
        EXPECT_FLOAT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), target_health); // health is not changing
    }

    // Check that the on remove command is executed in the last tick
    target->TickAllStatusEffects();
    EXPECT_FLOAT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), target_health - end_damage);
}