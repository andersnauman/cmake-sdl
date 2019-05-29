#ifndef COMPONENT_GRAPHIC_H_
#define COMPONENT_GRAPHIC_H_

#include <memory>
#include <iostream>

#include "Core/Vulkan.hpp"

namespace Component {
class Graphic {
    public:
        Graphic() {};
        ~Graphic() {};
        void SetOwner(unsigned int entityId) {
            entity_id_ = entityId;
        };
        unsigned int GetOwner() {
            return entity_id_;
        };
        std::shared_ptr<Core::Vulkan::Object>& Get() {
            return obj_;
        };
        void Reset() {
            Core::Unique<Core::Vulkan>::GetInstance().DestroyBufferArray(obj_->mvp, obj_->mvpMemory);
            Core::Unique<Core::Vulkan>::GetInstance().DestroyBuffer(obj_->index, obj_->indexMemory);
            Core::Unique<Core::Vulkan>::GetInstance().DestroyBuffer(obj_->vertex, obj_->vertexMemory);
        };
        void Initialize() {
            obj_ = std::make_shared<Core::Vulkan::Object>();
            for (auto &vert : obj_->vertices_) {
                vert.pos *= glm::vec3(10.0f, 10.0f, 32.0f);
            }
            Core::Unique<Core::Vulkan>::GetInstance().CreateVertexBuffer(obj_->vertices_, obj_->vertex, obj_->vertexMemory);
            Core::Unique<Core::Vulkan>::GetInstance().CreateIndexBuffer(obj_->indices_, obj_->index, obj_->indexMemory);
            Core::Unique<Core::Vulkan>::GetInstance().CreateUniformBuffers(obj_->mvp, obj_->mvpMemory);
            Core::Unique<Core::Vulkan>::GetInstance().CreateDescriptorSets(obj_);
        };

    private:
        unsigned long entity_id_;
        std::shared_ptr<Core::Vulkan::Object> obj_;
};
};

#endif // COMPONENT_GRAPHIC_H_