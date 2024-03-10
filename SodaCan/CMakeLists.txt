cmake_minimum_required(3.10)

project(SodaCan)


# setting up the build dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../bin-objs/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../bin/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}")


# adding files
file(GLOB_RECURSE SodaCan_SOURCES "src/*.cpp" "src/*.hpp" "src/*.c" "src/*.h")

# creating the exec
add_executable(SodaCan ${SodaCan_SOURCES})


# linking the Soda lib
add_subdirectory(../SodaEngine)

target_link_libraries(SodaCan PRIVATE SodaEngine)