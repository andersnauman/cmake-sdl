#ifndef COMPONENT_PLAYERCONTROLLED_H_
#define COMPONENT_PLAYERCONTROLLED_H_

#include <cstdint>

namespace Component {
class PlayerControlled {
    public:
        enum Action {
            left,
            right
        };
        PlayerControlled() {};
        ~PlayerControlled() {};
        void SetOwner(unsigned int entityId) {
            entity_id_ = entityId;
        };
        unsigned int GetOwner() {
            return entity_id_;
        };
        void Reset() {};
        void Initialize() {};
        Action GetAction(uint16_t scancode);

    private:
        unsigned long entity_id_;
        
};
};

#endif // COMPONENT_PLAYERCONTROLLED_H_