#include "Equipment.h"

#include <iostream>

#include "EquippableItem.h"

namespace HumanVSOrc
{
    Equipment::Equipment() = default;

    Equipment::~Equipment() = default;

    std::shared_ptr<EquippableItem> Equipment::GetItem(Slot slot) const
    {
        return equipped_items[static_cast<int>(slot)];
    }

    void Equipment::EquipItem(std::shared_ptr<EquippableItem> item, Slot slot)
    {
        equipped_items[static_cast<int>(slot)] = item;
    }

    std::shared_ptr<EquippableItem> Equipment::UnequipSlot(Slot slot)
    {
        std::shared_ptr<EquippableItem> item = equipped_items[static_cast<int>(slot)];
        equipped_items[static_cast<int>(slot)] = nullptr;
        return item;
    }

    void Equipment::Print() const
    {   
        for (int i = 0; i < static_cast<int>(Slot::COUNT); ++i)
        {
            if (equipped_items[i] != nullptr)
            {
                std::cout << "Slot " << i << ": " << equipped_items[i]->GetName() << std::endl;
            }
        }
    }

    bool Equipment::IsSlotEquipped(Slot slot) const
    {
        return equipped_items[static_cast<int>(slot)] != nullptr;
    }
}
