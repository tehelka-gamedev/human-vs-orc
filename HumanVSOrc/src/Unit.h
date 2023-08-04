#pragma once
#include <map>
#include <string>

#include "Attribute.h"
#include "Bonus.h"
#include "AttributeType.h"
#include "LifeSystem.h"

class Unit
{
    // Attributes
private:
    std::string name;
    std::unique_ptr<LifeSystem> life_system;
    std::map<AttributeType, std::unique_ptr<Attribute> > attributes = {};


public:
    explicit Unit(std::string name);
    ~Unit();

    // Returns true if the unit has an attribute of the given type
    // Also check if the attribute is in the LifeSystem
    bool HasAttribute(AttributeType attribute_type) const;
    
    void AddAttribute(AttributeType attribute_type, const std::string& display_name, float base_value);
    void AddLifeComponent(AttributeType attribute_type, const std::string& component_name, float max_value) const;

    // public for now to be able to test
    // but may be private later
    // Add a bonus to the unit
    void AddBonus(const std::shared_ptr<Bonus>& bonus);
    
    void TakeDamage(float amount) const;

    bool IsAlive() const;
    
    
    // Getters
    std::string GetName() const;
    float GetLifeComponentValue(AttributeType attribute_type) const;
    float GetLifeComponentMaxValue(AttributeType attribute_type) const;
    
    // Setters
    void SetName(const std::string& new_name);

    // Debug function to print the unit info
    void PrintInfo() const;
};
