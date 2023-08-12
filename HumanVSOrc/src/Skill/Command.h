#pragma once
#include <memory>

// class Unit;

namespace HumanVSOrc
{
    class ITargetable;

    namespace skills
    {
        // Command is the base class for all commands.
        // It is used to implement the Command design pattern.
        class Command
        {
        public:
            virtual ~Command() = default;
            virtual void Execute(std::weak_ptr<ITargetable> caster, std::weak_ptr<ITargetable> target) = 0;
        
        };
    
    }
}
