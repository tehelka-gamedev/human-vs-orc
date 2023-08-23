#pragma once
#include "Attribute.h"

namespace HumanVSOrc
{
    /* DependentAttribute is an attribute that depends on other attributes to compute its final value.
     The DependantAttribute computes first its final value, then gain a bonus of X for each interval of Y of the final value of each of its dependencies.

     e.g. : CRITICAL_CHANCE depends on AGILITY
        CRITICAL_CHANCE gains +1 for each interval of 5 of AGILITY
        
        so if CRITICAL_CHANCE base value is 1 and AGILITY final value is 12, CRITICAL_CHANCE final value is 3 (1 + 2)
     */
    class DependentAttribute : public Attribute
    {
    public:
        struct Dependency
        {
            std::weak_ptr<Attribute> attribute;
            float bonus_per_interval;
            float interval;

            Dependency(std::weak_ptr<Attribute> attribute, float bonus_per_interval, float interval);
        };
        
    private:
        std::vector<Dependency> dependencies;
        
        float CalculateFinalValue() override;

    public:
        DependentAttribute(AttributeType type, const std::string& name, float value, const std::vector<Dependency>& dependencies);

        // Override the mother class GetValue() method to recalculate the final value all the time.
        // This is because the final value of a DependentAttribute depends on the final value of other attributes.
        // This would require to implement a system like the Observer pattern to notify the DependentAttribute when the
        // final value of one of its dependencies changes.
        float GetValue() override; 
        
    };
    
}
