cmake_minimum_required(VERSION 3.21)

project(
    rockets
    VERSION 1.0.0
    DESCRIPTION "General-purpose game engine"
    LANGUAGES CXX
)


if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Build type not specified. Defaulting to Debug.")

    set(
        CMAKE_BUILD_TYPE
        Debug
        CACHE STRING "Build type"
        FORCE
    )

    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
            Debug
            Release
            RelWithDebInfo
            MinSizeRel
    )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)


set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/third_party/imgui")

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(
    imgui
    PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

target_compile_features(imgui PUBLIC cxx_std_20)

target_link_libraries(
    imgui
    PUBLIC
        SDL3::SDL3
)


file(
    GLOB_RECURSE ENGINE_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(rockets ${ENGINE_SOURCES})

target_compile_features(
    rockets
    PRIVATE
        cxx_std_20
)

target_include_directories(
    rockets
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    rockets
    PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        imgui
)

target_compile_definitions(
    rockets
    PRIVATE
        ROCKETS_ASSET_DIR="${CMAKE_SOURCE_DIR}/assets"
)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(
        rockets
        PRIVATE

            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wconversion
            -Wsign-conversion
            -Wnon-virtual-dtor

            $<$<CONFIG:Debug>:-g3>
            $<$<CONFIG:Debug>:-O0>

            $<$<CONFIG:Release>:-O2>

            $<$<CONFIG:RelWithDebInfo>:-O2;-g>
    )

elseif(MSVC)

    target_compile_options(
        rockets
        PRIVATE
            /W4
            /permissive-
    )

endif()


message(STATUS "")
message(STATUS "  ┌──────────────────────────────────────────┐")
message(STATUS "  │ Rockets ${PROJECT_VERSION}")
message(STATUS "  │")
message(STATUS "  │ Configuration : ${CMAKE_BUILD_TYPE}")
message(STATUS "  │ Compiler      : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  │ Build Dir     : ${CMAKE_BINARY_DIR}")
message(STATUS "  │ Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  └──────────────────────────────────────────┘")
message(STATUS "")
