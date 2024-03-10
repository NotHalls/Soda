cmake_minimum_required(3.10)

project(glad)


# creating the lib
add_library(glad STATIC src/glad.c)


# setting the include dirs
target_include_directories(glad PUBLIC include)