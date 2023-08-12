
#include <iostream>
#include <random>


#include "src/EquippableItem.h"
#include "src/Game.h"
#include "src/RandomGenerator.h"
#include "src/Unit.h"


int main(int argc, char* argv[])
{
    // // Create a dummy unit
    // std::shared_ptr<Unit> unit = std::make_shared<Unit>("Dummy");
    // // Add Health and damage attributes to the units
    // unit->AddLifeComponent(AttributeType::HEALTH, "Health", 100.0f);
    // unit->AddLifeComponent(AttributeType::SHIELD, "Shield", 50.0f);
    // unit->AddAttribute(AttributeType::DAMAGE, "Damage", 10.0f);
    //
    // // Create a dummy sword of type EquippableItem
    // std::shared_ptr<EquippableItem> sword = std::make_shared<EquippableItem>("Sword",Equipment::Slot::WEAPON);
    //
    // // Add damage bonus to the sword
    // sword->AddBonus(std::make_shared<Bonus>(10.0f, AttributeType::DAMAGE, Bonus::Type::RAW));
    //
    // unit->PrintInfo();
    // // Equip the sword to the unit
    // unit->Equip(sword);
    // std::cerr << "-" << std::endl;
    // unit->PrintInfo();
    //
    //Initialize random device
    std::random_device rd;
    HumanVSOrc::RandomGenerator::generator.seed(rd());

    // Later to add colors...
    // std::cout << "\033[37;42m 20/20             \033[0m\n";
    HumanVSOrc::Game game;
    
    game.Run();
    
    std::cout.flush();
    std::cout << "Press Enter to Close";
    std::cin.ignore();
    
    return 0;
}
