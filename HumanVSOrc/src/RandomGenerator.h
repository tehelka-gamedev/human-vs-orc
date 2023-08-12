#pragma once

#include <random>

namespace HumanVSOrc
{
    namespace RandomGenerator
    {
        inline std::default_random_engine generator;
        inline std::uniform_real_distribution<float> uniform(0.0, 1.0);

    }
}
