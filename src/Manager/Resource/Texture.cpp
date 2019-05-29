#include <iostream>

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
            path = "../Resource/Texture/statue.png";
            break;
    };

    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        throw std::runtime_error("Could not load image");
    }

    std::shared_ptr<Core::Vulkan::Object> obj(new Core::Vulkan::Object);
    obj->data.h = surface->h;
    obj->data.w = surface->w;
    obj->data.size = surface->h * surface->w * 4; // 4 == rgba aka 4byte
    obj->data.pixels.reset(std::malloc(obj->data.size), std::free);
    std::memcpy(obj->data.pixels.get(), surface->pixels, obj->data.size);
    SDL_FreeSurface(surface);

    // Vulkan objects
    // CreateShaderInfoBuffer()?
    //Core::Unique<Core::Vulkan>::GetInstance().CreateVertexBuffer(obj->vertices_, obj->vertex, obj->vertexMemory);
    //Core::Unique<Core::Vulkan>::GetInstance().CreateIndexBuffer(obj->indices_, obj->index, obj->indexMemory);
    /*
    Core::Unique<Core::Vulkan>::GetInstance().CreateTextureImage(obj);
    Core::Unique<Core::Vulkan>::GetInstance().CreateTextureSampler(obj->imageSampler);
    */
    //Core::Unique<Core::Vulkan>::GetInstance().CreateUniformBuffers(obj->mvp, obj->mvpMemory);
    //Core::Unique<Core::Vulkan>::GetInstance().CreateDescriptorSets(obj);
    //Core::Unique<Core::Vulkan>::GetInstance().CreateSecondaryCommandBuffer(obj);
    //Core::Unique<Core::Vulkan>::GetInstance().CreateCommandBuffers(obj);
    
    printf("Image loaded!\n");
    loadedObjects_.insert(std::pair<ObjectID, std::shared_ptr<Core::Vulkan::Object>>(id, obj));
};

void Texture::Unload(ObjectID id) {
    printf("Unloading %i\n", id);
    //std::shared_ptr<Core::Vulkan::Object>& obj = Get(id);
    //Core::Unique<Core::Vulkan>::GetInstance().DestroyTexture(obj);
    //Core::Unique<Core::Vulkan>::GetInstance().DestroyBuffer(obj->vertex, obj->vertexMemory);
    //Core::Unique<Core::Vulkan>::GetInstance().DestroyBuffer(obj->index, obj->indexMemory);
    //Core::Unique<Core::Vulkan>::GetInstance().DestroyBufferArray(obj->mvp, obj->mvpMemory);
    // Do not need to cleanup descriptor-set. They will be destroyed when the pool get destroyed.
};

void Texture::UnloadAll() {
    for (auto it = loadedObjects_.cbegin(); it != loadedObjects_.cend();) {
        Unload(it->first);
        it = loadedObjects_.erase(it);
    }
};

void Texture::Update(uint32_t imageIndex) {
    for (auto& obj : loadedObjects_) {
        //Core::Unique<Core::Vulkan>::GetInstance().UpdateUniformBuffer(obj.second, imageIndex);
    }
};

std::shared_ptr<Core::Vulkan::Object>& Texture::Get(ObjectID id) {
    try {
        return loadedObjects_.at(id);
    } catch (std::out_of_range& e) {
        throw std::runtime_error("Texture object is not loaded");
    }
};
};