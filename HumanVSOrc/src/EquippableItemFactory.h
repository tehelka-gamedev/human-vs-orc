#pragma once

#include <memory>

namespace HumanVSOrc
{
    class EquippableItem;
    
    class EquippableItemFactory
    {
    public:
        static std::shared_ptr<EquippableItem> CreateSword();
        static std::shared_ptr<EquippableItem> CreateAxe();
    
    };
    
}
