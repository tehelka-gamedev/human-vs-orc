#include "ApplyStatusEffectCommand.h"

#include <iostream>

#include "StatusEffect.h"
#include "../Unit.h"

namespace Skills
{
    ApplyStatusEffectCommand::ApplyStatusEffectCommand(std::unique_ptr<StatusEffect> status) : status(std::move(status))
    {
    }

    void ApplyStatusEffectCommand::Execute(std::weak_ptr<Unit> caster, std::weak_ptr<Unit> target)
    {
        std::shared_ptr<Unit> target_ptr = target.lock();
        if (!target_ptr)
        {

            std::cout << "ApplyStatusEffectCommand: target is null" << std::endl;
            return;
        }

        target_ptr->AddStatusEffect(std::move(status));
    }
}
