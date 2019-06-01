#include <cstdint>

// Global non-standard headers
#include "SDL.h"

#include "PlayerControlled.hpp"

namespace Component {
void PlayerControlled::SetOwner(unsigned int entityId) {
    entity_id_ = entityId;
};
unsigned int PlayerControlled::GetOwner() {
    return entity_id_;
};
void PlayerControlled::Reset() {
    keyMap.clear();  
};
void PlayerControlled::Initialize() {
    keyMap.insert({SDL_SCANCODE_W, up});
    keyMap.insert({SDL_SCANCODE_S, down});
    keyMap.insert({SDL_SCANCODE_A, left});
    keyMap.insert({SDL_SCANCODE_D, right});
    keyMap.insert({SDL_BUTTON_LEFT, fire});
};
PlayerControlled::Action PlayerControlled::GetAction(uint16_t scancode) {
    if (keyMap.find(scancode) == keyMap.end()) {
        return Action::none;
    }
    return keyMap.at(scancode);
};
};