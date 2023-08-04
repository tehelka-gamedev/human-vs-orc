#include "Weapon.h"

Weapon::Weapon(std::string name, float damage) : name(std::move(name)), damage_bonus(std::make_shared<Bonus>(damage, AttributeType::DAMAGE, Bonus::Type::RAW))
{
}

std::string Weapon::GetName() const
{
    return name;
}

std::shared_ptr<Bonus>& Weapon::GetDamageBonus()
{
    return damage_bonus;
}
