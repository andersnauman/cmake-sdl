#include "SDL.h"
#include <iostream>

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

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}