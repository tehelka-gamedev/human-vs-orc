#include "StatusEffect.h"

#include "Command.h"
#include "../ITargetable.h"


namespace skills
{
    StatusEffect::StatusEffect(std::string name, int duration, Type type,
                               std::unique_ptr<Command> on_update_command) : name(std::move(name)),
                                                                              duration(duration),
                                                                              type(type),
                                                                              on_update_command(std::move(
                                                                                      on_update_command))
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
            // TODO
            // on_update_command->Execute(caster, target);
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

    StatusEffect::Type StatusEffect::GetType() const
    {
        return type;
    }

    bool StatusEffect::operator==(const StatusEffect& other) const
    {
        return name == other.name && type == other.type;
    }
}
