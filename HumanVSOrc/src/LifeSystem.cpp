#include "LifeSystem.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>

#include "Attribute.h"
#include "AttributeType.h"
#include "LifeComponent.h"
#include "Bonus.h"

namespace HumanVSOrc
{
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

    void LifeSystem::RemoveBonus(std::shared_ptr<Bonus>& bonus)
    {
        // Iterate over all components and remove the bonus from the first component that matches the bonus target attribute
        for(std::unique_ptr<LifeComponent>& component : components)
        {
            if(component->GetAttributeType() == bonus->GetTargetAttribute())
            {
                component->RemoveBonus(bonus);
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
        return std::numeric_limits<float>::quiet_NaN();
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
        return std::numeric_limits<float>::quiet_NaN();
    }

    std::shared_ptr<Attribute> LifeSystem::GetComponent(AttributeType attribute_type) const
    {
        // Iterate over all components and return the first component that matches the attribute type
        for (const std::unique_ptr<LifeComponent>& component : components)
        {
            if(component->GetAttributeType() == attribute_type)
            {
                return component->GetAttribute();
            }
        }
        return nullptr;
    }


    void LifeSystem::PrintComponents() const
    {
        std::cerr << "LifeSystem components:" << std::endl;
        for (const std::unique_ptr<LifeComponent>& component : components)
        {
            std::cerr << "    " << component->GetDisplayName() << ": " << component->GetValue() << "/" << component->GetMaxValue() << std::endl;
        }
    }

    
}
