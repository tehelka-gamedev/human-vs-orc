#pragma once
#include <memory>
#include <string>

#include "Bonus.h"

// Class managing a weapon
class Weapon
{
    // Attributes
private:
    std::string name;
    std::shared_ptr<Bonus> damage_bonus;

public:
    Weapon(std::string name, float damage);

    // Getters
    std::string GetName() const;
    std::shared_ptr<Bonus>&  GetDamageBonus();
};
