#include "LifeComponent.h"

LifeComponent::LifeComponent(std::string name, float max_value): name(std::move(name)), value(max_value), max_value(max_value)
{}

bool LifeComponent::isDepleted() const
{
    return value <= 0;
}

bool LifeComponent::isFull() const
{
    return value >= max_value;
}

float LifeComponent::TakeDamage(const float damage)
{
    value -= damage;
    if (value < 0)
    {
        const float excess = -value;
        value = 0;
        return excess;
    }
    return 0;
}

float LifeComponent::GetValue() const
{
    return value;
}

float LifeComponent::GetMaxValue() const
{
    return max_value;
}

std::string LifeComponent::GetName() const
{
    return name;
}

void LifeComponent::SetValue(float new_value)
{
    value = new_value;
}

void LifeComponent::SetMaxValue(float new_max_value)
{
    max_value = new_max_value;
}

void LifeComponent::SetName(const std::string& new_name)
{
    name = new_name;
}
