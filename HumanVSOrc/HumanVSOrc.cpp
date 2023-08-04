
#include <iostream>
#include <random>


#include "src/Game.h"
#include "src/RandomGenerator.h"



int main(int argc, char* argv[])
{
    // Initialize random device
    std::random_device rd;
    RandomGenerator::generator.seed(rd());

    Game game;

    game.Run();
    
    std::cout.flush();
    std::cout << "Press Enter to Close";
    std::cin.ignore();
    
    return 0;
}
