#include <cstdint>
#include <iostream>

// Global non-standard headers
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <SDL_image.h>

#include "Component/PlayerControlled.hpp"
#include "Component/Position.hpp"
#include "Core/Unique.hpp"
#include "Manager/Component.hpp"
#include "System/Camera.hpp"

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
    /*
    if(mousePressed.find(SDL_BUTTON_LEFT) == mousePressed.end()) {
        return;
    }
    if(mousePressed[SDL_BUTTON_LEFT].repeat == true) {
        return;
    }
    std::vector<Component::Position> allPos = {};
    Core::Unique<Manager::Component<Component::Position>>::GetInstance().GetAllActive(allPos);
    for(auto &obj : allPos) {
        glm::vec3 pos = obj.Get();
        glm::vec2 mousePos = mousePressed[SDL_BUTTON_LEFT].pos;
        if(pos.x < mousePos.x && (pos.x + 32.0f) > mousePos.x) { // 32 = size
            printf("Hit object %i\n", obj.GetOwner());
        }
    }
    */
    for(auto &event : eventQueue_) {        
        if(event.type == SDL_BUTTON_LEFT) {
            //printf("Left mouse pressed: %i\n", event.type);
            glm::vec3 lookAt = Core::Unique<System::Camera>::GetInstance().GetLookPosition();
            System::Camera::Resolution resolution = Core::Unique<System::Camera>::GetInstance().GetResolution();
            printf("Camera look at X: %f Y:%f Z:%f\n", lookAt.x, lookAt.y, lookAt.z);
            //printf("Clicked on X: %f Y:%f\n", event.pos.x - (resolution.Width/2), event.pos.y - (resolution.Height/2));
            glm::vec3 pos3d = Core::Unique<System::Camera>::GetInstance().MousePos3D(event.pos);
            //printf("3d pos: %f %f %f\n", pos3d.x, pos3d.y, pos3d.z);
        }
    }
    eventQueue_.clear();
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
        
/*
        if(mousePressed.find(button) == mousePressed.end()) {
            mousePressed.insert({button, MouseEvent{pos, false}});
        } else {
            mousePressed[button].repeat = true;
        }
*/        
        //printf("Pressed mouse button: %i at X:%f Y:%f\n", button, pos.x, pos.y);
    } else if(state == KEY_RELEASED) {
        MouseEvent event = { pos, false, button};
        eventQueue_.emplace_back(event);
        //mousePressed.erase(button);
        printf("Released mouse button: %i at X:%f Y:%f\n", button, pos.x, pos.y);
    }
}
};