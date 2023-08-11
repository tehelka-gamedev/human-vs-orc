#include "gtest/gtest.h"

#include "../src/Unit.h"
#include "../src/EquippableItem.h"
#include "../src/Equipment.h"

class TestEquipment : public ::testing::Test
{
protected:
    void SetUp() override
    {
        unit.SetName("dummy");
        unit.AddLifeComponent(AttributeType::HEALTH, "health", 100);
        unit.AddAttribute(AttributeType::DAMAGE, "damage", 0.0f);
        unit.AddAttribute(AttributeType::ARMOR, "armor", 0.0f);

        // Sword with 10 damage bonus
        sword.AddBonus(std::make_shared<Bonus>(10.0f, AttributeType::DAMAGE, Bonus::Type::RAW));

        // Shield with 10 armor bonus
        shield.AddBonus(std::make_shared<Bonus>(10.0f, AttributeType::ARMOR, Bonus::Type::RAW));

        // Helmet with 5 armor bonus and 5 health bonus
        helmet.AddBonus(std::make_shared<Bonus>(5.0f, AttributeType::ARMOR, Bonus::Type::RAW));
        helmet.AddBonus(std::make_shared<Bonus>(5.0f, AttributeType::HEALTH, Bonus::Type::RAW));

        // Chest with 10 armor bonus and 10 health bonus
        chest.AddBonus(std::make_shared<Bonus>(10.0f, AttributeType::ARMOR, Bonus::Type::RAW));
        chest.AddBonus(std::make_shared<Bonus>(10.0f, AttributeType::HEALTH, Bonus::Type::RAW));

        // Boots with 5 armor bonus
        boots.AddBonus(std::make_shared<Bonus>(5.0f, AttributeType::ARMOR, Bonus::Type::RAW));

        // Gloves with 3 armor bonus
        gloves.AddBonus(std::make_shared<Bonus>(3.0f, AttributeType::ARMOR, Bonus::Type::RAW));

        // Ring with 10% health bonus
        ring.AddBonus(std::make_shared<Bonus>(0.0f, 0.10f, AttributeType::HEALTH, Bonus::Type::RAW));

        // Necklace with 10% damage bonus
        necklace.AddBonus(std::make_shared<Bonus>(0.0f, 0.10f, AttributeType::DAMAGE, Bonus::Type::RAW));

        // Belt with 5 armor and 10% armor bonus
        belt.AddBonus(std::make_shared<Bonus>(5.0f, 0.10f, AttributeType::ARMOR, Bonus::Type::RAW));
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }

    Unit unit{"dummy"};
    // One dummy item in each slot
    EquippableItem sword{"sword", Equipment::Slot::WEAPON};
    EquippableItem shield{"shield", Equipment::Slot::SHIELD};
    EquippableItem helmet{"helmet", Equipment::Slot::HELMET};
    EquippableItem chest{"chest", Equipment::Slot::CHEST};
    EquippableItem boots{"boots", Equipment::Slot::BOOTS};
    EquippableItem gloves{"gloves", Equipment::Slot::GLOVES};
    EquippableItem ring{"ring", Equipment::Slot::RING};
    EquippableItem necklace{"necklace", Equipment::Slot::NECKLACE};
    EquippableItem belt{"belt", Equipment::Slot::BELT};
    
};

// Test a dummy unit equipping a sword and unequipping it
TEST_F(TestEquipment, TestEquipSword)
{
    // Equip a sword
    // Check that the unit has the sword +10 damage
    const float damage = unit.GetAttributeValue(AttributeType::DAMAGE);
    
    unit.Equip(std::make_shared<EquippableItem>(sword));

    EXPECT_FLOAT_EQ(unit.GetAttributeValue(AttributeType::DAMAGE), damage + 10.0f);

    unit.Unequip(Equipment::Slot::WEAPON);
    EXPECT_FLOAT_EQ(unit.GetAttributeValue(AttributeType::DAMAGE), damage);
}

// Test a dummy unit equipping a shield and unequipping it
TEST_F(TestEquipment, TestEquipShield)
{
    // Equip a shield
    // Check that the unit has the shield +10 armor
    const float armor = unit.GetAttributeValue(AttributeType::ARMOR);
    
    unit.Equip(std::make_shared<EquippableItem>(shield));

    EXPECT_FLOAT_EQ(unit.GetAttributeValue(AttributeType::ARMOR), armor + 10.0f);

    unit.Unequip(Equipment::Slot::SHIELD);
    EXPECT_FLOAT_EQ(unit.GetAttributeValue(AttributeType::ARMOR), armor);
}

// Test a dummy unit equipping an item in each slot and check that the bonuses are applied
TEST_F(TestEquipment, TestEquipAll)
{
    const float damage = unit.GetAttributeValue(AttributeType::DAMAGE);
    const float armor = unit.GetAttributeValue(AttributeType::ARMOR);
    const float health = unit.GetLifeComponentMaxValue(AttributeType::HEALTH);
    
    unit.Equip(std::make_shared<EquippableItem>(sword));
    unit.Equip(std::make_shared<EquippableItem>(shield));
    unit.Equip(std::make_shared<EquippableItem>(helmet));
    unit.Equip(std::make_shared<EquippableItem>(chest));
    unit.Equip(std::make_shared<EquippableItem>(boots));
    unit.Equip(std::make_shared<EquippableItem>(gloves));
    unit.Equip(std::make_shared<EquippableItem>(ring));
    unit.Equip(std::make_shared<EquippableItem>(necklace));
    unit.Equip(std::make_shared<EquippableItem>(belt));

    // gain +10 damage, then +10% damage = +11 damage
    // gain +38 armor, then +10% armor = +41.8 armor
    // gain +15 health, then +10% health to the base 100+15 health = +26.5 health
    

    EXPECT_FLOAT_EQ(unit.GetAttributeValue(AttributeType::DAMAGE), damage + 11.0f);
    EXPECT_FLOAT_EQ(unit.GetAttributeValue(AttributeType::ARMOR), armor + 41.8f);
    EXPECT_FLOAT_EQ(unit.GetLifeComponentMaxValue(AttributeType::HEALTH), health + 26.5f);

    unit.Unequip(Equipment::Slot::WEAPON);
    unit.Unequip(Equipment::Slot::SHIELD);
    unit.Unequip(Equipment::Slot::HELMET);
    unit.Unequip(Equipment::Slot::CHEST);
    unit.Unequip(Equipment::Slot::BOOTS);
    unit.Unequip(Equipment::Slot::GLOVES);
    unit.Unequip(Equipment::Slot::RING);
    unit.Unequip(Equipment::Slot::NECKLACE);
    unit.Unequip(Equipment::Slot::BELT);

    EXPECT_FLOAT_EQ(unit.GetAttributeValue(AttributeType::DAMAGE), damage);
    EXPECT_FLOAT_EQ(unit.GetAttributeValue(AttributeType::ARMOR), armor);
    EXPECT_FLOAT_EQ(unit.GetLifeComponentMaxValue(AttributeType::HEALTH), health);
}

// Dummy test method
// TEST_F(TestEquipment, TestDummy)
// {
//     EquippableItem op_sword{"sword", Equipment::Slot::WEAPON};
//     EXPECT_EQ(1, 1);
// }