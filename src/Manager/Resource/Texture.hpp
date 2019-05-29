#ifndef MANAGER_RESOURCE_TEXTURE_H_
#define MANAGER_RESOURCE_TEXTURE_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>

// Global non-standard headers
#ifdef __APPLE__
#include <SDL_image.h>
#endif // __APPLE__

#ifdef __LINUX__
#include <SDL2/SDL_image.h>
#endif // __LINUX__

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>

// Local headers
#include "Core/Unique.hpp"
#include "Core/Vulkan.hpp"
#include "Core/Window.hpp"

namespace Manager::Resource {
class Texture {
    public:
        enum ObjectID : unsigned int {
            Statue,
        };

        void Load(ObjectID id);
        void Unload(ObjectID id);
        void UnloadAll();
        void Update(uint32_t imageIndex); //temp
        std::shared_ptr<Core::Vulkan::Object>& Get(ObjectID id);
    private:
        std::map<ObjectID, std::shared_ptr<Core::Vulkan::Object>> loadedObjects_;
};
};

#endif // MANAGER_RESOURCE_TEXTURE_H_