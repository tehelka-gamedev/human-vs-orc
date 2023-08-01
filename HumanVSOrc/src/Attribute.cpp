#include "Attribute.h"

#include <iostream>

#include "Bonus.h"

float Attribute::CalculateFinalValue()
{
    final_value = base_value;

    // All raw bonuses are computed and added to the base attribute value.
    float raw_multiplier = 0;
    for (std::shared_ptr<Bonus>& b: raw_bonus)
    {
        final_value += b->GetValue();
        raw_multiplier += b->GetMultiplier();
    }

    // add the raw multiplier bonus to the buffed base attribute value
    final_value *= (1 + raw_multiplier);

    // All final bonuses are computed and added to the final attribute value.
    float final_multiplier = 0;
    for (std::shared_ptr<Bonus>& b: final_bonus)
    {
        final_value += b->GetValue();
        final_multiplier += b->GetMultiplier();
    }

    // add the final multiplier bonus to the buffed base attribute value
    final_value *= (1 + final_multiplier);
    
    is_dirty = false;
    return final_value;
}

Attribute::Attribute(float value) : base_value(value)
{
    final_value = CalculateFinalValue();
}

Attribute::~Attribute()
= default;

void Attribute::AddRawBonus(const std::shared_ptr<Bonus>& bonus)
{
    raw_bonus.push_back(bonus);
    // print the address of the newly created bonus
    std::cout << "Bonus added : " << raw_bonus.back().get() << std::endl;
    is_dirty = true;
}

void Attribute::AddFinalBonus(const std::shared_ptr<Bonus>& bonus)
{
    final_bonus.push_back(bonus);
    is_dirty = true;
}

void Attribute::RemoveRawBonus(std::shared_ptr<Bonus>& bonus)
{
    auto it = std::remove_if(raw_bonus.begin(),
        raw_bonus.end(),
        [&bonus](const std::shared_ptr<Bonus>& b) { return b.get() == bonus.get(); }
        );
    if(it != raw_bonus.end())
    {
        raw_bonus.erase(it);
        is_dirty = true;
    }
}
//std::make_unique<Bonus>(bonus)

void Attribute::RemoveFinalBonus(std::shared_ptr<Bonus>& bonus)
{
    auto it = std::remove_if(final_bonus.begin(),
        final_bonus.end(),
        [&bonus](const std::shared_ptr<Bonus>& b) { return b.get() == bonus.get(); }
        );
    if(it != final_bonus.end())
    {
        final_bonus.erase(it);
        is_dirty = true;
    }
}

void Attribute::Tick()
{
    for (std::shared_ptr<Bonus>& b: raw_bonus)
    {
        b->Tick();
    }
    // Remove all bonus that are over
    auto it = std::remove_if(
        raw_bonus.begin(),
        raw_bonus.end(),
        [](const std::shared_ptr<Bonus>& b) { return b->IsOver(); });
    // Set to dirty if some bonus were removed
    if (it != raw_bonus.end())
    {
        is_dirty = true;
    }
    raw_bonus.erase(it,  raw_bonus.end());

    for (std::shared_ptr<Bonus>& b: raw_bonus)
    {
        b->Tick();
    }
    // Remove all bonus that are over
    it = std::remove_if(
        final_bonus.begin(),
        final_bonus.end(),
        [](const std::shared_ptr<Bonus>& b) { return b->IsOver(); });
    // Set to dirty if some bonus were removed
    if (it != final_bonus.end())
    {
        is_dirty = true;
    }
    final_bonus.erase(it, final_bonus.end());

    
}

float Attribute::GetValue()
{
    if (is_dirty)
    {
        final_value = CalculateFinalValue();
    }
    return final_value;
}

void Attribute::SetBaseValue(float new_value)
{
    base_value = new_value;
}
