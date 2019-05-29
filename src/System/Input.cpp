#include <cstdint>
#include <iostream>

#include "Component/PlayerControlled.hpp"
#include "Core/Unique.hpp"
#include "Manager/Component.hpp"

#include "Input.hpp"

namespace System {
void Input::SetKeyboardEvent(uint16_t scancode, uint8_t state, uint8_t repeat) {
    // State, 0 = released, 1 = pressed
    if(state == KEY_PRESSED) {
        std::vector<Component::PlayerControlled> a = {};
        Core::Unique<Manager::Component<Component::PlayerControlled>>::GetInstance().GetAllActive(a);
        for(auto &obj : a) {
            Component::PlayerControlled::Action action = obj.GetAction(scancode);
            switch (action) {
                case Component::PlayerControlled::left:
                    printf("Moving left\n");
            }
        }
        printf("Pressed keyboard-key: %i\n", scancode);
    } else if(state == KEY_RELEASED) {
        printf("Released keyboard-key %i\n", scancode);
    }
}
void Input::SetMouseEvent(uint8_t button, uint8_t state, uint8_t clicks, glm::vec2 pos) {
    // State, 0 = released, 1 = pressed
    if(state == KEY_PRESSED) {
        printf("Pressed mouse button: %i at X:%f Y:%f\n", button, pos.x, pos.y);
    } else if(state == KEY_RELEASED) {
        printf("Released mouse button: %i at X:%f Y:%f\n", button, pos.x, pos.y);
    }
}
};