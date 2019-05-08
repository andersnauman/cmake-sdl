# Cross-compile:
# cmake -DCMAKE_TOOLCHAIN_FILE=../ToolChain.cmake ..

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

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_INSTALL_PREFIX "install") # temp

# Dependencies
## SDL2
set(SDL_STATIC OFF CACHE INTERNAL "Build a static version of the library")
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

target_include_directories(${PROJECT_NAME} PRIVATE SDL2)
if (WIN32)
    # Error: ... undefined reference to `WinMain@16'
    # mingw32 must be linked before libSDL2main.a since the creation of linklibs.rsp will always be library before dependencies.
    # https://gitlab.kitware.com/cmake/cmake/commit/489b1c23b9a880da0012427b60cce7b6f5ddaa27
    #
    # Alternative solution:
    # get_directory_property(SDL_LIBS DIRECTORY external/SDL DEFINITION SDL_LIBS)
    # target_link_libraries(${PROJECT_NAME} ${SDL_LIBS})
    if (MINGW)
        target_link_libraries(${PROJECT_NAME} -lmingw32)
    endif()
    target_link_libraries(${PROJECT_NAME} SDL2main)
endif()
target_link_libraries(${PROJECT_NAME} SDL2)

## SDL2_image
#get_property(SDL2_image_SDL2 TARGET SDL2 PROPERTY LINK_LIBRARIES)
get_property(SDL2_image_SDL2 TARGET SDL2 PROPERTY INCLUDE_DIRECTORIES)
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} SDL2_image)

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
    RUNTIME DESTINATION
        ${INSTALL_RUNTIME_DIR}
    LIBRARY DESTINATION
        ${INSTALL_LIBRARY_DIR}
)