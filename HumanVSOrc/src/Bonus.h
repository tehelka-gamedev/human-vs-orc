#pragma once
#include "AttributeType.h"

namespace HumanVSOrc
{
    class Bonus
    {
    public:
        enum class Type
        {
            RAW,
            FINAL,
        };

        // Attributes
    private:
        float value = 0; // The raw additive value of the bonus (e.g. +10)
        float multiplier = 0; // The raw multiplicative value of the bonus (e.g. 0.10 = +10%)
        AttributeType target_attribute;
        int time_left = -1; // The time left in seconds for the bonus to be active. -1 means infinite.
        Type bonus_type;
    public:
        Bonus(float value, float multiplier, AttributeType attribute_to_target, Type bonus_type, int time_left=-1);
        Bonus(float value, AttributeType attribute_to_target, Type bonus_type, int time_left=-1);
    
        // Getters
        float GetValue() const;
        float GetMultiplier() const;
        AttributeType GetTargetAttribute() const;
        int GetTimeLeft() const;
        Type GetBonusType() const;

        bool IsOver() const;
        void Tick(); // Decrease the time left by 1. If the time left is already 0, do nothing.

        // Two bonuses are equal if they have the same value, multiplier and bonus type.
        // The time left is not taken into account.
        // Needed to use std::remove_if
        bool operator==(const Bonus& other) const;
    };
    
}
