#include <iostream>

#include "Core/Unique.hpp"
#include "Manager/Component.hpp"
#include "System/Camera.hpp"

#include "Render.hpp"

namespace System {
void Render::Update() {
    std::vector<Component::Graphic> a = {};
    Core::Unique<Manager::Component<Component::Graphic>>::GetInstance().GetAllActive(a);
    Core::Unique<Core::Vulkan>::GetInstance().StartSecondaryCommandBuffer((uint32_t) a.size());

    for (unsigned int i = 0; i < (uint32_t) a.size(); i++) {
        auto & obj = a.at(i);
        // Add object into the buffer
        Core::Unique<Core::Vulkan>::GetInstance().AddToSecondaryCommandBuffer(obj.Get(), i);
        // Get position and then get MVP
        Component::Position pos = Core::Unique<Manager::Component<Component::Position>>::GetInstance().Get(obj.GetOwner());
        //printf("Position: %f %f %f\n", pos.Get().x, pos.Get().y, pos.Get().z);
        Core::Vulkan::UniformBufferObject mvp = Core::Unique<System::Camera>::GetInstance().GetMVP(pos.Get());       
        // Update MVP on Vulkan object
        Core::Unique<Core::Vulkan>::GetInstance().UpdateUniformBuffer(obj.Get(), mvp);
    }
    Core::Unique<Core::Vulkan>::GetInstance().CreateCommandBuffers(false); // Only if the number of objects have changed.
};
};