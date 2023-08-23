#pragma once
#include <memory>
#include <string>

#include "StatusEffectType.h"
#include "Skill/Command.h"

namespace HumanVSOrc
{
    
    namespace skills
    {
        class Command; // remove ?
    }
    
    class ITargetable;
    
    class StatusEffect
    {

    private:
        std::string name;
        int duration = -1; // -1 means infinite
        StatusEffectType type = StatusEffectType::NONE;

        std::unique_ptr<skills::Command> on_apply_command = nullptr;
        std::unique_ptr<skills::Command> on_update_command = nullptr;
        std::unique_ptr<skills::Command> on_remove_command = nullptr;
        
        
        std::weak_ptr<ITargetable> caster;
        std::weak_ptr<ITargetable> target;
    

    public:
        StatusEffect(std::string name, int duration = -1, StatusEffectType type = StatusEffectType::NONE);
        ~StatusEffect();

        // Reduce the duration by 1
        // And execute the on_update_command
        void Tick();

        // Called when the status effect is applied
        void OnApply() const;
        // Called when the status effect is over
        void OnRemove() const;
    
        
        bool IsOver() const;

        // Getters
        std::string GetName() const;
        int GetDuration() const; // should be time left ?
        StatusEffectType GetType() const;

        // Setters
        StatusEffect& SetOnApplyCommand(std::unique_ptr<skills::Command> command);
        StatusEffect& SetOnUpdateCommand(std::unique_ptr<skills::Command> command);
        StatusEffect& SetOnRemoveCommand(std::unique_ptr<skills::Command> command);
        StatusEffect& SetCaster(std::weak_ptr<ITargetable> caster_ptr);
        StatusEffect& SetTarget(std::weak_ptr<ITargetable> target_ptr);
        
        bool operator==(const StatusEffect& other) const;
    };
    
}
