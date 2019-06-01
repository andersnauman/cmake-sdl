#ifndef MANAGER_RESOURCE_TEXTURE_H_
#define MANAGER_RESOURCE_TEXTURE_H_

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

// Global non-standard headers
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>

#include <Core/Vulkan.hpp>

namespace Manager::Resource {
class Texture {
    public:    
        struct Object {
            std::vector<Core::Vulkan::Coords> vertices_;
            std::vector<uint16_t> indices_;
            struct {
                int h, w;
                std::shared_ptr<void> pixels;
                VkDeviceSize size;
            } data;
            VkBuffer vertexBuffer_;
            VkDeviceMemory vertexBufferMemory_;
            VkBuffer indexBuffer_;
            VkDeviceMemory indexBufferMemory_;
            VkImage image_;
            VkDeviceMemory imageMemory_;
            VkImageView imageView_;
            VkSampler imageSampler_;            
        };

        enum ObjectID : unsigned int {
            Statue,
        };

        void Load(ObjectID id);
        void Unload(ObjectID id);
        void UnloadAll();
        void Update(uint32_t imageIndex); //temp
        std::shared_ptr<Object> Get(ObjectID id);
    private:
        std::map<ObjectID, std::shared_ptr<Object>> loadedObjects_;
};
};

#endif // MANAGER_RESOURCE_TEXTURE_H_