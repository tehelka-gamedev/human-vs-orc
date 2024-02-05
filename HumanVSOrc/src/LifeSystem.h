#pragma once
#include <memory>
#include <string>
#include <vector>

#include "AttributeType.h"
#include "AttributeGauge.h"

namespace HumanVSOrc
{
    class Attribute;
    class AttributeGauge;
    class Bonus;
    /*
    LifeSystem class
    This class is responsible for managing the life of a Unit.
    This is used to have modular life components like health, shield, or whatever.
*/
    class LifeSystem
    {
        // Attributes
    private:
        std::vector<std::weak_ptr<AttributeGauge>> components;

    public:
        LifeSystem();
        ~LifeSystem();

        bool HasComponent(AttributeType attribute_type) const;

        // Take damage to the first non-depleted life component
        // until the damage is depleted, starting from the last added component
        void TakeDamage(float damage);

        // Returns true if all life components are depleted
        bool IsDepleted() const;

        void AddComponent(const std::shared_ptr<AttributeGauge>& component);

        // Get a component value or max value, given its name
        // If the component does not exist, return std::nanf("")
        float GetComponentValue(AttributeType attribute_type) const;
        float GetComponentMaxValue(AttributeType attribute_type) const;
        

        // Debug function to print the life components
        void PrintComponents() const;
    };
}
