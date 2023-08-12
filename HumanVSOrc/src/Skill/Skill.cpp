#include "Skill.h"

#include <iostream>
#include <utility>

#include "../RandomGenerator.h"
#include "Command.h"

namespace skills
{
    Skill::Skill(std::string name, const int cd, const float success_rate, std::unique_ptr<Command> command) : name(std::move(
        name)), cooldown(cd), success_rate(success_rate), command(std::move(command))
    {
        if (success_rate < 0.0f || success_rate > 1.0f)
        {
            throw std::invalid_argument(
            "You cannot create a skill '" + this->name + "' with a success rate of " + std::to_string(success_rate)
        + ". It must be between 0.0 and 1.0.");
        }
    }

    Skill::~Skill() = default;

    void Skill::Tick()
    {
        if (current_cooldown > 0)
        {
            current_cooldown--;
        }
    }

    bool Skill::IsReady() const
    {
        return current_cooldown == 0;
    }

    void Skill::Execute(::std::weak_ptr<ITargetable> caster, ::std::weak_ptr<ITargetable> target)
    {
        if(command == nullptr)
        {
            std::cout << "Skill " << name << " has no command associated!" << std::endl;
            return;
        }
        
        if (!IsReady())
        {
            std::cout << "Skill " << name << " is not ready!" << std::endl;
            return;
        }
        current_cooldown = cooldown;
        const float random_event = RandomGenerator::uniform(RandomGenerator::generator);
        if (random_event > success_rate)
        {
            std::cout << "Skill " << name << " failed!" << std::endl;
            return;
        }
        std::cout << "Skill " << name << " casted!" << std::endl;
        command->Execute(std::move(caster), std::move(target));
    }

    int Skill::GetCooldown() const
    {
        return cooldown;
    }

    int Skill::GetCurrentCooldown() const
    {
        return current_cooldown;
    }

    void Skill::SetSuccessRate(float rate)
    {
        if (rate < 0.0f || rate > 1.0f)
        {
            throw std::invalid_argument(
            "You cannot set the success rate of skill '" + this->name + "' to " + std::to_string(rate)
        + ". It must be between 0.0 and 1.0.");
        }
        success_rate = rate;
    }
}
