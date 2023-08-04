
#include <iostream>

#include "src/Attribute.h"
#include "src/Bonus.h"
#include "src/Unit.h"
#include "src/Weapon.h"


int main(int argc, char* argv[])
{
    // // Create an attribute
    // Attribute attribute(10);
    // // Create a weapon
    // Weapon sword("Sword", 5);
    // // Add the weapon bonus to the attribute
    // attribute.AddRawBonus(sword.GetDamageBonus());
    // std::cout << "on weapon : " << sword.GetDamageBonus().get() << std::endl;
    // // Print the attribute value
    // std::cout << attribute.GetValue() << std::endl;
    // std::cout << "Hello world z!" << std::endl;

    // Create a test_unit
    Unit test_unit("dummy");
    
    test_unit.AddLifeComponent(AttributeType::HEALTH,  "health", 100);
    test_unit.TakeDamage(75);
    std::cout << "1" << std::endl;
    std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(50.0f, 0.0f, AttributeType::HEALTH, Bonus::Type::RAW);
    std::cout << "2" << std::endl;
    test_unit.AddBonus(bonus);
    std::cout << "3" << std::endl;
    std::cout << "unit has " << test_unit.GetLifeComponentMaxValue(AttributeType::HEALTH) << " health" << std::endl;

    
    return 0;
}
