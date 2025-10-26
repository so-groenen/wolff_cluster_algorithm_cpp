# include(FetchContent)
cmake_minimum_required(VERSION 3.10.0)
project(glad VERSION 0.1.0 LANGUAGES C CXX)

add_library(glad STATIC src/glad.c)
# add_library(glad::glad ALIAS glad)
target_include_directories(glad PUBLIC include)
 