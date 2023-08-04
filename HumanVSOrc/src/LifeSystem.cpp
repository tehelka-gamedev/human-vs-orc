#include "LifeSystem.h"

#include <algorithm>
#include <iostream>
#include <ostream>

#include "AttributeType.h"
#include "LifeComponent.h"
#include "Bonus.h"

LifeSystem::LifeSystem()
= default;

LifeSystem::~LifeSystem()
= default;

void LifeSystem::AddBonus(const std::shared_ptr<Bonus>& bonus)
{
    // Iterate over all components and add the bonus to the first component that matches the bonus target attribute
    for(std::unique_ptr<LifeComponent>& component : components)
    {
        if(component->GetAttributeType() == bonus->GetTargetAttribute())
        {
            component->AddBonus(bonus);
            break;
        }
    }
}


bool LifeSystem::HasComponent(AttributeType attribute_type) const
{
    return std::any_of(
        components.begin(),
        components.end(),
        [attribute_type](const std::unique_ptr<LifeComponent>& component) { return component->GetAttributeType() == attribute_type; }
        );
}

void LifeSystem::Tick()
{
    for (std::unique_ptr<LifeComponent>& component : components)
    {
        component->Tick();
    }
}

void LifeSystem::TakeDamage(float damage)
{
    std::cerr << "Take " << damage << " damage" << std::endl;
    float remaining_damage = damage;
    for (auto it = components.rbegin(); it != components.rend(); ++it)
    {
        std::unique_ptr<LifeComponent>& component = *it;
        if(!component->IsDepleted())
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
        [](const std::unique_ptr<LifeComponent>& component) { return component->IsDepleted(); }
        );
}

void LifeSystem::AddComponent(AttributeType attribute_type, const std::string& display_name, float max_value)
{
    components.push_back(std::make_unique<LifeComponent>(attribute_type, display_name, max_value));
}

float LifeSystem::GetComponentValue(const AttributeType attribute_type) const
{   
    for (const std::unique_ptr<LifeComponent>& component : components)
    {
        if(component->GetAttributeType() == attribute_type)
        {
            return component->GetValue();
        }
    }
    return -1;
}

float LifeSystem::GetComponentMaxValue(const AttributeType attribute_type) const
{
    for (const std::unique_ptr<LifeComponent>& component : components)
    {
        if(component->GetAttributeType() == attribute_type)
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
        std::cerr << "    " << component->GetDisplayName() << ": " << component->GetValue() << "/" << component->GetMaxValue() << std::endl;
    }
}

