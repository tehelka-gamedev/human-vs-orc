#pragma once
#include <memory>

#include "Skill.h"

namespace HumanVSOrc
{
    class Bonus;

    namespace skills
    {
    
        class SkillFactory
        {
        public:
            ~SkillFactory();
            static std::unique_ptr<Skill> CreateChargeSkill();
            static std::unique_ptr<Skill> CreateStunSkill();
            static std::unique_ptr<Skill> CreateBleedingStrikeSkill();
        
        };
    
    }
    
}
