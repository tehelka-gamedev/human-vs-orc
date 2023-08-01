﻿#pragma once
#include <memory>
#include <vector>

// TODO : refactor this class to use pointers to bonuses instead of copying them
// As they will be created outside of the attribute class, it will be easier to manage them.
class Attribute
{
    // Attributes
private:
    float base_value = 0;
    std::vector<std::shared_ptr<class Bonus>> raw_bonus;
    std::vector<std::shared_ptr<Bonus>> final_bonus;

    float final_value = 0; // Cache the final value to avoid recalculating it every time.
    bool is_dirty = true; // If true, the final value needs to be recalculated.

    float CalculateFinalValue();
public:
    Attribute(float value);
    ~Attribute();

    void AddRawBonus(const std::shared_ptr<Bonus>& bonus);
    void AddFinalBonus(const std::shared_ptr<Bonus>& bonus);
    void RemoveRawBonus(std::shared_ptr<Bonus>& bonus);
    void RemoveFinalBonus(std::shared_ptr<Bonus>& bonus);

    void Tick(); // Decrease the time left of all bonuses by 1.

    float GetValue();
    
    
};