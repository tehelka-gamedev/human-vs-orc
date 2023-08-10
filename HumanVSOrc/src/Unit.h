#pragma once
#include <map>
#include <string>

#include "Attribute.h"
#include "Bonus.h"
#include "AttributeType.h"
#include "Equipment.h"
#include "LifeSystem.h"
#include "Skill/StatusEffect.h"


namespace Skills
{
    class Skill;
    class StatusEffect;
}

class EquippableItem;
class Equipment;

class Unit : public std::enable_shared_from_this<Unit>
{
    // Attributes
private:
    std::string name;
    std::unique_ptr<LifeSystem> life_system;
    std::map<AttributeType, std::unique_ptr<Attribute> > attributes = {};
    
    std::weak_ptr<Unit> target;

    std::unique_ptr<Equipment> equipment;

    std::vector<std::unique_ptr<Skills::Skill>> skills;
    std::vector<std::unique_ptr<Skills::StatusEffect>> status_effects;
    
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

    // Remove a bonus from the unit
    void RemoveBonus(std::shared_ptr<Bonus>& bonus);
    void RemoveMultipleBonus(std::vector<std::shared_ptr<Bonus>>& bonuses);
    
    void TakeDamage(float amount) const;

    bool IsAlive() const;

    // For each attribute, Tick() all bonuses contained in the attributes
    // that are either in the map or in the life system
    void TickAllBonuses() const;

    //// Equipment
    void Equip(std::shared_ptr<EquippableItem> equippable_item);
    // Unequip the item in the given slot, should return the item (TODO later)
    void Unequip(Equipment::Slot equipment_slot);


    //// Skills
    // Add a skill to the unit
    void AddSkill(std::unique_ptr<Skills::Skill> skill);
    // Cast all skills
    void CastAllSkills();
    void TickAllSkills() const;

    //// Status effects
    // Add a status effect to the unit
    void AddStatusEffect(std::unique_ptr<Skills::StatusEffect> status_effect);
    // Tick all status effects
    void TickAllStatusEffects();
    // Returns true if the unit has a status effect of the given type
    bool HasStatusEffect(Skills::StatusEffect::Type status_effect_type) const;
    
    // Getters
    std::string GetName() const;
    float GetLifeComponentValue(AttributeType attribute_type) const;
    float GetLifeComponentMaxValue(AttributeType attribute_type) const;
    // Returns the value of the attribute of the given type
    // If the attribute is not found, returns std::nanf("")
    float GetAttributeValue(AttributeType attribute_type) const;
    
    // Setters
    void SetName(const std::string& new_name);
    void SetTarget(const std::shared_ptr<Unit>& new_target);

    // Debug function to print the unit info
    void PrintInfo() const;
    void PrintAttributes() const;

    
};
