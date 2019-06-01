#include <memory>

// Global non-standard headers
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "Core/Unique.hpp"
#include "Core/Vulkan.hpp"
#include "Manager/Resource/Texture.hpp"

#include "Graphic.hpp"

namespace Component {
void Graphic::SetOwner(unsigned int entityId) {
    entity_id_ = entityId;
};
unsigned int Graphic::GetOwner() {
    return entity_id_;
};
std::shared_ptr<Manager::Resource::Texture::Object>& Graphic::Get() {
    return obj_;
};
void Graphic::Reset() {
    Core::Unique<Core::Vulkan>::GetInstance().DestroyBufferArray(mvpBuffer_, mvpBufferMemory_);
};
void Graphic::Initialize() {
    Core::Unique<Manager::Resource::Texture>::GetInstance().Load(Manager::Resource::Texture::Statue);
    obj_ = Core::Unique<Manager::Resource::Texture>::GetInstance().Get(Manager::Resource::Texture::Statue);
    
    Core::Vulkan& vulkan = Core::Unique<Core::Vulkan>::GetInstance();
    vulkan.CreateUniformBuffers(mvpBuffer_, mvpBufferMemory_);
    vulkan.CreateDescriptorSets(descriptorSets_, mvpBuffer_, obj_->imageView_, obj_->imageSampler_);
};
};