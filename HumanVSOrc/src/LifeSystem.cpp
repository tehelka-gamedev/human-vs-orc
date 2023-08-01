#include "LifeSystem.h"

#include <algorithm>
#include <iostream>
#include <ostream>

#include "LifeComponent.h"

LifeSystem::LifeSystem()
= default;

LifeSystem::~LifeSystem()
= default;

void LifeSystem::TakeDamage(float damage)
{
    std::cerr << "Take " << damage << " damage" << std::endl;
    float remaining_damage = damage;
    for (auto it = components.rbegin(); it != components.rend(); ++it)
    {
        std::unique_ptr<LifeComponent>& component = *it;
        if(!component->isDepleted())
        {
            remaining_damage = component->TakeDamage(remaining_damage);
            // Compare to 0 because TakeDamage can return exactly 0
            if(remaining_damage == 0)
            {
                break;
            }
        }
    }
}

bool LifeSystem::IsDepleted() const
{
    return std::all_of(
        components.begin(),
        components.end(),
        [](const std::unique_ptr<LifeComponent>& component) { return component->isDepleted(); }
        );
}

void LifeSystem::AddComponent(std::string name, float max_value)
{
    components.push_back(std::make_unique<LifeComponent>(std::move(name), max_value));
}

float LifeSystem::GetComponentValue(const std::string& name) const
{   
    for (const std::unique_ptr<LifeComponent>& component : components)
    {
        if(component->GetName() == name)
        {
            return component->GetValue();
        }
    }
    return -1;
}

float LifeSystem::GetComponentMaxValue(const std::string& name) const
{
    for (const std::unique_ptr<LifeComponent>& component : components)
    {
        if(component->GetName() == name)
        {
            return component->GetMaxValue();
        }
    }
    return -1;
}


void LifeSystem::PrintComponents() const
{
    std::cerr << "LifeSystem components:" << std::endl;
    for (const std::unique_ptr<LifeComponent>& component : components)
    {
        std::cerr << "    " << component->GetName() << ": " << component->GetValue() << "/" << component->GetMaxValue() << std::endl;
    }
}

