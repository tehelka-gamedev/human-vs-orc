#include "gtest/gtest.h"


#include "../src/Skill/Skill.h"
#include "../src/Unit.h"
#include "../src/const.h"
#include "../src/Skill/SkillFactory.h"
#include "../src/Skill/Command.h"

using namespace HumanVSOrc;

using namespace skills;

class TestSkill : public ::testing::Test
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

// Test that skills are correctly initialized
TEST_F(TestSkill, TestInitialisation)
{
    constexpr int cd = 3; // cooldown
    // Create a skill with no command
    const Skill skill("Useless skill", cd, 0.5f, nullptr);

    // Check that the skill does not start on cooldown
    EXPECT_EQ(skill.IsReady(), true);
    EXPECT_EQ(skill.GetCooldown(), cd);
    EXPECT_EQ(skill.GetCurrentCooldown(), 0);

}

// Test the Charge skill
TEST_F(TestSkill, TestCharge)
{
    // Create a skill with no command
    auto skill = SkillFactory::CreateChargeSkill();
    int bonus_duration = static_cast<int>(GameConstants::Skills::Charge::DURATION);
    int cd = skill->GetCooldown(); // cooldown
    float damage = caster->GetAttributeValue(AttributeType::DAMAGE);
    skill->SetSuccessRate(1.0f);
    
    // Execute the skill
    skill->Execute(caster, target);

    // Check that the skill is on cooldown
    EXPECT_EQ(skill->IsReady(), false);
    EXPECT_EQ(skill->GetCooldown(), cd);
    EXPECT_EQ(skill->GetCurrentCooldown(), cd);

    // Check that the caster doubled his damage
    EXPECT_EQ(caster->GetAttributeValue(AttributeType::DAMAGE), damage * 2);


    
    // Tick the skill "cd-1" times (skill should still be on cooldown)
    // and check that the skill is still on cooldown
    for (int i = 0; i < cd - 1; ++i)
    {
        skill->Tick();
        EXPECT_EQ(skill->IsReady(), false);
        EXPECT_EQ(skill->GetCooldown(), cd);
        EXPECT_EQ(skill->GetCurrentCooldown(), cd - i - 1);
    }

    // Tick the caster bonus_duration-1 times
    // and check that the buff is still up
    for (int i = 0; i < bonus_duration - 1; ++i)
    {
        caster->TickAllBonuses();
        EXPECT_EQ(caster->GetAttributeValue(AttributeType::DAMAGE), damage * 2);
    }

    
    // Tick the skill and the caster one last time
    // and check that the skill is ready and that the caster's damage is back to normal
    skill->Tick();
    caster->TickAllBonuses();
    EXPECT_EQ(skill->IsReady(), true);
    EXPECT_EQ(skill->GetCooldown(), cd);
    EXPECT_EQ(skill->GetCurrentCooldown(), 0);
    EXPECT_EQ(caster->GetAttributeValue(AttributeType::DAMAGE), damage);
    
    
}


// Test Bleeding Strike skill
TEST_F(TestSkill, TestBleedingStrike)
{
    // Create a skill with no command
    auto skill = SkillFactory::CreateBleedingStrikeSkill();
    int status_duration = static_cast<int>(GameConstants::Skills::BleedingStrike::DURATION);
    int cd = skill->GetCooldown(); // cooldown
    float caster_damage = caster->GetAttributeValue(AttributeType::DAMAGE);
    float instant_damage = static_cast<float>(GameConstants::Skills::BleedingStrike::INSTANT_DAMAGE);
    float damage_per_tick = static_cast<float>(GameConstants::Skills::BleedingStrike::DMG_PER_TICK);
    
    
    float target_starting_health = target->GetLifeComponentValue(AttributeType::HEALTH);
    float target_current_health = target_starting_health;
    skill->SetSuccessRate(1.0f);

    std::cout << "aaa\n";
    std::cout << "caster : " << caster << std::endl;
    
    // Execute the skill
    skill->Execute(caster, target);

    // Check that the skill is on cooldown
    EXPECT_EQ(skill->IsReady(), false);
    EXPECT_EQ(skill->GetCooldown(), cd);
    EXPECT_EQ(skill->GetCurrentCooldown(), cd);

    // Check that the target has the bleeding status effect
    EXPECT_EQ(target->HasStatusEffect(StatusEffectType::BLEEDING), true);

    // Check that the target has lost the instant damage
    EXPECT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), target_current_health - instant_damage);
    target_current_health = target->GetLifeComponentValue(AttributeType::HEALTH);

    // Check that the caster's damage is not modified
    EXPECT_EQ(caster->GetAttributeValue(AttributeType::DAMAGE), caster_damage);

    
    // Tick the status effect "status_duration" times and check that the target has lost the damage_per_tick
    for (int i = 0; i < status_duration ; ++i)
    {
        EXPECT_EQ(target->HasStatusEffect(StatusEffectType::BLEEDING), true);
        target->TickAllStatusEffects();
        EXPECT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH), target_current_health - damage_per_tick);
        target_current_health = target->GetLifeComponentValue(AttributeType::HEALTH);
    }

    // Check that in total the target has lost the instant damage + status_duration * damage_per_tick
    EXPECT_EQ(target->GetLifeComponentValue(AttributeType::HEALTH),
              target_starting_health - instant_damage - static_cast<float>(status_duration) * damage_per_tick);
    // Check that the target has lost the bleeding status effect
    EXPECT_EQ(target->HasStatusEffect(StatusEffectType::BLEEDING), false);
    
}