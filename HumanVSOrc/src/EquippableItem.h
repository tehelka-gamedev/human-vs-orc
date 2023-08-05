#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Equipment.h"

class EquippableItem
{
    std::string name = "Unnamed item";
    Equipment::Slot slot;
    std::vector<std::shared_ptr<class Bonus>> bonuses; // list of bonuses provided by the item
public:
    EquippableItem(std::string name, Equipment::Slot slot);
    ~EquippableItem();

    void AddBonus(std::shared_ptr<class Bonus> bonus);

    // Getters
    std::string GetName() const;
    Equipment::Slot GetSlot() const;
    std::vector<std::shared_ptr<class Bonus>> GetBonuses() const;
    const std::vector<std::shared_ptr<class Bonus>>& GetBonusesByReference() const;
};
