#pragma once
#include <memory>

namespace skills
{
    class StatusEffect;
}

class Bonus;

class ITargetable
{
public:
    virtual ~ITargetable() = default;
    virtual void TakeDamage(float amount) const = 0;
    virtual void AddBonus(const std::shared_ptr<Bonus>& bonus) = 0;
    virtual void AddStatusEffect(std::unique_ptr<skills::StatusEffect> status_effect) = 0;
};
