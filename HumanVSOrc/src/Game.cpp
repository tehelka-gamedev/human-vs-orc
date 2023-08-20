#include "Game.h"

#include <iomanip>
#include <iostream>

#include "EquippableItem.h"
#include "EquippableItemFactory.h"
#include "Unit.h"
#include "UnitFactory.h"

namespace HumanVSOrc
{
    void Game::Init()
    {
        CreateUnits();
        CreateItems();

        // Give the sword to the knight
        unit_list[0]->Equip(item_list[0]);

        // Give the axe to the orc
        unit_list[1]->Equip(item_list[1]);
        
        unit_list[0]->SetTarget(unit_list[1]);
        unit_list[1]->SetTarget(unit_list[0]);
    
    }

    void Game::CreateUnits()
    {
        // Create two units
        unit_list.push_back(UnitFactory::CreateKnight());
        unit_list.push_back(UnitFactory::CreateOrc());

  
    }

    void Game::CreateItems()
    {
        // Create a sword for the knight and an axe for the orc
        item_list.push_back(EquippableItemFactory::CreateSword());
        item_list.push_back(EquippableItemFactory::CreateAxe());
    }

    Game::Game() : turn(0)
    {
    }

    Game::~Game()
    = default;

    void Game::Run()
    {
        PrintTitle();
        std::cout << std::fixed << std::setprecision(0);

        Init();

        while(!IsOver())
        {
            Update();
            std::cout.flush();
            std::cout << "Press Enter to continue to next turn";
            std::cin.ignore();
        }

        PrintEnd();
    
    }

    void Game::Update()
    {
        turn++;
        std::cout << " -- TURN " << turn << " -- " << std::endl;
    
        std::cout << std::endl << "Units status at the beginning of the turn:" << std::endl;

        // Display unit status
        for(const std::shared_ptr<Unit>& unit : unit_list)
        {
            unit->PrintInfo();
        }
        std::cout << std::endl;

        // Update all units
        for(const std::shared_ptr<Unit>& unit : unit_list)
        {
            unit->TickAllSkills();
            unit->TickAllBonuses();
            unit->TickAllStatusEffects();
        }

        // All units cast their skills
        for(const std::shared_ptr<Unit>& unit : unit_list)
        {
            unit->CastAllSkills();
        }

        // All units attack
        for(const std::shared_ptr<Unit>& unit : unit_list)
        {
            unit->Attack();
        }

        std::cout << std::endl;
        std::cout << std::endl;
    }

    void Game::PrintTitle() const
    {
        std::cout << R"(  _    _                             )" << "\n";
        std::cout << R"( | |  | |                            )" << "\n";
        std::cout << R"( | |__| |_   _ _ __ ___   __ _ _ __  )" << "\n";
        std::cout << R"( |  __  | | | | '_ ` _ \ / _` | '_ \ )" << "\n";
        std::cout << R"( | |  | | |_| | | | | | | (_| | | | |)" << "\n";
        std::cout << R"( |_|  |_|\__,_|_| |_| |_|\__,_|_| |_|)" << "\n";
        std::cout << R"( __      _______    ____             )" << "\n";
        std::cout << R"( \ \    / / ____|  / __ \            )" << "\n";
        std::cout << R"(  \ \  / / (___   | |  | |_ __ ___   )" << "\n";
        std::cout << R"(   \ \/ / \___ \  | |  | | '__/ __|  )" << "\n";
        std::cout << R"(    \  /  ____) | | |__| | | | (__   )" << "\n";
        std::cout << R"(     \/  |_____/   \____/|_|  \___|  )" << "\n";

        std::cout << std::endl;
    }

    void Game::PrintEnd() const
    {
        // Find the winner
        std::shared_ptr<Unit> winner = nullptr;
        for(const std::shared_ptr<Unit>& unit : unit_list)
        {
            if(unit->IsAlive())
            {
                winner = unit;
                break;
            }
        }

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << " -- GAME OVER -- " << std::endl;
        std::cout << "The winner is " << winner->GetName() << "!" << std::endl;
        std::cout << winner->GetName() << " status:" << std::endl;
        winner->PrintInfo();
        
    }

    bool Game::IsOver() const
    {
        // The game is over when one any unit is dead
        return std::any_of(unit_list.begin(), unit_list.end(), [](const std::shared_ptr<Unit>& unit) { return !unit->IsAlive(); });
    }
}
