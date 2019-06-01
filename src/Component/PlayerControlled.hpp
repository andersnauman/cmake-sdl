#ifndef COMPONENT_PLAYERCONTROLLED_H_
#define COMPONENT_PLAYERCONTROLLED_H_

#include <cstdint>
#include <map>

namespace Component {
class PlayerControlled {
    public:
        enum Action {
            up,
            down,
            left,
            right,
            fire,
            none,
        };
        PlayerControlled() {};
        ~PlayerControlled() {};
        void SetOwner(unsigned int entityId);
        unsigned int GetOwner();
        void Reset();
        void Initialize();
        void Update() {};

        Action GetAction(uint16_t scancode);

    private:
        unsigned long entity_id_;
        std::map<uint16_t, Action> keyMap; 
};
};

#endif // COMPONENT_PLAYERCONTROLLED_H_