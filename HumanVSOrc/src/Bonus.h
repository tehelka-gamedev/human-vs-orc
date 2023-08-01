#pragma once
#include "BonusType.h"

class Bonus
{
    // Attributes
private:
    float value = 0; // The raw additive value of the bonus (e.g. +10)
    float multiplier = 0; // The raw multiplicative value of the bonus (e.g. 0.10 = +10%)
    BonusType bonus_type;
    int time_left = 0; // The time left in seconds for the bonus to be active. -1 means infinite.
public:
    Bonus(float value, float multiplier, BonusType bonus_type, int time_left=-1);
    Bonus(float value, BonusType bonus_type, int time_left=-1);
    
    // Getters
    float GetValue() const;
    float GetMultiplier() const;
    BonusType GetBonusType() const;
    int GetTimeLeft() const;

    bool IsOver() const;
    void Tick(); // Decrease the time left by 1. If the time left is already 0, do nothing.

    // Two bonuses are equal if they have the same value, multiplier and bonus type.
    // The time left is not taken into account.
    // Needed to use std::remove_if
    bool operator==(const Bonus& other) const;
};
