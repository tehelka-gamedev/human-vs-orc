#include "LifeComponent.h"

#include "Bonus.h"

LifeComponent::LifeComponent(AttributeType attribute_type, std::string name, float max_value): value(max_value), max_value(attribute_type, std::move(name), max_value)
{}

bool LifeComponent::IsDepleted() const
{
    return value <= 0;
}

bool LifeComponent::IsFull()
{
    return value >= max_value.GetValue();
}

void LifeComponent::AddBonus(const std::shared_ptr<Bonus>& bonus)
{
    // Unsure yet how to handle the change of current life...
    //const float previous_max_value = max_value.GetValue();
    max_value.AddBonus(bonus);
    //value += max_value.GetValue() - previous_max_value;
}

void LifeComponent::Tick()
{
    // Might add health regen here ?
    max_value.Tick();
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

float LifeComponent::GetMaxValue()
{
    return max_value.GetValue();
}

std::string LifeComponent::GetDisplayName() const
{
    return max_value.GetDisplayName();
}

AttributeType LifeComponent::GetAttributeType() const
{
    return max_value.GetAttributeType();
}

void LifeComponent::SetValue(float new_value)
{
    value = new_value;
}

void LifeComponent::SetMaxValue(float new_max_value)
{
    max_value.SetBaseValue(new_max_value);
}

