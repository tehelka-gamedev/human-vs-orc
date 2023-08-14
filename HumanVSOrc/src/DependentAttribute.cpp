#include "DependentAttribute.h"

#include <iostream>
#include <utility>

namespace HumanVSOrc
{
    DependentAttribute::Dependency::Dependency(std::weak_ptr<Attribute> attribute, float bonus_per_interval,
        float interval) : attribute(std::move(attribute)), bonus_per_interval(bonus_per_interval), interval(interval)
    {
    }

    float DependentAttribute::CalculateFinalValue()
    {
        // Compute the final value of the attribute without the bonus from the dependencies (using the mother class method)
        final_value = Attribute::CalculateFinalValue();

        // Add the bonus from the dependencies
        for (Dependency& d: dependencies)
        {
            if(d.interval == 0)
            {
                std::cout << "Attribute " << display_name << " has a dependency with an interval of 0\n";
                continue;
            }
            
            std::shared_ptr<Attribute> attribute = d.attribute.lock();
            if (attribute == nullptr)
            {
                std::cout << "Attribute " << display_name << " has a dependency on a null attribute\n";
                continue;
            }
            
            // Get the final value of the dependency
            float dependency_final_value = attribute->GetValue();
            // Compute the number of intervals (rounded down)
            const float intervals = std::floor(dependency_final_value / d.interval);
            // Add the bonus
            final_value += d.bonus_per_interval * intervals;
        }
        
        return final_value;
    }

    DependentAttribute::DependentAttribute(AttributeType type, const std::string& name, float value,
                                          std::vector<Dependency>& dependencies) : Attribute(type, name, value), dependencies(dependencies)
    {
    }

    float DependentAttribute::GetValue()
    {
        is_dirty = true;
        return Attribute::GetValue();
    }
}
