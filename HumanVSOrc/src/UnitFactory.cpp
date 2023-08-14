#include "UnitFactory.h"

#include "const.h"
#include "Unit.h"
#include "Skill/SkillFactory.h"

namespace HumanVSOrc
{
    std::shared_ptr<Unit> UnitFactory::CreateKnight()
    {
        std::shared_ptr<Unit> unit = std::make_shared<Unit>("Knight");
        unit->AddLifeComponent(AttributeType::HEALTH, "Health", static_cast<float>(GameConstants::KnightConstants::BASE_HEALTH));
        unit->AddLifeComponent(AttributeType::SHIELD, "Shield", static_cast<float>(GameConstants::KnightConstants::BASE_SHIELD));
        unit->AddAttribute(AttributeType::DAMAGE, "Damage", static_cast<float>(GameConstants::KnightConstants::BASE_DAMAGE));

        unit->AddSkill(skills::SkillFactory::CreateChargeSkill());
        
        return unit;
    }

    std::shared_ptr<Unit> UnitFactory::CreateOrc()
    {
        std::shared_ptr<Unit> unit = std::make_shared<Unit>("Orc");
        unit->AddLifeComponent(AttributeType::HEALTH, "Health", static_cast<float>(GameConstants::OrcConstants::BASE_HEALTH));
        unit->AddAttribute(AttributeType::DAMAGE, "Damage", static_cast<float>(GameConstants::OrcConstants::BASE_DAMAGE));

        unit->AddSkill(skills::SkillFactory::CreateStunSkill());
        
        return unit;
    }
}
