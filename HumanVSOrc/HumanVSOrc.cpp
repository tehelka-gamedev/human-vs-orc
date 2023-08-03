
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

    // Create a unit
    Unit test_unit("dummy");
    // Give it health
    test_unit.AddLifeComponent("health", 100);
    // Print its info
    test_unit.PrintInfo();
    
    return 0;
}
