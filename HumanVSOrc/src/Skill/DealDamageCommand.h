#pragma once
#include "Command.h"

namespace Skills
{
    class DealDamageCommand : public Command
    {
    private:
        float damage_amount = 0.0f;
    public:
        explicit DealDamageCommand(float damage_amount);
        void Execute(std::weak_ptr<Unit> caster, std::weak_ptr<Unit> target) override;
    };
}
