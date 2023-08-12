#pragma once
#include <memory>
#include <string>

namespace HumanVSOrc
{
    class ITargetable;
    class Unit;

    namespace skills
    {
        class Command;

        class Skill
        {
            // Attributes
        private:
            std::string name;
            int cooldown = 0;
            int current_cooldown = 0;
            float success_rate = 1.0f;

            std::unique_ptr<Command> command;
        public:
            Skill(std::string name, int cd, float success_rate, std::unique_ptr<Command> command);
            ~Skill();
            // Reduce the cooldown by 1
            void Tick();

        
            bool IsReady() const;
            void Execute(std::weak_ptr<ITargetable> caster, std::weak_ptr<ITargetable> target);

            // Getters
            int GetCooldown() const;
            int GetCurrentCooldown() const;

            // Setters
            void SetSuccessRate(float rate);
        };
    }
    
}
