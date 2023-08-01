#pragma once
#include <string>

/*
    LifeComponent class
    This class is responsible for managing a "life" bar
    This is used to have modular life components like health, shield, or whatever.
*/
class LifeComponent
{
    // Attributes
private:
    std::string name;
    float value = 0;
    float max_value = 0;
    
    
public:
    LifeComponent(std::string name, float max_value);

    bool isDepleted() const;
    bool isFull() const;

    // Take damage to this life component and return the amount of damage in excess
    float TakeDamage(float damage);
    
    // Getters
    float GetValue() const;
    float GetMaxValue() const;
    std::string GetName() const;

    // Setters
    void SetValue(float new_value);
    void SetMaxValue(float new_max_value);
    void SetName(const std::string& new_name);
};
