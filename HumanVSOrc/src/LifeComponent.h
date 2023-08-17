#pragma once
#include <string>

#include "Attribute.h"

namespace HumanVSOrc
{
    /*
    LifeComponent class
    This class is responsible for managing a "life" bar
    This is used to have modular life components like health, shield, or whatever.
*/
    class LifeComponent
    {
        // Attributes
    private:
        float value = 0;
        std::shared_ptr<Attribute> max_value;
    
    
    public:
        LifeComponent(AttributeType attribute_type, std::string name, float max_value);

        bool IsDepleted() const;
        bool IsFull();

        void AddBonus(const std::shared_ptr<Bonus>& bonus);
        void RemoveBonus(std::shared_ptr<Bonus>& bonus);
    
        void Tick();
    
        // Take damage to this life component and return the amount of damage in excess
        float TakeDamage(float damage);
    
        // Getters
        float GetValue() const;
        float GetMaxValue();
        std::string GetDisplayName() const;
        AttributeType GetAttributeType() const;
        std::shared_ptr<Attribute> GetAttribute();

        // Setters
        void SetValue(float new_value);
        void SetMaxValue(float new_max_value);
    };
}
