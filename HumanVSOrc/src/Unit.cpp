#include "Unit.h"

#include <iostream>

#include "Equipment.h"
#include "EquippableItem.h"
#include "Skill/DealDamageCommand.h"

Unit::Unit(std::string name) : name(std::move(name)), life_system(std::make_unique<LifeSystem>()), equipment(std::make_unique<Equipment>())
{
}

Unit::~Unit()
= default;

void Unit::Attack()
{
    // // If no Damage attribute, cannot attack
    // if (!HasAttribute(AttributeType::DAMAGE))
    // {
    //     std::cout << "Unit " << name << " tried to attack but has no damage attribute" << std::endl;
    //     return;
    // }
    //
    // std::shared_ptr<Unit> target_ptr = target.lock();
    // if (!target_ptr)
    // {
    //     std::cout << "Unit " << name << " tried to attack but has no target" << std::endl;
    //     return;
    // }
    //
    // std::cout << name << " attacks " << target_ptr->name << std::endl;
    // target_ptr->TakeDamage(GetAttributeValue(AttributeType::DAMAGE));

    // Create a DealDamageCommand and execute it
    Skill::DealDamageCommand deal_damage_command(GetAttributeValue(AttributeType::DAMAGE));
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

void Unit::TickAllBonuses()
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
