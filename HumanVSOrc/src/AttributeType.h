#pragma once

namespace HumanVSOrc
{
    enum class AttributeType
    {
        HEALTH,
        SHIELD, // consist in a shield that absorb damage before health
        DAMAGE,
        ARMOR, // defense against physical damage

        AGILITY, // just a regular attribute boosting CRITICAL_CHANCE
        // Attributes supposed to depend on other attributes
        CRITICAL_CHANCE, // chance to deal a critical hit, boosted by AGILITY
    };
    
}
