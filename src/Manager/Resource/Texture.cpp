#include <cstdint>
#include <map>
#include <memory>
#include <vector>

// Global non-standard headers
#ifdef __APPLE__
#include <SDL_image.h>
#endif // __APPLE__

#ifdef __LINUX__
#include <SDL2/SDL_image.h>
#endif // __LINUX__

// Local headers
#include "Core/Unique.hpp"
#include "Core/Vulkan.hpp"

#include "Texture.hpp"

namespace Manager::Resource {
void Texture::Load(ObjectID id) {
    if (loadedObjects_.find(id) != loadedObjects_.end()) {
        printf("Texture is already loaded\n");
        return;
    }
    // Image data
    std::string path;
    switch (id) {
        case Statue:
            path = "../src/Resource/Texture/statue.png";
            break;
    };

    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        throw std::runtime_error("Could not load image");
    }

    std::shared_ptr<Object> obj(new Object);
    obj->data.h = surface->h;
    obj->data.w = surface->w;
    obj->data.size = surface->h * surface->w * 4; // 4 == rgba aka 4byte
    obj->data.pixels.reset(std::malloc(obj->data.size), std::free);
    std::memcpy(obj->data.pixels.get(), surface->pixels, obj->data.size);
    SDL_FreeSurface(surface);

    // inPosition and attributeDescriptions in shader
    std::vector<Core::Vulkan::Coords> vertices = {
        {{+16.0f, +16.0f, 0.0f},{0.0f, 0.0f}},
        {{-16.0f, -16.0f, 0.0f},{1.0f, 0.0f}}, // none
        {{+16.0f, -16.0f, 0.0f},{1.0f, 0.0f}}, // none
        {{-16.0f, +16.0f, 0.0f},{1.0f, 0.0f}}, // none
        {{+16.0f, +0.0f, 0.0f},{0.0f, 1.0f}},
        {{+0.0f, +16.0f, 0.0f},{1.0f, 0.0f}},
        {{+0.0f, +0.0f, 0.0f},{1.0f, 1.0f}},
    };    
    std::vector<uint16_t> indices = {{
        0, 6, 4, 6, 0, 5
    }};
    obj->vertices_ = vertices;
    obj->indices_ = indices;
    // Vulkan objects
    Core::Vulkan& vulkan = Core::Unique<Core::Vulkan>::GetInstance();

    vulkan.CreateVertexBuffer(obj->vertices_, obj->vertexBuffer_, obj->vertexBufferMemory_);
    vulkan.CreateIndexBuffer(obj->indices_, obj->indexBuffer_, obj->indexBufferMemory_);
    vulkan.CreateTextureImage(obj->image_, obj->imageMemory_, obj->data.pixels, obj->data.size, obj->data.h, obj->data.w);
    vulkan.CreateTextureImageView(obj->image_, obj->imageView_);
    vulkan.CreateTextureSampler(obj->imageSampler_);
    //loadedObjects_.insert(std::pair<ObjectID, std::shared_ptr<Object>>(id, obj));
    loadedObjects_.insert({id, obj});
    printf("Image loaded!\n");
};

void Texture::Unload(ObjectID id) {
    printf("Unloading %i\n", id);
    //std::shared_ptr<Object> obj = Get(id);
    std::shared_ptr<Object> obj = loadedObjects_.at(id);
    Core::Vulkan& vulkan = Core::Unique<Core::Vulkan>::GetInstance();
    vulkan.DestroyTexture(obj->image_, obj->imageMemory_, obj->imageView_, obj->imageSampler_);
    vulkan.DestroyBuffer(obj->vertexBuffer_, obj->vertexBufferMemory_);
    vulkan.DestroyBuffer(obj->indexBuffer_, obj->indexBufferMemory_);
};

void Texture::UnloadAll() {
    for (auto it = loadedObjects_.cbegin(); it != loadedObjects_.cend();) {
        Unload(it->first);
        it = loadedObjects_.erase(it);
    }
};

void Texture::Update(uint32_t imageIndex) {
    //for (auto& obj : loadedObjects_) {}
};

std::shared_ptr<Texture::Object> Texture::Get(ObjectID id) {
    try {
        return loadedObjects_.at(id);
    } catch (std::out_of_range& e) {
        throw std::runtime_error("Texture object is not loaded");
    }
};
};