#include <iostream>
#include <memory>

#include "Core/Unique.hpp"
#include "Manager/Component.hpp"
#include "System/Camera.hpp"

#include "Render.hpp"

namespace System {
void Render::Update() {
    std::vector<Component::Graphic> a = {};
    Core::Unique<Manager::Component<Component::Graphic>>::GetInstance().GetAllActive(a);
    Core::Vulkan& vulkan = Core::Unique<Core::Vulkan>::GetInstance();
    vulkan.StartSecondaryCommandBuffer((uint32_t) a.size());
    for (unsigned int i = 0; i < (uint32_t) a.size(); i++) {
        auto & graphic = a.at(i);
        std::shared_ptr<Manager::Resource::Texture::Object>& texture = graphic.Get();
        vulkan.AddToSecondaryCommandBuffer(texture->vertexBuffer_, texture->indexBuffer_, static_cast<uint32_t>(texture->indices_.size()), graphic.descriptorSets_, i);
        
        Component::Position pos = Core::Unique<Manager::Component<Component::Position>>::GetInstance().Get(graphic.GetOwner());
        //printf("Position: %f %f %f\n", pos.Get().x, pos.Get().y, pos.Get().z);
        Core::Vulkan::UniformBufferObject mvp = Core::Unique<System::Camera>::GetInstance().GetMVP(pos.Get());       

        vulkan.UpdateUniformBuffer(mvp, graphic.mvpBufferMemory_);
    }
    vulkan.CreateCommandBuffers(false); // Only if the number of objects have changed.
};
};