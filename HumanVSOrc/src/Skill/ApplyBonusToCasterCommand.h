#pragma once
#include "Command.h"

class Bonus;

namespace Skills
{
    class ApplyBonusToCasterCommand : public Command
    {
        std::shared_ptr<Bonus> bonus;
    public:
        explicit ApplyBonusToCasterCommand(std::shared_ptr<Bonus> bonus);
        void Execute(std::weak_ptr<Unit> caster, std::weak_ptr<Unit> target) override;
    };
    
}
