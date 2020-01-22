#include <iostream>

#include "Core/Unique.hpp"
#include "Core/Vulkan.hpp"
#include "Core/Window.hpp"
#include "Component/Graphic.hpp"
#include "Component/PlayerControlled.hpp"
#include "Component/Position.hpp"
#include "Manager/Entity.hpp"
#include "Manager/Component.hpp"
#include "Manager/Resource/Texture.hpp"
#include "System/Input.hpp"
#include "System/Render.hpp"

int main() {
    // Load Window(SDL) and Vulkan
    Core::Unique<Core::Window>::GetInstance().Initialize();
    Core::Unique<Core::Vulkan>::GetInstance().SetInstanceExtensions(Core::Unique<Core::Window>::GetInstance().GetInstanceExtensions());
    Core::Unique<Core::Vulkan>::GetInstance().Initialize();

    // Add entities and components
    // 1
    unsigned int id = Core::Unique<Manager::Entity>::GetInstance().Add();
    Core::Unique<Manager::Component<Component::Position>>::GetInstance().Add(id);
    Core::Unique<Manager::Component<Component::Position>>::GetInstance().Get(id).Set(glm::vec3(0.0f, -10.0f, 20.0f));
    Core::Unique<Manager::Component<Component::Graphic>>::GetInstance().Add(id);
    Core::Unique<Manager::Component<Component::PlayerControlled>>::GetInstance().Add(id);
    // 2
    id = Core::Unique<Manager::Entity>::GetInstance().Add();
    Core::Unique<Manager::Component<Component::Position>>::GetInstance().Add(id);
    Core::Unique<Manager::Component<Component::Graphic>>::GetInstance().Add(id);

    // Main loop
    while(!Core::Unique<Core::Window>::GetInstance().Done()) {
        Core::Unique<Core::Window>::GetInstance().HandleEvents();
        uint32_t image = Core::Unique<Core::Vulkan>::GetInstance().StartFrame();
        if (image == UINT32_MAX) {
            continue;
        }
        Core::Unique<System::Input>::GetInstance().Update();
        Core::Unique<System::Render>::GetInstance().Update();
        Core::Unique<Core::Vulkan>::GetInstance().EndFrame();
    }
    Core::Unique<Manager::Resource::Texture>::GetInstance().UnloadAll();
    Core::Unique<Manager::Component<Component::PlayerControlled>>::GetInstance().Destroy();
    Core::Unique<Manager::Component<Component::Position>>::GetInstance().Destroy();
    Core::Unique<Manager::Component<Component::Graphic>>::GetInstance().Destroy();
    Core::Unique<Core::Vulkan>::GetInstance().Destroy();
    Core::Unique<Core::Window>::GetInstance().Destroy();
    return 0;
}