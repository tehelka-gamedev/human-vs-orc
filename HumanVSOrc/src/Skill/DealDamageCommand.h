#pragma once
#include "Command.h"

namespace Skill
{
    class DealDamageCommand : public Command
    {
    private:
        float damage_amount = 0.0f;
    public:
        explicit DealDamageCommand(float damage_amount);
        ~DealDamageCommand();
        void Execute(std::weak_ptr<Unit> caster, std::weak_ptr<Unit> target) override;
    };
}
