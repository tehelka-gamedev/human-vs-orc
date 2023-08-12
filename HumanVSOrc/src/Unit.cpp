#include "Unit.h"

#include <algorithm>
#include <iostream>

#include "Equipment.h"
#include "EquippableItem.h"
#include "Skill/DealDamageCommand.h"
#include "Skill/Skill.h"

#include "Skill/StatusEffect.h"

Unit::Unit(std::string name) : name(std::move(name)), life_system(std::make_unique<LifeSystem>()), equipment(std::make_unique<Equipment>())
{
}


Unit::~Unit()
= default;

void Unit::Attack()
{
    // If the unit is stunned, do nothing
    if(HasStatusEffect(skills::StatusEffect::Type::STUNNED))
    {
        std::cout << name << " is stunned and cannot attack" << std::endl;
        return;
    }
    
    // Create a DealDamageCommand and execute it
    skills::DealDamageCommand deal_damage_command(GetAttributeValue(AttributeType::DAMAGE));
    deal_damage_command.Execute(std::weak_ptr<Unit>(shared_from_this()), target);
}

bool Unit::HasAttribute(AttributeType attribute_type) const
{
    return attributes.find(attribute_type) != attributes.end() || life_system->HasComponent(attribute_type);
}

void Unit::AddAttribute(AttributeType attribute_type, const std::string& display_name, float base_value)
{
    // If the attribute is already present, do something
    if (HasAttribute(attribute_type))
    {
        std::cout << "Attribute of type " << static_cast<int>(attribute_type) <<
            " already present" << std::endl;
        return;
    }
    // add the attribute
    attributes[attribute_type] = std::make_unique<Attribute>(attribute_type, display_name, base_value);
}

void Unit::AddLifeComponent(AttributeType attribute_type, const std::string& component_name, float max_value) const
{
    // If the attribute is already present, do something
    if (HasAttribute(attribute_type))
    {
        std::cout << "Attribute of type " << static_cast<int>(attribute_type) <<
            " already present" << std::endl;
        return;
    }
    life_system->AddComponent(attribute_type, component_name, max_value);
}

void Unit::AddBonus(const std::shared_ptr<Bonus>& bonus)
{
    
    AttributeType attribute_type = bonus->GetTargetAttribute();
    // If the attribute is not present, do something
    if (!HasAttribute(attribute_type))
    {
        std::cout << "Attribute of type " << static_cast<int>(attribute_type) <<
            " not present" << std::endl;
        return;
    }
    // add the bonus
    // if the attribute type is in the map, add the bonus to the attribute
    if (attributes.find(attribute_type) != attributes.end())
    {
        attributes[attribute_type]->AddBonus(bonus);
    }
    else if (life_system->HasComponent(attribute_type))
    {
        life_system->AddBonus(bonus);
    }
    
}

void Unit::AddMultipleBonus(const std::vector<std::shared_ptr<Bonus>>& bonuses)
{
    for (const auto& bonus : bonuses)
    {
        AddBonus(bonus);
    }
}

void Unit::RemoveBonus(std::shared_ptr<Bonus>& bonus)
{
    AttributeType attribute_type = bonus->GetTargetAttribute();
    // If the attribute is not present, do something
    if (!HasAttribute(attribute_type))
    {
        std::cout << "Attribute of type " << static_cast<int>(attribute_type) <<
            " not present" << std::endl;
        return;
    }
    // remove the bonus
    // if the attribute type is in the map, remove the bonus from the attribute
    if (attributes.find(attribute_type) != attributes.end())
    {
        attributes[attribute_type]->RemoveBonus(bonus);
    }
    else if (life_system->HasComponent(attribute_type))
    {
        life_system->RemoveBonus(bonus);
    }
}

void Unit::RemoveMultipleBonus(std::vector<std::shared_ptr<Bonus>>& bonuses)
{
    for (std::shared_ptr<Bonus>& bonus : bonuses)
    {
        RemoveBonus(bonus);
    }
}

void Unit::TakeDamage(float amount) const
{
    life_system->TakeDamage(amount);
}

bool Unit::IsAlive() const
{
    return !life_system->IsDepleted();
}

void Unit::TickAllBonuses() const
{   
    for (auto& attribute : attributes)
    {
        attribute.second->Tick();
    }
    life_system->Tick();
}

void Unit::Equip(std::shared_ptr<EquippableItem> equippable_item)
{
    // TODO : if already item in this slot, unequip it first
    // ...

    AddMultipleBonus(equippable_item->GetBonusesByReference());
    equipment->EquipItem(equippable_item, equippable_item->GetSlot());
}

void Unit::Unequip(Equipment::Slot equipment_slot)
{
    std::shared_ptr<EquippableItem> item = equipment->UnequipSlot(equipment_slot);
    std::vector<std::shared_ptr<Bonus>> bonuses = item->GetBonusesByReference();
    RemoveMultipleBonus(bonuses);
}

void Unit::AddSkill(std::unique_ptr<skills::Skill> skill)
{
    skills.push_back(std::move(skill));
}

void Unit::CastAllSkills()
{
    // If the unit is stunned, do nothing
    if (HasStatusEffect(skills::StatusEffect::Type::STUNNED))
    {
        std::cout << "Unit " << name << " is stunned and cannot cast skills" << std::endl;
        return;
    }
    
    const std::weak_ptr<Unit> caster(shared_from_this());
    for (const std::unique_ptr<skills::Skill>& skill : skills)
    {
        skill->Execute(caster, target);
    }
}

void Unit::TickAllSkills() const
{
    for (const std::unique_ptr<skills::Skill>& skill : skills)
    {
        skill->Tick();
    }
}

void Unit::AddStatusEffect(std::unique_ptr<skills::StatusEffect> status_effect)
{   
    // TODO : if already status effect of this type, do something
    status_effects.push_back(std::move(status_effect));
    
}

void Unit::TickAllStatusEffects()
{
    for (const std::unique_ptr<skills::StatusEffect>& status_effect : status_effects)
    {
        status_effect->Tick();
    }
    
    // remove all status effects that are over
    auto it = std::remove_if(
        status_effects.begin(),
        status_effects.end(),
        [](const std::unique_ptr<skills::StatusEffect>& status) { return status->IsOver(); });

    status_effects.erase(it, status_effects.end());
}

bool Unit::HasStatusEffect(skills::StatusEffect::Type status_effect_type) const
{
    return std::any_of(
        status_effects.begin(),
        status_effects.end(),
        [status_effect_type](const std::unique_ptr<skills::StatusEffect>& status) { return status->GetType() == status_effect_type; });
}

std::string Unit::GetName() const
{
    return name;
}

float Unit::GetLifeComponentValue(AttributeType attribute_type) const
{
    return life_system->GetComponentValue(attribute_type);
}

float Unit::GetLifeComponentMaxValue(AttributeType attribute_type) const
{
    return life_system->GetComponentMaxValue(attribute_type);
}

float Unit::GetAttributeValue(AttributeType attribute_type) const
{
    auto attribute = attributes.find(attribute_type);
    if (attribute != attributes.end())
    {
        return attribute->second->GetValue();
    }
    
    return std::numeric_limits<float>::quiet_NaN();
    
}

void Unit::SetName(const std::string& new_name)
{   
    name = new_name;
}

void Unit::SetTarget(const std::shared_ptr<Unit>& new_target)
{
    target = new_target;
}

void Unit::PrintInfo() const
{   
    std::cout << "Unit name: " << name << std::endl;
    life_system->PrintComponents();
    PrintAttributes();
    std::cout << std::endl;
}

void Unit::PrintAttributes() const
{
    for (auto& attribute : attributes)
    {
        attribute.second->PrintInfo();
    }
}
