cmake_minimum_required (VERSION 3.14)
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0074 NEW) # Use PACKAGE_ROOT variable

# Include PIC due to the fact of mixing SHARED and STATIC libraries.
# https://stackoverflow.com/questions/50600708/combining-cmake-object-libraries-with-shared-libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(GNUInstallDirs)

project(SDL2_image
    VERSION     2.0.3
    LANGUAGES   C
    DESCRIPTION "SDL2_image is a SDL2-project to add image functionality"
)

# Honor the BUILD_SHARED_LIBS variable instead of defining STATIC/SHARED in add_library
set(BUILD_SHARED_LIBS ON CACHE BOOL "")
add_library(${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} SDL2)

# Header-files
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
    "${CMAKE_CURRENT_SOURCE_DIR}/SDL_image.h"
)

# Source-files
## Base
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

###############
# Enable / Disable formats
###
option(LOAD_BMP  "Enable BMP support" ON)
option(LOAD_JPG  "Enable JPG support" OFF) # Do not have CMake-support yet
option(LOAD_GIF  "Enable GIF support" ON)
option(LOAD_PNG  "Enable PNG support" ON)
option(LOAD_LBM  "Enable LBM support" ON)
option(LOAD_PCX  "Enable PCX support" ON)
option(LOAD_PNM  "Enable PNM support" ON)
option(LOAD_SVG  "Enable SVG support" ON)
option(LOAD_TGA  "Enable TGA support" ON)
option(LOAD_TIF  "Enable TIF support" OFF) # No support yet
option(LOAD_WEBP "Enable WEBP support" OFF) # No support yet
option(LOAD_WIC  "Enable WIC support" ON)
option(LOAD_XCF  "Enable XCF support" ON)
option(LOAD_XPM  "Enable XPM support" ON)
option(LOAD_XV   "Enable XV support" ON)

###############
# Add settings to each active format
###
## Default to STATIC
set(SHARED_LIB_SETTING_PRE_DEP ${BUILD_SHARED_LIBS} CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
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
    add_subdirectory(external/libpng-1.6.35 EXCLUDE_FROM_ALL)
    target_link_libraries(${PROJECT_NAME} PRIVATE png_static)
    target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/libpng-1.6.35")

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
    add_subdirectory(external/libwebp-1.0.0 EXCLUDE_FROM_ALL)
    target_link_libraries(${PROJECT_NAME} PRIVATE webpdecoder webp webpdemux)
    target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/libwebp-1.0.0/src")
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_WEBP)
endif()
## WIC
if(LOAD_WIC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_WIC)
    if(WIN32 AND NOT COMMAND SDL_IMAGE_USE_WIC_BACKEND)
        message(STATUS "LOAD_WIC was set to TRUE but SDL_IMAGE_USE_WIC_BACKEND macro was not defined")
        message(AUTHOR_WARNING "Test if this 'COMMAND ...' works")
    endif()
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
## Back to original setting regarding STATIC/SHARED
set(BUILD_SHARED_LIBS ${SHARED_LIB_SETTING_PRE_DEP} CACHE BOOL "")

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

###############
# Dependencies
###
## SDL2
if (NOT TARGET SDL2)
    message(STATUS "SDL2-target was not found. Trying find_package.")
    find_package(SDL2 REQUIRED)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
endif()

###############
# Config* files
###
include(CMakePackageConfigHelpers)

## Version-file helper
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
## Config-file helper
configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake"
)

###############
# Install
###
## Targets + Export
install(
    TARGETS
        ${PROJECT_NAME}
    EXPORT
        ${PROJECT_NAME}Targets
    PUBLIC_HEADER DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    LIBRARY DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
    ARCHIVE DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
    RUNTIME DESTINATION
        ${CMAKE_INSTALL_BINDIR}
)

## Exported Targets-files
set(TARGET_DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake")
install(
    EXPORT
        ${PROJECT_NAME}Targets
    NAMESPACE
        SDL2::
    DESTINATION
        "${TARGET_DESTINATION}"
)

## Config- / ConfigVersion-files
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION
        "${TARGET_DESTINATION}"
)

###############
# Info output
###
message(STATUS "")
message(STATUS "SDL2_image was configured with the following options:")
message(STATUS "")
message(STATUS " Build Shared Library: ${BUILD_SHARED_LIBS}")
message(STATUS " Using BUILD_SHARED_LIBS which defaults to FALSE")
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
