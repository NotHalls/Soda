cmake_minimum_required(VERSION 3.10)


# adding files
file(GLOB_RECURSE SodaCan_SOURCES "src/*.cpp" "src/*.hpp" "src/*.c" "src/*.h")

# creating the exec
add_executable(SodaCan ${SodaCan_SOURCES})


# Build specific stuff
target_compile_definitions(SodaCan PUBLIC $<$<CONFIG:Debug>:SD_DEBUG>)
target_compile_definitions(SodaCan PUBLIC $<$<CONFIG:RELEASE>:SD_RELEASE>)
target_compile_definitions(SodaCan PUBLIC $<$<CONFIG:Dist>:SD_DIST>)


# linking the Soda lib
# add_subdirectory(../SodaEngine)
target_link_libraries(SodaCan PRIVATE SodaEngine)
# link_libraries(SodaEngine)


# include directories that includes the SodaEngine
include_directories(../SodaEngine/submodules/spdlog/include)
include_directories(../SodaEngine/src)
include_directories(../SodaEngine/submodules/glm)
include_directories(../SodaEngine/submodules/imgui)