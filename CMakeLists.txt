cmake_minimum_required(VERSION 3.14)
enable_language( C CXX ASM )

set(CMAKE_INSTALL_PREFIX "install") # temp

## Vulkan
# Apple need MoltenVK instead of Vulkan.
if(APPLE)
    # export VULKAN_SDK="/Users/andersnauman/Downloads/vulkansdk-macos-1.1.97.0/macOS"
    # export VK_LAYER_PATH="${VULKAN_SDK}/etc/vulkan/explicit_layer.d"
    # export VK_ICD_FILENAMES="${VULKAN_SDK}/etc/vulkan/icd.d/MoltenVK_icd.json"
    find_package(Vulkan REQUIRED)
else()
    add_subdirectory(external/Vulkan-Headers EXCLUDE_FROM_ALL)
    if(MINGW AND CMAKE_CROSSCOMPILING)
        message(FATAL_ERROR "Vulkan version 1.1.106 cannot be cross-compiled. Must run a binary which is 'impossible'")
    endif()
    add_subdirectory(external/Vulkan-Loader EXCLUDE_FROM_ALL)
endif()

## SDL2
set(SDL_STATIC OFF CACHE INTERNAL "Build a static version of the library")
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

## SDL2_image
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)

add_subdirectory(src)
