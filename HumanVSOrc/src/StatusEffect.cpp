#include "StatusEffect.h"

#include "Skill/Command.h"


namespace HumanVSOrc
{
    StatusEffect::StatusEffect(std::string name, int duration, StatusEffectType type) : name(std::move(name)),
        duration(duration), type(type)
    {
    }

    StatusEffect::~StatusEffect() = default;

    void StatusEffect::Tick()
    {
        if (duration > 0)
        {
            duration--;
        }

        if (on_update_command != nullptr)
        {
            on_update_command->Execute(caster, target);
        }
    }

    void StatusEffect::OnApply() const
    {
        if (on_apply_command != nullptr)
        {
            on_apply_command->Execute(caster, target);
        }
    }

    void StatusEffect::OnRemove() const
    {
        if (on_remove_command != nullptr)
        {
            on_remove_command->Execute(caster, target);
        }
    }


    bool StatusEffect::IsOver() const
    {
        return duration == 0;
    }

    std::string StatusEffect::GetName() const
    {
        return name;
    }

    int StatusEffect::GetDuration() const
    {
        return duration;
    }

    StatusEffectType StatusEffect::GetType() const
    {
        return type;
    }

    StatusEffect& StatusEffect::SetOnApplyCommand(std::unique_ptr<skills::Command> command)
    {
        on_apply_command = std::move(command);
        return *this;
    }

    StatusEffect& StatusEffect::SetOnUpdateCommand(std::unique_ptr<skills::Command> command)
    {
        on_update_command = std::move(command);
        return *this;
    }

    StatusEffect& StatusEffect::SetOnRemoveCommand(std::unique_ptr<skills::Command> command)
    {
        on_remove_command = std::move(command);
        return *this;
    }

    StatusEffect& StatusEffect::SetCaster(std::weak_ptr<ITargetable> caster_ptr)
    {
        this->caster = std::move(caster_ptr);
        return *this;
    }

    StatusEffect& StatusEffect::SetTarget(std::weak_ptr<ITargetable> target_ptr)
    {
        this->target = std::move(target_ptr);
        return *this;
    }

    bool StatusEffect::operator==(const StatusEffect& other) const
    {
        return name == other.name && type == other.type;
    }
}
