cmake_minimum_required(VERSION 3.10.0)
project(physgui VERSION 0.1.0 LANGUAGES C CXX)


add_library(physgui STATIC  src/phys_runner/cross_platform_runner.cpp
                            src/phys_runner/native_runner.cpp
                            src/phys_runner/cross_platform_runner.cpp
                            src/phys_runner/game_loop.cpp
                            src/phys_backend/app_window.cpp
                            src/phys_backend/imgui_manager.cpp
                            src/phys_backend/open_gl_context.cpp
                            src/phys_backend/sdl_backend.cpp)

add_library(physgui::physgui ALIAS physgui) 

target_include_directories(physgui PUBLIC include)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

message(STATUS "Adding source files & imgui sdl2 backend")

option(FETCH_IMGUI OFF)

 

if(FETCH_IMGUI)
    message(STATUS "building imgui from FetchContent")
    add_subdirectory(vendors/imgui_gl3_sdl2)
else()
    message(STATUS "building imgui from local folder")
    add_subdirectory(vendors/imgui)
endif()

 
if (PLATFORM STREQUAL "desktop") 
    find_library(glad QUIET)
    if (NOT glad_FOUND)
        message(STATUS "glad not found.")
        add_subdirectory(vendors/glad)
    else()
        message(STATUS "glad found.")
    endif()

    find_package(SDL2 QUIET)
    if (NOT SDL2_FOUND)
        message(FATAL_ERROR "SDL2 not found.")
    else()
        message(STATUS "SDL2 found.")
    endif()
endif()
 
target_compile_features(physgui PRIVATE cxx_std_23)

 
if (PLATFORM STREQUAL "Web")
    message(STATUS "Web build: only linking to imgui")

    target_compile_definitions(physgui PUBLIC __EMSCRIPTEN__ IMGUI_IMPL_OPENGL_ES2)
    target_link_libraries     (physgui PUBLIC imgui)
     
elseif(PLATFORM STREQUAL "desktop")
    message(STATUS "Building PhysGui for desktop")

    target_link_libraries  (physgui PUBLIC SDL2::Main
                                                imgui
                                                glad)

endif()
 



