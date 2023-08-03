#pragma once
#include <string>

#include "Bonus.h"
#include "BonusType.h"
#include "LifeSystem.h"

class Unit
{
    // Attributes
private:
    std::string name;
    std::unique_ptr<LifeSystem> life_system;
    // might add a list of Attributes later
    
public:
    explicit Unit(std::string name);
    ~Unit();


    void AddLifeComponent(const std::string& component_name, float max_value) const;

    void AddBonus(const std::shared_ptr<Bonus>& bonus);
    
    void TakeDamage(float amount) const;

    bool IsAlive() const;
    
    
    // Getters
    std::string GetName() const;
    float GetLifeComponentValue(const std::string& component_name) const;
    float GetLifeComponentMaxValue(const std::string& component_name) const;
    
    // Setters
    void SetName(const std::string& new_name);

    // Debug function to print the unit info
    void PrintInfo() const;
};
