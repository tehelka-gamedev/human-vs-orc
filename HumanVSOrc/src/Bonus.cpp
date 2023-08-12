#include "Bonus.h"

#include <iostream>

namespace HumanVSOrc
{
    Bonus::Bonus(float value, float multiplier, AttributeType attribute_to_target, Type bonus_type, int time_left) : value(value), multiplier(multiplier), target_attribute(attribute_to_target), time_left(time_left), bonus_type(bonus_type)
    {
    }

    Bonus::Bonus(float value, AttributeType attribute_to_target,Type bonus_type, int time_left) : Bonus(value, 0, attribute_to_target, bonus_type, time_left)
    {
    
    }

    float Bonus::GetValue() const
    {
        return value;
    }

    float Bonus::GetMultiplier() const
    {
        return multiplier;
    }

    AttributeType Bonus::GetTargetAttribute() const
    {
        return target_attribute;
    }

    int Bonus::GetTimeLeft() const
    {
        return time_left;
    }

    Bonus::Type Bonus::GetBonusType() const
    {
        return bonus_type;
    }

    bool Bonus::IsOver() const
    {
        return time_left == 0;
    }

    void Bonus::Tick()
    {
        if(time_left > 0)
        {
            --time_left;
        }
    }

    bool Bonus::operator==(const Bonus& other) const
    {   
        return value == other.GetValue() && multiplier == other.GetMultiplier() && target_attribute == other.GetTargetAttribute();
    }
    
}





