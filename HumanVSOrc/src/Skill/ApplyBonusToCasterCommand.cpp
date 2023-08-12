#include "ApplyBonusToCasterCommand.h"

#include <iostream>

#include "../ITargetable.h"
#include "../Bonus.h"

namespace HumanVSOrc
{
    namespace skills
    {
        ApplyBonusToCasterCommand::ApplyBonusToCasterCommand(std::shared_ptr<Bonus> bonus) : bonus(std::move(bonus))
        {
        }

        void ApplyBonusToCasterCommand::Execute(std::weak_ptr<ITargetable> caster, std::weak_ptr<ITargetable> target)
        {
            std::shared_ptr<ITargetable> caster_ptr = caster.lock();
            if (!caster_ptr)
            {
                // This may be not necessary for this command ? As if the caster cast for instance
                // a fireball, the caster can die before the fireball hits the target.
                std::cout << "ApplyBonusToCasterCommand: caster is null" << std::endl;
                return;
            }
            caster_ptr->AddBonus(bonus);
        }
    
    }
    
}
