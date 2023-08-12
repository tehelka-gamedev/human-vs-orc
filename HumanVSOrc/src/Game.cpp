#include "Game.h"

#include <iomanip>
#include <iostream>

#include "Unit.h"
#include "const.h"
#include "Skill/SkillFactory.h"
#include "Skill/Skill.h"

void Game::Init()
{
    CreateUnits();
    unit_list[0]->SetTarget(unit_list[1]);
    unit_list[1]->SetTarget(unit_list[0]);
    
}

void Game::CreateUnits()
{
    // Create two units
    unit_list.push_back(std::make_shared<Unit>("Human"));
    unit_list.push_back(std::make_shared<Unit>("Orc"));

    // Add Health and damage attributes to the units
    unit_list[0]->AddLifeComponent(AttributeType::HEALTH, "Health", static_cast<float>(GameConstants::KnightConstants::BASE_HEALTH));
    unit_list[0]->AddLifeComponent(AttributeType::SHIELD, "Shield", static_cast<float>(GameConstants::KnightConstants::BASE_SHIELD));
    unit_list[0]->AddAttribute(AttributeType::DAMAGE, "Damage", static_cast<float>(GameConstants::KnightConstants::BASE_DAMAGE));

    unit_list[1]->AddLifeComponent(AttributeType::HEALTH, "Health", static_cast<float>(GameConstants::OrcConstants::BASE_HEALTH));
    unit_list[1]->AddAttribute(AttributeType::DAMAGE, "Damage", static_cast<float>(GameConstants::OrcConstants::BASE_DAMAGE));

    // Add skills to the units
    // Charge to the human
    // and Stun to the orc
    unit_list[0]->AddSkill(skills::SkillFactory::CreateChargeSkill());
    unit_list[1]->AddSkill(skills::SkillFactory::CreateStunSkill());
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
