#include "Weapon.h"

Weapon::Weapon(std::string name, float damage) : name(std::move(name)), damage_bonus(std::make_shared<Bonus>(damage, BonusType::DAMAGE))
{
}

std::shared_ptr<Bonus>& Weapon::GetDamageBonus()
{
    return damage_bonus;
}
