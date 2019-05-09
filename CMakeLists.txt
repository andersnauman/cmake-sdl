cmake_minimum_required(VERSION 3.14)

## SDL2
set(SDL_STATIC OFF CACHE INTERNAL "Build a static version of the library")
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

## SDL2_image
set(SDL_IMAGE_STATIC OFF CACHE INTERNAL "Build a static version of the library")
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)

add_subdirectory(src)
