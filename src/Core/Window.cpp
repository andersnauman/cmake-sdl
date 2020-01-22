#include <vector>
#include <stdexcept>
#include <cstdint>

#ifdef __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_vulkan.h>
#endif // __APPLE__

#ifdef __LINUX__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_vulkan.h>
#endif // __LINUX__

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_vulkan.h>
#endif

#include <glm/glm.hpp>

#include "Core/Unique.hpp"
#include "Core/Vulkan.hpp"
#include "System/Camera.hpp"
#include "System/Input.hpp"

#include "Window.hpp"

namespace Core {
SDL_Window* Window::window_ = nullptr;
bool Window::done_ = false;

void Window::Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    window_ = SDL_CreateWindow("Vulkan", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    if (window_ == NULL) {
        throw std::runtime_error("Could not create SDL window");
    }
}

void Window::Destroy() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

bool Window::Done() {
    return done_;
}

void Window::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                done_ = true;
                break;
            case SDL_WINDOWEVENT:
                HandleWindowEvent(event.window);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                Core::Unique<System::Input>::GetInstance().SetKeyboardEvent((uint16_t) event.key.keysym.scancode, event.key.state, event.key.repeat);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                Core::Unique<System::Input>::GetInstance().SetMouseEvent(event.button.button, event.button.state, event.button.clicks, glm::vec2((float) event.button.x, (float) event.button.y));
                break;
        };
    }
}

void Window::HandleWindowEvent(SDL_WindowEvent window) {
    switch(window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:   
            Core::Unique<Core::Vulkan>::GetInstance().SetWindowSize(window.data1, window.data2);
            Core::Unique<System::Camera>::GetInstance().SetAspectRatio((float)(window.data1 / window.data2));
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            break;
        default:
            break;
    }
}

SDL_bool Window::CreateSurface(VkInstance instance, VkSurfaceKHR* surface) {
    return SDL_Vulkan_CreateSurface(window_, instance, surface);
}

std::vector<const char*> Window::GetInstanceExtensions() {
    unsigned int count;
    std::vector<const char*> extensions;

    if (SDL_Vulkan_GetInstanceExtensions(window_, &count, nullptr) != SDL_TRUE) {
        return extensions;
    }
    extensions.resize(count);
    SDL_Vulkan_GetInstanceExtensions(window_, &count, extensions.data());
    return extensions;
}
}
