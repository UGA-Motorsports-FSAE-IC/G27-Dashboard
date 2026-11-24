
cmake_minimum_required(VERSION 3.22)

# ------------------------------------------------------------
# Compiler settings
# ------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_PROJECT_NAME G27-Dashboard)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})

message("Build type: ${CMAKE_BUILD_TYPE}")

enable_language(C)
enable_language(CXX)
enable_language(ASM)

# ------------------------------------------------------------
# STM32 executable
# ------------------------------------------------------------
add_executable(${CMAKE_PROJECT_NAME})

# STM32CubeMX-generated project
add_subdirectory(cmake/stm32cubemx)

# ------------------------------------------------------------
# LVGL library
#
# Built straight from the sources in the Drivers/lvgl submodule
# instead of through LVGL's own CMake scripts. That keeps the
# firmware build independent of LVGL's host-side tooling
# (Python config generation, Kconfig, SDL, ...).
#
# lv_conf.h lives in the project root. LV_CONF_INCLUDE_SIMPLE
# makes LVGL do a plain #include "lv_conf.h".
# ------------------------------------------------------------
set(LVGL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/lvgl)

file(GLOB_RECURSE LVGL_SOURCES CONFIGURE_DEPENDS
    ${LVGL_DIR}/src/*.c
)

add_library(lvgl STATIC ${LVGL_SOURCES})

target_include_directories(lvgl PUBLIC
    ${LVGL_DIR}                     # "lvgl.h"
    ${CMAKE_CURRENT_SOURCE_DIR}     # "lv_conf.h"
)

target_compile_definitions(lvgl PUBLIC
    LV_CONF_INCLUDE_SIMPLE          # #include "lv_conf.h"
    LV_LVGL_H_INCLUDE_SIMPLE        # #include "lvgl.h" (used by the Editor's generated code)
)

# ------------------------------------------------------------
# LVGL Editor generated UI  (Dashboard_LVGL_UI/ui -> lib-ui)
#
# Only the ui/ folder is pulled in. Dashboard_LVGL_UI/ itself is
# the PC simulator project and must NOT be added to the firmware
# build (it downloads its own LVGL and links Windows libraries).
# The lvgl target must exist before this so lib-ui links to it.
# ------------------------------------------------------------
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/Dashboard_LVGL_UI/ui
    ${CMAKE_BINARY_DIR}/lib-ui
)

# String subjects only hold short values like "10250" or "13.8",
# so 32 bytes is plenty (the generated default is 256 bytes each).
target_compile_definitions(lib-ui PUBLIC
    UI_SUBJECT_STRING_LENGTH=32
)

# ------------------------------------------------------------
# Project sources
# ------------------------------------------------------------
target_sources(${CMAKE_PROJECT_NAME} PRIVATE

    Core/Src/shiftLights.c
    Core/Src/data.c
    Core/Src/display.c

    Core/Src/fmc-display/lcd_io.c

    Core/Src/fmc-display/rpiSceneBuilderUser.cpp
    Core/Src/fmc-display/rpiDisplaySceneBuilder.cpp
    Core/Src/fmc-display/rpiDisplayShapes.c
)

# ------------------------------------------------------------
# Include directories
# (LVGL and the UI headers come in through the lvgl / lib-ui
#  targets below, so they don't need to be listed here.)
# ------------------------------------------------------------
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    Core/Inc
)

# ------------------------------------------------------------
# Link libraries
# (No PRIVATE keyword on purpose: cmake/stm32cubemx/CMakeLists.txt
#  uses the plain signature on this target, and CMake refuses to mix
#  the plain and keyword forms on the same target.)
# ------------------------------------------------------------
target_link_libraries(${CMAKE_PROJECT_NAME}

    stm32cubemx
    lib-ui
    lvgl
)

# ------------------------------------------------------------
# Remove unwanted implicit library
# ------------------------------------------------------------
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)
