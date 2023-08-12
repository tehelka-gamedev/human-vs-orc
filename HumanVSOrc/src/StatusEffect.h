#pragma once
#include <memory>
#include <string>

namespace HumanVSOrc
{
    
    namespace skills
    {
        class Command;
    }
    
    class ITargetable;
    
    class StatusEffect
    {
    public:
        enum class Type
        {
            NONE,
            STUNNED,
            BLEEDING,
        };

    private:
        std::string name;
        int duration = -1; // -1 means infinite
        Type type = Type::NONE;
        std::unique_ptr<skills::Command> on_update_command = nullptr;

        // May add a on_apply_command and on_remove_command later

        // Note: the caster and target are not used in the current implementation
        // TODO: define these attributes
        std::weak_ptr<ITargetable> caster;
        std::weak_ptr<ITargetable> target;
    

    public:
        StatusEffect(std::string name, int duration=-1, Type type=Type::NONE, std::unique_ptr<skills::Command> on_update_command=nullptr);

        ~StatusEffect();

        // Reduce the duration by 1
        // And execute the on_update_command
        void Tick();
    
        
        bool IsOver() const;

        // Getters
        std::string GetName() const;
        int GetDuration() const; // should be time left ?
        Type GetType() const;

        bool operator==(const StatusEffect& other) const;
    };
    
}
