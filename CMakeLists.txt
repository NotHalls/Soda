cmake_minimum_required(VERSION 3.10)

project(Soda)


# setting the CXX standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# setting up the compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
# no clang compiler
if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "clang" OR NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "clang++")
    message(FATAL_ERROR "Error: SodaEngine shall be compiled with the clang compiler")
endif()


# setting the default build-type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose A Build-Type (Debug | Release | Dist)" FORCE)
endif()
# setting the build configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "Supported Build Types" FORCE)

# compiler optimizations
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} -03")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -03")
set(CMAKE_C_FLAGS_DIST      "${CMAKE_C_FLAGS_DIST} -03")
set(CMAKE_CXX_FLAGS_DIST    "${CMAKE_CXX_FLAGS_DIST} -03")


# @TESTING: maybe we need to add_library(..) here


# adding the subdirectories
add_subdirectory(SodaEngine)
add_subdirectory(SodaCan)
add_subdirectory(TestingGrounds)