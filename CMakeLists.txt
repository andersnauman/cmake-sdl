cmake_minimum_required(VERSION 3.14)
enable_language( C CXX ASM )

set(CMAKE_INSTALL_PREFIX "install") # temp

## Vulkan
add_subdirectory(external/Vulkan-Headers EXCLUDE_FROM_ALL)
if(MINGW AND CMAKE_CROSSCOMPILING)
    message(FATAL_ERROR "Vulkan version 1.1.106 cannot be cross-compiled.")
endif()
add_subdirectory(external/Vulkan-Loader EXCLUDE_FROM_ALL)

## SDL2
set(SDL_STATIC OFF CACHE INTERNAL "Build a static version of the library")
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

## SDL2_image
set(SDL_IMAGE_SHARED ON CACHE BOOL "Build a shared version of the library")
set(SDL_IMAGE_STATIC OFF CACHE INTERNAL "Build a static version of the library")
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)

add_subdirectory(src)
