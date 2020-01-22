cmake_minimum_required(VERSION 3.14)

# Include PIC due to the fact of mixing SHARED and STATIC libraries.
# https://stackoverflow.com/questions/50600708/combining-cmake-object-libraries-with-shared-libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Need some DLL magic to happen.
# https://stackoverflow.com/questions/40739061/error-lnk1104-cannot-open-file-debug-myprojectlib-lib
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(GNUInstallDirs)

project(zlib
    VERSION 1.2.11
    LANGUAGES C
)

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
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h.cmakein
    ${CMAKE_CURRENT_BINARY_DIR}/zconf.h @ONLY
)

###############
# Library files
###
set(ZLIB_PUBLIC_HDRS
    "${CMAKE_CURRENT_BINARY_DIR}/zconf.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/zlib.h"
)
set(ZLIB_PRIVATE_HDRS
    "${CMAKE_CURRENT_SOURCE_DIR}/crc32.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/deflate.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/gzguts.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/inffast.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/inffixed.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/inflate.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/inftrees.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/trees.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/zutil.h"
)
set(ZLIB_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/adler32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/compress.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/crc32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/deflate.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/gzclose.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/gzlib.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/gzread.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/gzwrite.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/inflate.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/infback.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/inftrees.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/inffast.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/trees.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/uncompr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/zutil.c"
)

###############
# Build
###
# Honor the BUILD_SHARED_LIBS variable instead of defining STATIC/SHARED in add_library
set(BUILD_SHARED_LIBS ON CACHE BOOL "")
add_library(${PROJECT_NAME} SHARED)

# Header-files
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
    "${CMAKE_CURRENT_SOURCE_DIR}/zlib.h"
)

target_sources(${PROJECT_NAME} PRIVATE 
    ${ZLIB_SRCS}
    ${ZLIB_ASMS}
    ${ZLIB_PRIVATE_HDRS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
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
    RUNTIME DESTINATION
        "${INSTALL_BIN_DIR}"
    ARCHIVE DESTINATION
        "${INSTALL_LIB_DIR}"
    LIBRARY DESTINATION
        "${INSTALL_LIB_DIR}"
)

## Exported Targets-files
set(TARGET_DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake")
install(
    EXPORT
        ${PROJECT_NAME}Targets
    NAMESPACE
        zlib::
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