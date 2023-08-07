#include "DealDamageCommand.h"

#include <iostream>
#include "../Unit.h"

namespace Skill
{
    DealDamageCommand::DealDamageCommand(float damage_amount) : damage_amount(damage_amount)
    {
    }

    DealDamageCommand::~DealDamageCommand() = default;
    
    void DealDamageCommand::Execute(std::weak_ptr<Unit> caster, std::weak_ptr<Unit> target)
    {
        // Assumes caster has a Damage attribute
        std::shared_ptr<Unit> caster_ptr = caster.lock();
        if (!caster_ptr)
        {
            // This may be not necessary for this command ? As if the caster cast for instance
            // a fireball, the caster can die before the fireball hits the target.
            std::cout << "DealDamageCommand: caster is null" << std::endl;
            return;
        }
        if (!caster_ptr->HasAttribute(AttributeType::DAMAGE))
        {
            std::cout << "DealDamageCommand: caster has no damage attribute" << std::endl;
            return;
        }

        std::shared_ptr<Unit> target_ptr = target.lock();
        if(!target_ptr)
        {
            std::cout << "DealDamageCommand: target is null" << std::endl;
            return;
        }

        target_ptr->TakeDamage(damage_amount);

        
    }

}
