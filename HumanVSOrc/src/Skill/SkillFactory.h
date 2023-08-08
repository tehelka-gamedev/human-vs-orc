#pragma once
#include <memory>

class Bonus;

namespace Skills
{
    class Skill;
    
    class SkillFactory
    {
    public:
        ~SkillFactory();
        static std::unique_ptr<Skill> CreateChargeSkill();
        static std::unique_ptr<Skill> CreateStunSkill();
        
    };
    
}
