#pragma once
#include "Attribute.h"


namespace HumanVSOrc
{
    /* AttributeGauge class
     * Attribute holding also a max value and several helper functions.
     * Used to manage attributes like health, mana, ... Anything like a health bar.
     * 
     */
    class AttributeGauge : public Attribute
    {
    public:
        AttributeGauge(AttributeType type, const std::string& name, float max_value);

        bool IsDepleted() const;
        bool IsFull();

        float GetMaxValue();
        float GetCurrentValue() const;

        // Increase or decrease the current value. Amount is supposed to be positive.
        void IncreaseCurrentValue(float amount);
        void DecreaseCurrentValue(float amount);

    private:
        float current_value = -1.0f;
    };
}
