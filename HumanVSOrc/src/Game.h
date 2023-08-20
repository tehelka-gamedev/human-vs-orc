#pragma once
#include <algorithm>
#include <memory>
#include <vector>


namespace HumanVSOrc
{
    class Unit;
    class EquippableItem;
    class Game
    {
        // Attributes
    private:
        std::vector<std::shared_ptr<Unit>> unit_list;
        std::vector<std::shared_ptr<EquippableItem>> item_list;

        int turn=0;

        void Init();
        void CreateUnits();
        void CreateItems();
        
        void Update();
        void PrintTitle() const;
        void PrintEnd() const;

        bool IsOver() const;
    public:
        Game();
        ~Game();

        void Run();

    };
    
}
