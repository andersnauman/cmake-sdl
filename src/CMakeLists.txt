cmake_minimum_required(VERSION 3.14)

include(GNUInstallDirs)
include(ExternalProject)
project(window CXX)

# Directories
set(LIBRARY_DIR lib)
set(RUNTIME_DIR bin)

# RPATH for APPLE/UNIX. Windows do not use RPATH.
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
if (APPLE)
    set(CMAKE_INSTALL_RPATH "@loader_path/${LIBRARY_DIR}")
elseif (UNIX)
    set(CMAKE_INSTALL_RPATH "$ORIGIN/${LIBRARY_DIR}")
endif()

add_executable(${PROJECT_NAME}
    main.cpp
    Component/Graphic.cpp
    Component/Position.cpp
    Component/PlayerControlled.cpp
    Core/Vulkan.cpp
    Core/Vulkan_debug.cpp
    Core/Vulkan_utils.cpp
    Core/Window.cpp
    Manager/Resource/Texture.cpp
    System/Render.cpp
    System/Input.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Resources
set(RESOURCES
    "Resource/Texture/statue.png"
    "Shader/frag.spv"
    "Shader/vert.spv"
)

# Dependencies
## GLM
if(TARGET glm::glm)
    target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
elseif()
    find_package(glm REQUIRED)
    if (glm_FOUND)
        target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
    endif()
endif()

## Vulkan
if(NOT APPLE)
    if(NOT (TARGET Vulkan::Headers AND TARGET Vulkan::Vulkan))
        message(AUTHOR_WARNING "TODO: Add support to find vulkan through find_package()")
        message(FATAL_ERROR "Could not find Vulkan")
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Headers)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

## SDL2
if (WIN32)
    # Error: ... undefined reference to `WinMain@16'
    # mingw32 must be linked before libSDL2main.a since the creation of linklibs.rsp will always be library before dependencies.
    # https://gitlab.kitware.com/cmake/cmake/commit/489b1c23b9a880da0012427b60cce7b6f5ddaa27
    #
    # Alternative solution:
    # get_directory_property(SDL_LIBS DIRECTORY external/SDL DEFINITION SDL_LIBS)
    # target_link_libraries(${PROJECT_NAME} ${SDL_LIBS})
    if (MINGW AND CMAKE_CROSSCOMPILING)
        target_link_libraries(${PROJECT_NAME} PRIVATE -lmingw32)
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)

## SDL2_image
if (NOT TARGET SDL2_image)
    message(AUTHOR_WARNING "TODO: Add support to find SDL2_image through find_package()")
    message(FATAL_ERROR "Could not find SDL2_image")
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)

# Install
## Paths
set(INSTALL_RUNTIME_DIR ${RUNTIME_DIR})
if (MINGW)
    set(INSTALL_LIBRARY_DIR ${INSTALL_RUNTIME_DIR})
else ()
    set(INSTALL_LIBRARY_DIR ${INSTALL_RUNTIME_DIR}/${LIBRARY_DIR})
endif()

## Targets
install(
    TARGETS
        ${PROJECT_NAME}
        SDL2
        SDL2_image
        #vulkan
        #Vulkan-Headers
    RUNTIME DESTINATION
        ${INSTALL_RUNTIME_DIR}
    LIBRARY DESTINATION
        ${INSTALL_LIBRARY_DIR}
)
if(APPLE)
    install(
        FILES
            ${Vulkan_LIBRARIES}
        DESTINATION
            ${INSTALL_LIBRARY_DIR}
    )
endif()

## Resources
install(
    FILES
        ${RESOURCES}
    DESTINATION
        ${INSTALL_RUNTIME_DIR}/Resources
)