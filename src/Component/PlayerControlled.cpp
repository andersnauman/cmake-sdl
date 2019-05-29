#include <cstdint>

#include "PlayerControlled.hpp"

namespace Component {
PlayerControlled::Action PlayerControlled::GetAction(uint16_t scancode) {
    return Action::left;
};
};