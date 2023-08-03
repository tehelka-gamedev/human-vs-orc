#include "Unit.h"

#include <iostream>


Unit::Unit(std::string name) : name(std::move(name)), life_system(std::make_unique<LifeSystem>())
{
}

Unit::~Unit()
= default;

void Unit::AddLifeComponent(const std::string& component_name, float max_value) const
{
    life_system->AddComponent(component_name, max_value);
}

void Unit::AddBonus(const std::shared_ptr<Bonus>& bonus)
{
}

void Unit::TakeDamage(float amount) const
{
    life_system->TakeDamage(amount);
}

bool Unit::IsAlive() const
{
    return !life_system->IsDepleted();
}

std::string Unit::GetName() const
{
    return name;
}

float Unit::GetLifeComponentValue(const std::string& component_name) const
{
    return life_system->GetComponentValue(component_name);
}

float Unit::GetLifeComponentMaxValue(const std::string& component_name) const
{
    return life_system->GetComponentMaxValue(component_name);
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
