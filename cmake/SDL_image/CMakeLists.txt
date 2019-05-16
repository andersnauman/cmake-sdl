cmake_minimum_required (VERSION 3.12)
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0074 NEW) # Use PACKAGE_ROOT variable

# Include PIC due to the fact of mixing SHARED and STATIC libraries.
# https://stackoverflow.com/questions/50600708/combining-cmake-object-libraries-with-shared-libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(GNUInstallDirs)

project(SDL2_image
    VERSION     2.0.3
    LANGUAGES   C
    DESCRIPTION "SDL2_image is a SDL2-project to add image funcationality"
)
set(SDL_IMAGE_SHARED OFF CACHE BOOL "Build a shared version of the library")
set(SDL_IMAGE_STATIC ON CACHE BOOL "Build a static version of the library")

add_library(${PROJECT_NAME} SHARED)
add_dependencies(${PROJECT_NAME} SDL2)

# Source-files
## Base
target_sources(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/SDL_image.h"
)
target_sources(${PROJECT_NAME} PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_bmp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_jpg.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_png.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_lbm.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_pcx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_pnm.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_svg.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_webp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_xcf.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_xpm.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMG_xv.c"
)
if(APPLE)
    target_sources(${PROJECT_NAME} PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/IMG_ImageIO.m"
        #"${CMAKE_CURRENT_SOURCE_DIR}/IMG_UIImage.m" #'UIKit/UIKit.h' file not found
    )
else()
    target_sources(${PROJECT_NAME} PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/IMG_gif.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/IMG_tga.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/IMG_tif.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/IMG_WIC.c"
    )
endif()

# Formats
set_option(LOAD_BMP  "Enable BMP support" ON)
set_option(LOAD_JPG  "Enable JPG support" OFF) # Do not have CMake-support yet
set_option(LOAD_GIF  "Enable GIF support" ON)
set_option(LOAD_PNG  "Enable PNG support" ON)
set_option(LOAD_LBM  "Enable LBM support" ON)
set_option(LOAD_PCX  "Enable PCX support" ON)
set_option(LOAD_PNM  "Enable PNM support" ON)
set_option(LOAD_SVG  "Enable SVG support" ON)
set_option(LOAD_TGA  "Enable TGA support" ON)
set_option(LOAD_TIF  "Enable TIF support" OFF) # No support yet
set_option(LOAD_WEBP "Enable WEBP support" OFF) # No support yet
set_option(LOAD_WIC  "Enable WIC support" OFF) # No support yet
set_option(LOAD_XCF  "Enable XCF support" ON)
set_option(LOAD_XPM  "Enable XPM support" ON)
set_option(LOAD_XV   "Enable XV support" ON)

## BMP
if(LOAD_BMP)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_BMP)
endif()
## JPG
if(LOAD_JPG)
    #add_subdirectory(external/jpeg-9b)
    #target_link_libraries(${PROJECT_NAME} PRIVATE JPEG)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_JPG)
endif()
## GIF
if(LOAD_GIF)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_GIF)
endif()
## LBM
if(LOAD_LBM)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_LBM)
endif()
## PCX
if(LOAD_PCX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_PCX)
endif()
## PNG
if(LOAD_PNG)
    if(MINGW AND CMAKE_CROSSCOMPILING)
        # To find ZLIB inside MinGW when you cross-compile, a better path needs to be added.
        set(ZLIB_ROOT "${CMAKE_FIND_ROOT_PATH}/sys-root/mingw" CACHE INTERNAL "FindZLIB.cmake tries this path if set")
    endif()
    set(PNG_SHARED OFF CACHE INTERNAL "Build shared lib")
    add_subdirectory(external/libpng-1.6.35)
    target_link_libraries(${PROJECT_NAME} PRIVATE png_static)
    target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/libpng-1.6.35")

    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_PNG)
endif()
## PNM
if(LOAD_PNM)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_PNM)
endif()
## SVG
if(LOAD_SVG)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_SVG)
endif()
## TGA
if(LOAD_TGA)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_TGA)
endif()
## TIF
if(LOAD_TIF)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_TIF)
endif()
## WEBP
if(LOAD_WEBP)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_WEBP)
endif()
## WIC
if(LOAD_WIC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_WIC)
endif()
## XCF
if(LOAD_XCF)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_XCF)
endif()
## XPM
if(LOAD_XPM)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_XPM)
endif()
## XV
if(LOAD_XV)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_XV)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Dependencies
## SDL2
if (NOT TARGET SDL2)
    message(FATAL_ERROR "SDL2 was not yet loaded. Please do so.")
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
endif()

# Info Output
message(STATUS "")
message(STATUS "SDL2_image was configured with the following options:")
message(STATUS "")
message(STATUS " Build Shared Library: ${SDL_IMAGE_SHARED}")
message(STATUS " Build Static Library: ${SDL_IMAGE_STATIC}")
message(STATUS "")
message(STATUS " Formats:")
message(STATUS "")
message(STATUS "  BMP:  ${LOAD_BMP}")
message(STATUS "  JPG:  ${LOAD_JPG}")
message(STATUS "  GIF:  ${LOAD_GIF}")
message(STATUS "  LBM:  ${LOAD_LBM}")
message(STATUS "  PCX:  ${LOAD_PCX}")
message(STATUS "  PNG:  ${LOAD_PNG}")
message(STATUS "  PNM:  ${LOAD_PNM}")
message(STATUS "  SVG:  ${LOAD_SVG}")
message(STATUS "  TGA:  ${LOAD_TGA}")
message(STATUS "  TIF:  ${LOAD_TIF}")
message(STATUS "  WEBP: ${LOAD_WEBP}")
message(STATUS "  WIC:  ${LOAD_WIC}")
message(STATUS "  XCF:  ${LOAD_XCF}")
message(STATUS "  XPM:  ${LOAD_XPM}")
message(STATUS "  XV:   ${LOAD_XV}")
message(STATUS "")
