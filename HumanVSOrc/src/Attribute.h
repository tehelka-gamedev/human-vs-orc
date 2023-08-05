#pragma once
#include <memory>
#include <string>
#include <vector>

#include "AttributeType.h"


class Attribute
{
    // Attributes
private:
    AttributeType attribute_type;
    std::string display_name;
    float base_value = 0;
    std::vector<std::shared_ptr<class Bonus>> raw_bonus;
    std::vector<std::shared_ptr<Bonus>> final_bonus;

    float final_value = 0; // Cache the final value to avoid recalculating it every time.
    bool is_dirty = true; // If true, the final value needs to be recalculated.

    float CalculateFinalValue();

    void AddRawBonus(const std::shared_ptr<Bonus>& bonus);
    void AddFinalBonus(const std::shared_ptr<Bonus>& bonus);
    void RemoveRawBonus(std::shared_ptr<Bonus>& bonus);
    void RemoveFinalBonus(std::shared_ptr<Bonus>& bonus);
public:
    Attribute(AttributeType attribute_type, const std::string& name, float value);
    ~Attribute();

    void AddBonus(const std::shared_ptr<Bonus>& bonus);
    void RemoveBonus(std::shared_ptr<Bonus>& bonus);
    

    void Tick(); // Decrease the time left of all bonuses by 1.

    float GetValue();
    AttributeType GetAttributeType() const;
    std::string GetDisplayName() const;

    // Setters
    void SetBaseValue(float new_value);

    // Print info for debugging
    void PrintInfo();
    
};
