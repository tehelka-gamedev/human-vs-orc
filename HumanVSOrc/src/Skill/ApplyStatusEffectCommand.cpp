#include "ApplyStatusEffectCommand.h"

#include <iostream>

#include "../StatusEffect.h"
#include "../ITargetable.h"

namespace HumanVSOrc
{
    namespace skills
    {
        ApplyStatusEffectCommand::ApplyStatusEffectCommand(std::unique_ptr<StatusEffect> status) : status(std::move(status))
        {
        }

        ApplyStatusEffectCommand::~ApplyStatusEffectCommand() = default;

        void ApplyStatusEffectCommand::Execute(::std::weak_ptr<ITargetable> caster, ::std::weak_ptr<ITargetable> target)
        {
            std::shared_ptr<ITargetable> target_ptr = target.lock();
            if (!target_ptr)
            {

                std::cout << "ApplyStatusEffectCommand: target is null" << std::endl;
                return;
            }
            status->SetCaster(caster)
                   .SetTarget(target);

            // Create the StatusEffect
            status->OnApply();
            target_ptr->AddStatusEffect(std::move(status));
        }
    }
    
}
