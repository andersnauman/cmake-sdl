#ifndef COMPONENT_POSITION_H_
#define COMPONENT_POSITION_H_

// Global non-standard headers
#include <glm/glm.hpp>

namespace Component {
class Position {
    public:
        void SetOwner(unsigned int entityId) {
            entity_id_ = entityId;
        };

        unsigned int GetOwner() {
            return entity_id_;
        };

        void Reset() {};
        void Initialize() {
            //pos_ = glm::vec3(-1.5f, -1.5f, 1.0f);
            pos_ = glm::vec3(0.0f, 0.0f, 0.0f);
        };

        void Set(glm::vec3 newPos) {
            pos_ = newPos;
        };

        glm::vec3 Get() {
            return pos_;
        }

        void Move(glm::vec3 move);

    private:
        unsigned long entity_id_;
        glm::vec3 pos_;
};
};

#endif // COMPONENT_POSITION_H_