#include <memory>

// Global non-standard headers
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "Core/Unique.hpp"
#include "Core/Vulkan.hpp"

#include "Graphic.hpp"

namespace Component {
void Graphic::SetOwner(unsigned int entityId) {
    entity_id_ = entityId;
};
unsigned int Graphic::GetOwner() {
    return entity_id_;
};
std::shared_ptr<Core::Vulkan::Object>& Graphic::Get() {
    return obj_;
};
void Graphic::Reset() {
    Core::Unique<Core::Vulkan>::GetInstance().DestroyBufferArray(obj_->mvp, obj_->mvpMemory);
    Core::Unique<Core::Vulkan>::GetInstance().DestroyBuffer(obj_->index, obj_->indexMemory);
    Core::Unique<Core::Vulkan>::GetInstance().DestroyBuffer(obj_->vertex, obj_->vertexMemory);
};
void Graphic::Initialize() {
    obj_ = std::make_shared<Core::Vulkan::Object>();
    for (auto &vert : obj_->vertices_) {
        vert.pos *= glm::vec3(10.0f, 10.0f, 32.0f);
    }
    Core::Unique<Core::Vulkan>::GetInstance().CreateVertexBuffer(obj_->vertices_, obj_->vertex, obj_->vertexMemory);
    Core::Unique<Core::Vulkan>::GetInstance().CreateIndexBuffer(obj_->indices_, obj_->index, obj_->indexMemory);
    Core::Unique<Core::Vulkan>::GetInstance().CreateUniformBuffers(obj_->mvp, obj_->mvpMemory);
    Core::Unique<Core::Vulkan>::GetInstance().CreateDescriptorSets(obj_);
};
};