#pragma once
#include <map>
#include <string>

#include "Attribute.h"
#include "Bonus.h"
#include "AttributeType.h"
#include "DependentAttribute.h"
#include "Equipment.h"
#include "ITargetable.h"
#include "LifeSystem.h"
#include "StatusEffect.h"



namespace HumanVSOrc
{
namespace skills
{
    class Skill;
}
    
    class StatusEffect;
class EquippableItem;
class Equipment;

class Unit : public std::enable_shared_from_this<Unit>, public ITargetable
{
    // Attributes
private:
    std::string name;
    std::unique_ptr<LifeSystem> life_system;
    std::map<AttributeType, std::shared_ptr<Attribute> > attributes = {};
    
    std::weak_ptr<Unit> target;

    std::unique_ptr<Equipment> equipment;

    std::vector<std::unique_ptr<skills::Skill>> skills;
    std::vector<std::unique_ptr<StatusEffect>> status_effects;
    
public:
    explicit Unit(std::string name);
    ~Unit() override;

    // Attack the target
    // If no target, do nothing
    void Attack();
    
    // Returns true if the unit has an attribute of the given type
    // Also check if the attribute is in the LifeSystem
    bool HasAttribute(AttributeType attribute_type) const;
    
    void AddAttribute(AttributeType attribute_type, const std::string& display_name, float base_value);
    void AddDependentAttribute(AttributeType attribute_type, const std::string& display_name, float base_value, std::vector<DependentAttribute::Dependency>& dependencies);
    void AddLifeComponent(AttributeType attribute_type, const std::string& component_name, float max_value) const;

    // public for now to be able to test
    // but may be private later
    // Add a bonus to the unit
    void AddBonus(const std::shared_ptr<Bonus>& bonus) override;
    void AddMultipleBonus(const std::vector<std::shared_ptr<Bonus>>& bonuses);

    // Remove a bonus from the unit
    void RemoveBonus(std::shared_ptr<Bonus>& bonus);
    void RemoveMultipleBonus(std::vector<std::shared_ptr<Bonus>>& bonuses);
    
    void TakeDamage(float amount) const override;

    bool IsAlive() const;

    // For each attribute, Tick() all bonuses contained in the attributes
    // that are either in the map or in the life system
    void TickAllBonuses() const;

    //// Equipment
    void Equip(std::shared_ptr<EquippableItem> equippable_item);
    // Unequip the item in the given slot (should be better to return the item, but not done)
    void Unequip(Equipment::Slot equipment_slot);


    //// Skills
    // Add a skill to the unit
    void AddSkill(std::unique_ptr<skills::Skill> skill);
    // Cast all skills
    void CastAllSkills();
    void TickAllSkills() const;

    //// Status effects
    // Add a status effect to the unit
    void AddStatusEffect(std::unique_ptr<HumanVSOrc::StatusEffect> status_effect) override;
    // Tick all status effects
    void TickAllStatusEffects();
    // Returns true if the unit has a status effect of the given type
    bool HasStatusEffect(HumanVSOrc::StatusEffectType status_effect_type) const;
    
    // Getters
    std::string GetName() const;
    float GetLifeComponentValue(AttributeType attribute_type) const;
    float GetLifeComponentMaxValue(AttributeType attribute_type) const;
    // Returns the value of the attribute of the given type
    // If the attribute is not found, returns std::nanf("")
    float GetAttributeValue(AttributeType attribute_type) const;
    // Get the attribute of the given type
    // If the attribute is not found, returns nullptr
    std::shared_ptr<Attribute> GetAttribute(AttributeType attribute_type) const;
        
    // Setters
    void SetName(const std::string& new_name);
    void SetTarget(const std::shared_ptr<Unit>& new_target);

    // Debug function to print the unit info
    void PrintInfo() const;
    void PrintAttributes() const;

    
};
}
