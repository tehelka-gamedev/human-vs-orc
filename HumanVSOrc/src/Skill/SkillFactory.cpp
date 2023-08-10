#include "SkillFactory.h"

#include "ApplyBonusToCasterCommand.h"
#include "ApplyStatusEffectCommand.h"
#include "DealDamageCommand.h"
#include "Skill.h"
#include "StatusEffect.h"
#include "../const.h"

#include "../Bonus.h"

namespace Skills
{
    SkillFactory::~SkillFactory() = default;

    std::unique_ptr<Skill> SkillFactory::CreateChargeSkill()
    {
        std::unique_ptr<Skill> skill = std::make_unique<Skill>("Charge", static_cast<int>(GameConstants::Skills::Charge::COOLDOWN), static_cast<float>(GameConstants::Skills::Charge::SUCCESS_RATE)/100.0f, std::make_unique<ApplyBonusToCasterCommand>(
            std::make_shared<Bonus>(0.0f, 1.0f, AttributeType::DAMAGE, Bonus::Type::FINAL, static_cast<int>(GameConstants::Skills::Charge::DURATION))
        ));
        return skill;
    }

    std::unique_ptr<Skill> SkillFactory::CreateStunSkill()
    {
        std::unique_ptr<Skill> skill = std::make_unique<Skill>("Stun", static_cast<int>(GameConstants::Skills::Stun::COOLDOWN), static_cast<float>(GameConstants::Skills::Stun::SUCCESS_RATE)/100.0f,
        std::make_unique<ApplyStatusEffectCommand>(
            std::make_unique<StatusEffect>("Stunned", static_cast<int>(GameConstants::Skills::Stun::DURATION), StatusEffect::Type::STUNNED)
        ));
        
        return skill;
    }
}
