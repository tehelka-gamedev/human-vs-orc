#pragma once
#include <memory>

namespace HumanVSOrc
{
    class Bonus;

    namespace skills
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
    
}
