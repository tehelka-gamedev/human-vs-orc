#pragma once
#include <memory>
#include <string>
#include <vector>

namespace HumanVSOrc
{
    class Attribute;
    class LifeComponent;
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
        std::vector<std::unique_ptr<LifeComponent>> components;
    
    public:
        LifeSystem();
        ~LifeSystem();

        // Iterate over all components and add the bonus to the first
        // component that matches the bonus target attribute
        void AddBonus(const std::shared_ptr<Bonus>& bonus);
        void RemoveBonus(std::shared_ptr<Bonus>& bonus);
    
        bool HasComponent(enum class AttributeType attribute_type) const;

        void Tick();
    
        // Take damage to the first non-depleted life component
        // until the damage is depleted, starting from the last added component
        void TakeDamage(float damage);

        // Returns true if all life components are depleted
        bool IsDepleted() const;
    
        void AddComponent(enum class AttributeType attribute_type, const std::string& display_name, float max_value);

        // Get a component value or max value, given its name
        // If the component does not exist, return std::nanf("")
        float GetComponentValue(AttributeType attribute_type) const;
        float GetComponentMaxValue(AttributeType attribute_type) const;
        // Get an attribute given its type
        // If the attribute does not exist, return nullptr
        std::shared_ptr<Attribute> GetComponent(AttributeType attribute_type) const;
    
    
        // Debug function to print the life components
        void PrintComponents() const;
    };
    
}
