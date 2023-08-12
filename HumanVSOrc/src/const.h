#pragma once

// Game constants are written here
// Should be moved to a config file later
namespace HumanVSOrc
{
    namespace GameConstants
    {
        //// Units stats
        enum class KnightConstants
        {
            BASE_HEALTH = 20,
            BASE_SHIELD = 50,
            BASE_DAMAGE = 5, // this is raw damage without weapon
        };

        enum class OrcConstants
        {
            BASE_HEALTH = 60,
            BASE_DAMAGE = 8,
        };

        enum class PaladinConstants
        {
            BASE_HEALTH = 30,
            BASE_SHIELD = 50,
            BASE_DAMAGE = 0,
        };

        //// Weapons stats
        constexpr float SWORD_DAMAGE = 5;
        constexpr float AXE_DAMAGE = 8;
        constexpr float HAMMER_DAMAGE = 3;


        //// Skills
        namespace Skills
        {
            enum class Charge
            {
                COOLDOWN = 3,
                SUCCESS_RATE = 60, // 60%
                DURATION = 1,
            };

            enum class Stun
            {
                COOLDOWN = 5,
                SUCCESS_RATE = 100, // 20%
                DURATION = 1,
            };
        }
 
    }
}
