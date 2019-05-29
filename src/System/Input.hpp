#ifndef SYSTEM_INPUT_H_
#define SYSTEM_INPUT_H_

#include <cstdint>

#include <glm/glm.hpp>

#define KEY_RELEASED    0
#define KEY_PRESSED     1

namespace System {
class Input {
    public:
        Input() {};
        void SetKeyboardEvent(uint16_t scancode, uint8_t state, uint8_t repeat);
        void SetMouseEvent(uint8_t button, uint8_t state, uint8_t clicks, glm::vec2 pos);
};
};

#endif // SYSTEM_INPUT_H_