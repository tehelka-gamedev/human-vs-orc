﻿#pragma once
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
    
    std::weak_ptr<Unit> target;

    std::unique_ptr<class Equipment> equipment;
    
public:
    explicit Unit(std::string name);
    ~Unit();

    // Attack the target
    // If no target, do nothing
    void Attack();
    
    // Returns true if the unit has an attribute of the given type
    // Also check if the attribute is in the LifeSystem
    bool HasAttribute(AttributeType attribute_type) const;
    
    void AddAttribute(AttributeType attribute_type, const std::string& display_name, float base_value);
    void AddLifeComponent(AttributeType attribute_type, const std::string& component_name, float max_value) const;

    // public for now to be able to test
    // but may be private later
    // Add a bonus to the unit
    void AddBonus(const std::shared_ptr<Bonus>& bonus);
    void AddMultipleBonus(const std::vector<std::shared_ptr<Bonus>>& bonuses);
    
    void TakeDamage(float amount) const;

    bool IsAlive() const;

    // For each attribute, Tick() all bonuses contained in the attributes
    // that are either in the map or in the life system
    void TickAllBonuses();

    //// Equipment
    void Equip(std::shared_ptr<class EquippableItem> equippable_item);
    
    // Getters
    std::string GetName() const;
    float GetLifeComponentValue(AttributeType attribute_type) const;
    float GetLifeComponentMaxValue(AttributeType attribute_type) const;
    float GetAttributeValue(AttributeType attribute_type) const;
    
    // Setters
    void SetName(const std::string& new_name);
    void SetTarget(const std::shared_ptr<Unit>& new_target);

    // Debug function to print the unit info
    void PrintInfo() const;
    void PrintAttributes() const;

    
};
