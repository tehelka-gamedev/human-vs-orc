#include "Bonus.h"

Bonus::Bonus(float value, float multiplier, BonusType bonus_type, int time_left) : value(value), multiplier(multiplier), bonus_type(bonus_type), time_left(time_left)
{
}

Bonus::Bonus(float value, BonusType bonus_type, int time_left) : Bonus(value, 0, bonus_type, time_left)
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

BonusType Bonus::GetBonusType() const
{
    return bonus_type;
}

int Bonus::GetTimeLeft() const
{
    return time_left;
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
    return value == other.GetValue() && multiplier == other.GetMultiplier() && bonus_type == other.GetBonusType();
}






