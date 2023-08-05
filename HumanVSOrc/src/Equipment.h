#pragma once
#include <array>
#include <memory>

// Class managing a unit's equipment
class Equipment
{
public:
    // Equipment slots enumeration
    enum class Slot
    {
        WEAPON,
        ARMOR,
        SHIELD,
        HELMET,
        BOOTS,
        GLOVES,
        RING,
        NECKLACE,
        BELT,
        COUNT // number of slots, this is not a slot! Must be last!
    };
    
    //  Attributes
private:
    std::array<std::shared_ptr<class EquippableItem>, static_cast<int>(Slot::COUNT)> equipped_items;
    
    
public:
    Equipment();
    ~Equipment();
    
    // Getters
    std::shared_ptr<class EquippableItem> GetItem(Slot slot) const;
    
    // Setters
    void EquipItem(std::shared_ptr<EquippableItem> item, Slot slot);
    
    // Methods
    void Print() const;
};
