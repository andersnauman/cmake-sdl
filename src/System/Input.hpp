#ifndef SYSTEM_INPUT_H_
#define SYSTEM_INPUT_H_

#include <cstdint>
#include <map>
#include <vector>

// Global non-standard headers
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#define KEY_RELEASED    0
#define KEY_PRESSED     1

namespace System {
class Input {
    public:
        Input() {};
        void Update();
        void SetKeyboardEvent(uint16_t scancode, uint8_t state, uint8_t repeat);
        void SetMouseEvent(uint8_t button, uint8_t state, uint8_t clicks, glm::vec2 pos);
    private:
        struct MouseEvent {
            glm::vec2 pos;
            bool repeat;
            uint8_t type;
        };
        std::map<uint16_t, bool> keyPressed;
        std::map<uint8_t, MouseEvent> mousePressed;

        std::vector<MouseEvent> eventQueue_;

};
};

#endif // SYSTEM_INPUT_H_