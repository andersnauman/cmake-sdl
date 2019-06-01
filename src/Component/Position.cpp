// Global non-standard headers
#include <glm/glm.hpp>

#include "Position.hpp"

namespace Component {
void Position::SetOwner(unsigned int entityId) {
    entity_id_ = entityId;
};

unsigned int Position::GetOwner() {
    return entity_id_;
};

void Position::Reset() {
    pos_ = glm::vec3(0.0f, 0.0f, 0.0f);
    entity_id_ = 0;
};

void Position::Initialize() {
    pos_ = glm::vec3(0.0f, 0.0f, 0.0f);
};

void Position::Set(glm::vec3 newPos) {
    pos_ = newPos;
};

glm::vec3 Position::Get() {
    return pos_;
};

void Position::Move(glm::vec3 move) {
    pos_ += move;
}; 
};