cmake_minimum_required(VERSION 3.10.0)
project(wolff_simulation VERSION 0.1.0 LANGUAGES C CXX)


add_executable(wolff_simulation src/raylib_array_2d/raylib_array_2d.cpp
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
                                src/main.cpp)

target_compile_features   (wolff_simulation PRIVATE cxx_std_23)
target_include_directories(wolff_simulation PRIVATE Spin2D)
target_include_directories(wolff_simulation PRIVATE RayGuiWrapper)
target_include_directories(wolff_simulation PRIVATE include)
target_link_libraries     (wolff_simulation PRIVATE raylib)