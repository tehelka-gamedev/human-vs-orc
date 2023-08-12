#pragma once
#include "Command.h"

class Bonus;

namespace skills
{
    class ApplyBonusToCasterCommand : public Command
    {
        std::shared_ptr<Bonus> bonus;
    public:
        explicit ApplyBonusToCasterCommand(std::shared_ptr<Bonus> bonus);
        void Execute(std::weak_ptr<ITargetable> caster, std::weak_ptr<ITargetable> target) override;
    };
    
}
