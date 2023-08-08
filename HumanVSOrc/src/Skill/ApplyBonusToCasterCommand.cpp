#include "ApplyBonusToCasterCommand.h"

#include <iostream>

#include "../Unit.h"
#include "../Bonus.h"

Skills::ApplyBonusToCasterCommand::ApplyBonusToCasterCommand(std::shared_ptr<Bonus> bonus) : bonus(std::move(bonus))
{
}

void Skills::ApplyBonusToCasterCommand::Execute(std::weak_ptr<Unit> caster, std::weak_ptr<Unit> target)
{
    std::shared_ptr<Unit> caster_ptr = caster.lock();
    if (!caster_ptr)
    {
        // This may be not necessary for this command ? As if the caster cast for instance
        // a fireball, the caster can die before the fireball hits the target.
        std::cout << "ApplyBonusToCasterCommand: caster is null" << std::endl;
        return;
    }
    caster_ptr->AddBonus(bonus);
}
