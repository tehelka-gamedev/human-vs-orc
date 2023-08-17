#pragma once
#include <memory>

#include "Command.h"
#include "../StatusEffect.h"

namespace HumanVSOrc
{
    class StatusEffect;
    namespace skills
    {
    
        class ApplyStatusEffectCommand : public Command
        {
            std::unique_ptr<StatusEffect> status;
            
        public:
            explicit ApplyStatusEffectCommand(std::unique_ptr<StatusEffect> status);
            ~ApplyStatusEffectCommand() override;
            void Execute(std::weak_ptr<ITargetable> caster, std::weak_ptr<ITargetable> target) override;
        
        };
    }
    
}
