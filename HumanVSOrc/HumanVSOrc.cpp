
#include <iostream>
#include <random>


#include "src/EquippableItem.h"
#include "src/Game.h"
#include "src/RandomGenerator.h"
#include "src/Unit.h"


int main(int argc, char* argv[])
{
    // Create a dummy unit
    std::shared_ptr<Unit> unit = std::make_shared<Unit>("Dummy");
    // Add Health and damage attributes to the units
    unit->AddLifeComponent(AttributeType::HEALTH, "Health", 100.0f);
    unit->AddLifeComponent(AttributeType::SHIELD, "Shield", 50.0f);
    unit->AddAttribute(AttributeType::DAMAGE, "Damage", 10.0f);

    // Create a dummy sword of type EquippableItem
    std::shared_ptr<EquippableItem> sword = std::make_shared<EquippableItem>("Sword",Equipment::Slot::WEAPON);
    
    // Add damage bonus to the sword
    sword->AddBonus(std::make_shared<Bonus>(10.0f, AttributeType::DAMAGE, Bonus::Type::RAW));

    unit->PrintInfo();
    // Equip the sword to the unit
    unit->Equip(sword);
    std::cerr << "-" << std::endl;
    unit->PrintInfo();
    
    // Initialize random device
    // std::random_device rd;
    // RandomGenerator::generator.seed(rd());
    //
    // Game game;
    //
    // game.Run();
    //
    // std::cout.flush();
    // std::cout << "Press Enter to Close";
    // std::cin.ignore();
    
    return 0;
}
