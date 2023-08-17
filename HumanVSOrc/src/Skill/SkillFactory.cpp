#include "SkillFactory.h"

#include "ApplyBonusToCasterCommand.h"
#include "ApplyStatusEffectCommand.h"
#include "DealDamageCommand.h"
#include "../const.h"

#include "../Bonus.h"

namespace HumanVSOrc
{
    namespace skills
    {
        SkillFactory::~SkillFactory() = default;

        std::unique_ptr<Skill> SkillFactory::CreateChargeSkill()
        {
            int cooldown = static_cast<int>(GameConstants::Skills::Charge::COOLDOWN);
            float success_rate = static_cast<float>(GameConstants::Skills::Charge::SUCCESS_RATE) / 100.0f;
            int duration = static_cast<int>(GameConstants::Skills::Charge::DURATION);

            auto charge_bonus = std::make_shared<Bonus>(
                0.0f,
                1.0f,
                AttributeType::DAMAGE,
                Bonus::Type::FINAL,
                duration);

            std::unique_ptr<Skill> skill = std::make_unique<Skill>(
                "Charge",
                cooldown,
                success_rate,
                std::make_unique<ApplyBonusToCasterCommand>(charge_bonus)
            );

            return skill;
        }

        std::unique_ptr<Skill> SkillFactory::CreateStunSkill()
        {
            int cooldown = static_cast<int>(GameConstants::Skills::Stun::COOLDOWN);
            float success_rate = static_cast<float>(GameConstants::Skills::Stun::SUCCESS_RATE) / 100.0f;
            int duration = static_cast<int>(GameConstants::Skills::Stun::DURATION);


            std::unique_ptr<StatusEffect> stun_effect = std::make_unique<StatusEffect>(
                "Stunned",
                duration,
                StatusEffectType::STUNNED
            );
            std::unique_ptr<Command> apply_status_effect_command = std::make_unique<ApplyStatusEffectCommand>(std::move(stun_effect));
            std::unique_ptr<Skill> skill = std::make_unique<Skill>(
                "Stun",
                cooldown,
                success_rate,
                std::move(apply_status_effect_command)
            );

            return skill;
        }

        std::unique_ptr<Skill> SkillFactory::CreateBleedingStrikeSkill()
        {
            int duration = static_cast<int>(GameConstants::Skills::BleedingStrike::DURATION);
            int cooldown = static_cast<int>(GameConstants::Skills::BleedingStrike::COOLDOWN);
            float success_rate = static_cast<float>(GameConstants::Skills::BleedingStrike::SUCCESS_RATE) / 100.0f;
            float dmg_per_tick = static_cast<float>(GameConstants::Skills::BleedingStrike::DMG_PER_TICK);
            float instant_damage = static_cast<float>(GameConstants::Skills::BleedingStrike::INSTANT_DAMAGE);

            std::unique_ptr<Command> on_tick_command = std::make_unique<DealDamageCommand>(dmg_per_tick);
            std::unique_ptr<Command> on_apply_command = std::make_unique<DealDamageCommand>(instant_damage);
            
            std::unique_ptr<StatusEffect> bleeding_status = std::make_unique<StatusEffect>(
                "Bleeding",
                duration,
                StatusEffectType::BLEEDING
            );
            bleeding_status->SetOnUpdateCommand(std::move(on_tick_command))
                .SetOnApplyCommand(std::move(on_apply_command));
            
            std::unique_ptr<Command> apply_status_effect_command = std::make_unique<ApplyStatusEffectCommand>(
                std::move(bleeding_status));

            std::unique_ptr<Skill> skill = std::make_unique<Skill>(
                "Bleeding Strike",
                cooldown,
                success_rate,
                std::move(apply_status_effect_command)
            );

            return skill;
        }
    }
}
