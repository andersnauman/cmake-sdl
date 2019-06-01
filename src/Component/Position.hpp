#ifndef COMPONENT_POSITION_H_
#define COMPONENT_POSITION_H_

// Global non-standard headers
#include <glm/glm.hpp>

namespace Component {
class Position {
    public:
        Position() {};
        ~Position() {};
        void SetOwner(unsigned int entityId);
        unsigned int GetOwner();
        void Reset();
        void Initialize();
        void Update() {};

        void Set(glm::vec3 newPos);
        glm::vec3 Get();
        void Move(glm::vec3 move);

    private:
        unsigned long entity_id_;
        glm::vec3 pos_;
};
};

#endif // COMPONENT_POSITION_H_