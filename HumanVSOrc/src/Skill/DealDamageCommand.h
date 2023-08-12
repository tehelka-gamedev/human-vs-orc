#pragma once
#include "Command.h"

namespace skills
{
    class DealDamageCommand : public Command
    {
    private:
        float damage_amount = 0.0f;
    public:
        explicit DealDamageCommand(float damage_amount);
        void Execute(::std::weak_ptr<ITargetable> caster, ::std::weak_ptr<ITargetable> target) override;
    };
}
