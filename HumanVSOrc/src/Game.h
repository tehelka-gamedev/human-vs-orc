#pragma once
#include <memory>
#include <vector>

namespace HumanVSOrc
{
    class Game
    {
        // Attributes
    private:
        std::vector<std::shared_ptr<class Unit>> unit_list;

        int turn=0;

        void Init();
        void CreateUnits();

        void Update();
        void PrintTitle() const;

        bool IsOver();
    public:
        Game();
        ~Game();

        void Run();

    };

    inline bool Game::IsOver()
    {
        return turn >= 3;
    }
    
}
