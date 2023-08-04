#include "Unit.h"

#include <iostream>



Unit::Unit(std::string name) : name(std::move(name)), life_system(std::make_unique<LifeSystem>())
{
}

Unit::~Unit()
= default;

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

void Unit::SetName(const std::string& new_name)
{   
    name = new_name;
}

void Unit::PrintInfo() const
{   
    std::cout << "Unit name: " << name << std::endl;
    life_system->PrintComponents();
    std::cout << std::endl;
}
