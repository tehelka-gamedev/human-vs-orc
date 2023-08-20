#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Equipment.h"

namespace HumanVSOrc
{
    class Bonus;
    
    class EquippableItem
    {
        std::string name = "Unnamed item";
        Equipment::Slot slot;
        std::vector<std::shared_ptr<Bonus>> bonuses; // list of bonuses provided by the item
    public:
        EquippableItem(std::string name, Equipment::Slot slot);
        ~EquippableItem();

        void AddBonus(std::shared_ptr<Bonus> bonus);

        // Getters
        std::string GetName() const;
        Equipment::Slot GetSlot() const;
        std::vector<std::shared_ptr<Bonus>> GetBonuses() const;
        const std::vector<std::shared_ptr<Bonus>>& GetBonusesByReference() const;
    };
    
}
