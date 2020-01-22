#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <vector>
#include <stdexcept>
#include <iostream>

// Global non-standard headers
#ifdef __APPLE__
#include <SDL.h>
#include <SDL_vulkan.h>
#endif // __APPLE__

#ifdef __LINUX__
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#endif // __LINUX__

#ifdef _WIN32
#include <SDL.h>
#include <SDL_vulkan.h>
#endif // _WIN32

namespace Core {
class Window {
    public:
        Window() {};
        ~Window() {};

        void Initialize();
        void Destroy();
        bool Done();
        void HandleEvents();
        static void HandleWindowEvent(SDL_WindowEvent event);

        // Vulkan related        
        SDL_bool CreateSurface(VkInstance instance, VkSurfaceKHR* surface);
        std::vector<const char*> GetInstanceExtensions();

    private:
        static SDL_Window *window_;
        static bool done_;

        const int WIDTH = 800;
        const int HEIGHT = 600;
};
}

#endif // CORE_WINDOW_H
