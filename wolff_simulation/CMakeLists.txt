cmake_minimum_required(VERSION 3.10.0)
# project(wolff_simulation VERSION 0.1.0 LANGUAGES C CXX)


add_executable(wolff_simulation  main.cpp
							src/wolff_algorithms/base_wolff_algorithm.cpp
							src/wolff_algorithms/single_spin_wolff_algorithm.cpp
							src/wolff_algorithms/full_wolff_algorithm.cpp
							src/spin_handlers/abstract_spin_handler.cpp
							src/spin_handlers/automatic_spin_handler/full_automatic_cluster_creator.cpp
							src/spin_handlers/automatic_spin_handler/single_spin_automatic_cluster_creator.cpp
							src/spin_handlers/automatic_spin_handler.cpp
							src/spin_handlers/manual_spin_handler/full_manual_cluster_creator.cpp
							src/spin_handlers/manual_spin_handler/manual_controller.cpp
							src/spin_handlers/manual_spin_handler/single_spin_manual_cluster_creator.cpp
							src/spin_handlers/manual_spin_handler.cpp
							src/wolff_finite_state_machine.cpp
							src/imgui_array_2d/my_gui_array.cpp)
							
target_include_directories(wolff_simulation PRIVATE include)
target_include_directories(wolff_simulation PRIVATE periodic_array_2d)
target_include_directories(wolff_simulation PRIVATE app)


if (PLATFORM STREQUAL "Web")
 
    set_target_properties(wolff_simulation PROPERTIES OUTPUT_NAME "index") 
    set_target_properties(wolff_simulation PROPERTIES SUFFIX      ".html") 

    # For esmcripten:
    set(EMS -sUSE_SDL=2 -sDISABLE_EXCEPTION_CATCHING=1 )

    # For the linker:
    set(LDFLAGS "-s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1") # -s NO_FILESYSTEM=1")

    target_link_options(wolff_simulation PUBLIC ${EMS}
                                    ${LDFLAGS}
                                    --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/fonts@/fonts
                                    --shell-file   ${CMAKE_CURRENT_SOURCE_DIR}/web/imgui_shell.html)

    target_compile_options(wolff_simulation PUBLIC ${EMS})
    
    # For github:
    add_custom_command(
        TARGET wolff_simulation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:wolff_simulation>/index.html ${CMAKE_SOURCE_DIR}/docs/index.html)

    add_custom_command(
        TARGET wolff_simulation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:wolff_simulation>/index.js ${CMAKE_SOURCE_DIR}/docs/index.js)

    add_custom_command(
        TARGET wolff_simulation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:wolff_simulation>/index.wasm ${CMAKE_SOURCE_DIR}/docs/index.wasm)

    add_custom_command(
        TARGET wolff_simulation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:wolff_simulation>/index.data ${CMAKE_SOURCE_DIR}/docs/index.data)


elseif (PLATFORM STREQUAL "desktop")
    message(STATUS "Building PhysGui for Desktop")
    
    # Move fonts to binary dir 
    add_custom_command(
        TARGET wolff_simulation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:wolff_simulation>/fonts)
endif()

target_compile_features(wolff_simulation PRIVATE cxx_std_23)
target_link_libraries  (wolff_simulation PUBLIC physgui::physgui)

 