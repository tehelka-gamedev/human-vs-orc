#include "LifeSystem.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>

#include "Attribute.h"
#include "AttributeType.h"
#include "AttributeGauge.h"

namespace HumanVSOrc
{
    LifeSystem::LifeSystem()
    = default;

    LifeSystem::~LifeSystem()
    = default;

    bool LifeSystem::HasComponent(AttributeType attribute_type) const
    {
        return std::any_of(
            components.begin(),
            components.end(),
            [attribute_type](const std::weak_ptr<AttributeGauge>& component)
            {
                if (component.expired())
                {
                    return false;
                }
                return component.lock()->GetAttributeType() == attribute_type;
            }
        );
    }

    // Not needed ?
    /*
    void LifeSystem::Tick()
    {
        for (std::unique_ptr<LifeComponent>& component : components)
        {
            component->Tick();
        }
    }
    */
    
    void LifeSystem::TakeDamage(float damage)
    {
        float remaining_damage = damage;
        for (auto it = components.rbegin(); it != components.rend(); ++it)
        {
            std::weak_ptr<AttributeGauge>& component = *it;
            if (component.expired())
            {
                continue; // Skip expired components, just in case
            }
            std::shared_ptr<AttributeGauge> component_shared = component.lock();

            // If the component is already depleted, skip it
            if (component_shared->IsDepleted())
            {
                continue;
            }
            // If the component can absorb all the damage, absorb it and skip the rest
            if (component_shared->GetCurrentValue() >= remaining_damage)
            {
                component_shared->DecreaseCurrentValue(remaining_damage);
                break;
            }
            // Otherwise, the component will be depleted, and the remaining damage will be decreased
            remaining_damage -= component_shared->GetCurrentValue();
            component_shared->DecreaseCurrentValue(component_shared->GetCurrentValue());
            
        }
    }

    bool LifeSystem::IsDepleted() const
    {
        return std::all_of(
            components.begin(),
            components.end(),
            [](const std::weak_ptr<AttributeGauge>& component)
            {
                if (component.expired())
                {
                    return true;
                }
                return component.lock()->IsDepleted();
            }
        );
    }

    void LifeSystem::AddComponent(const std::shared_ptr<AttributeGauge>& component)
    {
        components.push_back(component);
    }
    

    float LifeSystem::GetComponentValue(const AttributeType attribute_type) const
    {   
        for (const std::weak_ptr<AttributeGauge>& component : components)
        {
            if (component.expired())
            {
                continue;
            }
            const std::shared_ptr<AttributeGauge> component_shared = component.lock();
            if(component_shared->GetAttributeType() == attribute_type)
            {
                return component_shared->GetCurrentValue();
            }
        }
        return std::numeric_limits<float>::quiet_NaN();
    }

    float LifeSystem::GetComponentMaxValue(const AttributeType attribute_type) const
    {
        for (const std::weak_ptr<AttributeGauge>& component : components)
        {
            if (component.expired())
            {
                continue;
            }
            const std::shared_ptr<AttributeGauge> component_shared = component.lock();
            if(component_shared->GetAttributeType() == attribute_type)
            {
                return component_shared->GetMaxValue();
            }
        }
        return std::numeric_limits<float>::quiet_NaN();
    }
    


    void LifeSystem::PrintComponents() const
    {
        std::cerr << "LifeSystem components:" << std::endl;
        for (const std::weak_ptr<AttributeGauge>& component : components)
        {
            if (component.expired())
            {
                std::cerr << "  - expired" << std::endl;
                continue;
            }
            const std::shared_ptr<AttributeGauge> component_shared = component.lock();
            std::cerr << "  - " << component_shared->GetDisplayName() << ": " << component_shared->GetCurrentValue() << " / " << component_shared->GetMaxValue() << std::endl;
        }
    }

    
}
