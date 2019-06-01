#ifndef COMPONENT_GRAPHIC_H_
#define COMPONENT_GRAPHIC_H_

#include <memory>
#include <vector>

#include <vulkan/vulkan.hpp>

#include "Manager/Resource/Texture.hpp"

namespace Component {
class Graphic {
    public:
        Graphic() {};
        ~Graphic() {};
        void SetOwner(unsigned int entityId);
        unsigned int GetOwner();
        void Reset();
        void Initialize();
        void Update() {};

        std::shared_ptr<Manager::Resource::Texture::Object>& Get();
        std::vector<VkBuffer> mvpBuffer_;
        std::vector<VkDeviceMemory> mvpBufferMemory_;
        std::vector<VkDescriptorSet> descriptorSets_;
    private:
        unsigned long entity_id_;
        std::shared_ptr<Manager::Resource::Texture::Object> obj_;

};
};

#endif // COMPONENT_GRAPHIC_H_