#include "DealDamageCommand.h"

#include <iostream>
#include "../ITargetable.h"

namespace skills
{
    DealDamageCommand::DealDamageCommand(float damage_amount) : damage_amount(damage_amount)
    {
    }

    
    void DealDamageCommand::Execute(::std::weak_ptr<ITargetable> caster, ::std::weak_ptr<ITargetable> target)
    {
        // Assumes caster has a Damage attribute
        std::shared_ptr<ITargetable> caster_ptr = caster.lock();
        if (!caster_ptr)
        {
            // This may be not necessary for this command ? As if the caster cast for instance
            // a fireball, the caster can die before the fireball hits the target.
            std::cout << "DealDamageCommand: caster is null" << std::endl;
            return;
        }

        std::shared_ptr<ITargetable> target_ptr = target.lock();
        if(!target_ptr)
        {
            std::cout << "DealDamageCommand: target is null" << std::endl;
            return;
        }

        target_ptr->TakeDamage(damage_amount);

        
    }

}
