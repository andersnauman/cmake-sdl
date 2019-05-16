#include <vector>
#include <iostream>

#include "SDL.h"

#include <vulkan/vulkan.h>

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char *argv[]) {
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("An SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_VULKAN);

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    VkInstance instance;

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
    uint32_t gpu_count = 0;
    vkEnumeratePhysicalDevices(instance, &gpu_count, nullptr);
    std::vector<VkPhysicalDevice> gpu_list(gpu_count);
    vkEnumeratePhysicalDevices(instance, &gpu_count, gpu_list.data());
    VkPhysicalDeviceProperties prop;
    vkGetPhysicalDeviceProperties(gpu_list[0], &prop);
    printf("Graphics: %s\n", prop.deviceName);

    uint32_t family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(gpu_list[0], &family_count, nullptr);
    std::vector<VkQueueFamilyProperties> family_list(family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(gpu_list[0], &family_count, family_list.data());

    for(auto f : family_list) {
        if(f.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            printf("Found graphics!!\n");
        }
    }

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}