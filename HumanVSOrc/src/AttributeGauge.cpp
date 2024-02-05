#include "AttributeGauge.h"

namespace HumanVSOrc
{
    AttributeGauge::AttributeGauge(AttributeType type, const std::string& name, float max_value) :
        Attribute(type, name, max_value), current_value(max_value)
    {
    }

    bool AttributeGauge::IsDepleted() const
    {
        return current_value <= 0;
    }

    bool AttributeGauge::IsFull()
    {
        return current_value >= GetValue();
    }

    float AttributeGauge::GetMaxValue()
    {
        return GetValue();
    }

    float AttributeGauge::GetCurrentValue() const
    {
        return current_value;
    }

    void AttributeGauge::IncreaseCurrentValue(float amount)
    {
        current_value += amount;
        if (current_value > GetMaxValue())
        {
            current_value = GetMaxValue();
        }
    }

    void AttributeGauge::DecreaseCurrentValue(float amount)
    {
        current_value -= amount;
        if (current_value < 0)
        {
            current_value = 0;
        }
    }
}
