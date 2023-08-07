#pragma once
#include <memory>

// class Unit;

class Unit;

namespace Skill
{
    // Command is the base class for all commands.
    // It is used to implement the Command design pattern.
    class Command
    {
    public:
        virtual ~Command() = default;
        virtual void Execute(std::weak_ptr<Unit> caster, std::weak_ptr<Unit> target) = 0;
        
    };
    
}
