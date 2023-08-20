#include "EquippableItemFactory.h"

#include "const.h"
#include "EquippableItem.h"
#include "Equipment.h"

#include "Bonus.h"

std::shared_ptr<HumanVSOrc::EquippableItem> HumanVSOrc::EquippableItemFactory::CreateSword()
{
    std::shared_ptr<EquippableItem> sword = std::make_shared<EquippableItem>("Sword", Equipment::Slot::WEAPON);
    std::shared_ptr<Bonus> damage_bonus = std::make_shared<Bonus>(GameConstants::SWORD_DAMAGE, AttributeType::DAMAGE, Bonus::Type::RAW);

    sword->AddBonus(damage_bonus);

    return sword;
}

std::shared_ptr<HumanVSOrc::EquippableItem> HumanVSOrc::EquippableItemFactory::CreateAxe()
{
    std::shared_ptr<EquippableItem> axe = std::make_shared<EquippableItem>("Axe", Equipment::Slot::WEAPON);
    std::shared_ptr<Bonus> damage_bonus = std::make_shared<Bonus>(GameConstants::AXE_DAMAGE, AttributeType::DAMAGE, Bonus::Type::RAW);

    axe->AddBonus(damage_bonus);

    return axe;
}
