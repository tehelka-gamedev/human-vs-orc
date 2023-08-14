#pragma once
#include <memory>

namespace HumanVSOrc
{
class Unit;
 
 class UnitFactory
{
 public:
  static std::shared_ptr<Unit> CreateKnight();
  static std::shared_ptr<Unit> CreateOrc();
     
  
  
};
    
}
