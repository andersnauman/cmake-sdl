#include <cstdint>
#include <iostream>

// Global non-standard headers
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "Component/PlayerControlled.hpp"
#include "Component/Position.hpp"
#include "Core/Unique.hpp"
#include "Manager/Component.hpp"

#include "Input.hpp"

namespace System {
void Input::Update() {
    std::vector<Component::PlayerControlled> selected = {};
    Core::Unique<Manager::Component<Component::PlayerControlled>>::GetInstance().GetAllActive(selected);
    for(auto &obj : selected) {
        for (const auto &key : keyPressed) {
            Component::PlayerControlled::Action action = obj.GetAction(key.first);
            unsigned long owner = obj.GetOwner();
            Component::Position &pos = Core::Unique<Manager::Component<Component::Position>>::GetInstance().Get(owner);
            switch (action) {
                case Component::PlayerControlled::up:
                    pos.Move(glm::vec3(0.0f, 10.0f, 0.0f));
                    break;
                case Component::PlayerControlled::down:
                    pos.Move(glm::vec3(0.0f, -10.0f, 0.0f));
                    break;
                case Component::PlayerControlled::left:
                    pos.Move(glm::vec3(-10.0f, 0.0f, 0.0f));
                    break;
                case Component::PlayerControlled::right:
                    pos.Move(glm::vec3(10.0f, 0.0f, 0.0f));                                                          
                    break;
                case Component::PlayerControlled::fire:
                case Component::PlayerControlled::none:
                    break;
            }
        }
    }
}
void Input::SetKeyboardEvent(uint16_t scancode, uint8_t state, uint8_t repeat) {
    // State, 0 = released, 1 = pressed
    if(state == KEY_PRESSED) {
        if (keyPressed.find(scancode) == keyPressed.end()) {
            keyPressed.insert({scancode, repeat});
        } else {
            keyPressed[scancode] = repeat;
        }
        //printf("Pressed keyboard-key: %i\n", scancode);
    } else if(state == KEY_RELEASED) {
        keyPressed.erase(scancode);
        //printf("Released keyboard-key %i\n", scancode);
    }
}
void Input::SetMouseEvent(uint8_t button, uint8_t state, uint8_t clicks, glm::vec2 pos) {
    // top-left = 0,0
    // State, 0 = released, 1 = pressed
    if(state == KEY_PRESSED) {
        printf("Pressed mouse button: %i at X:%f Y:%f\n", button, pos.x, pos.y);
    } else if(state == KEY_RELEASED) {
        printf("Released mouse button: %i at X:%f Y:%f\n", button, pos.x, pos.y);
    }
}
};