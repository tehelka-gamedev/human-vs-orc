#pragma once
#include <memory>
#include <string>
#include <vector>

/*
    LifeSystem class
    This class is responsible for managing the life of a Unit.
    This is used to have modular life components like health, shield, or whatever.
*/
class LifeSystem
{
    // Attributes
private:
    std::vector<std::unique_ptr<class LifeComponent>> components;
    
public:
    LifeSystem();
    ~LifeSystem();
    // Take damage to the first non-depleted life component
    // until the damage is depleted, starting from the last added component
    void TakeDamage(float damage);

    // Returns true if all life components are depleted
    bool IsDepleted() const;
    
    void AddComponent(std::string name, float max_value);

    // Get a component value or max value, given its name
    // If the component does not exist, return -1
    float GetComponentValue(const std::string& name) const;
    float GetComponentMaxValue(const std::string& name) const;
    
    
    // Debug function to print the life components
    void PrintComponents() const;
};
