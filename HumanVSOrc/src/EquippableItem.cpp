#include "EquippableItem.h"

#include "Bonus.h"

namespace HumanVSOrc
{
    EquippableItem::EquippableItem(std::string name, Equipment::Slot slot) : name(std::move(name)), slot(slot)
    {
    }

    EquippableItem::~EquippableItem()
    = default;

    void EquippableItem::AddBonus(std::shared_ptr<Bonus> bonus)
    {
        bonuses.push_back(std::move(bonus));
    }

    std::string EquippableItem::GetName() const
    {
        return name;
    }

    Equipment::Slot EquippableItem::GetSlot() const
    {
        return slot;
    }

    std::vector<std::shared_ptr<Bonus>> EquippableItem::GetBonuses() const
    {
        return bonuses;
    }

    const std::vector<std::shared_ptr<Bonus>>& EquippableItem::GetBonusesByReference() const
    {
        return bonuses;
    }
    
}
