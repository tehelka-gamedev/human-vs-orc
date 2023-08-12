#pragma once
#include <memory>

#include "Command.h"

namespace skills
{
    class StatusEffect;
    
    class ApplyStatusEffectCommand : public Command
    {
        std::unique_ptr<StatusEffect> status;
    public:
        explicit ApplyStatusEffectCommand(std::unique_ptr<StatusEffect> status);
        void Execute(std::weak_ptr<ITargetable> caster, std::weak_ptr<ITargetable> target) override;
        
    };
}
