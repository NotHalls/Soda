cmake_minimum_required(3.10)

project(SodaEngine)


# defining the system spesific tasks
if(WIN32)
    add_compile_definitions(SD_PLATFORM_WIN)
elseif(APPLE)
    add_compile_definitions(SD_PLATFORM_MAC)
elseif(UNIX)
    add_compile_definitions(SD_PLATFORM_LINUX)
endif()


# setting up the build dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../bin-objs/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../bin/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}")


# files of the Soda project
file(GLOB_RECURSE SODA_SOURCES "src/*.cpp" "src/*.hpp" "src/*.c" "src/*.h")
file(GLOB_RECURSE STBI_SOURCES "submodules/stb_image/*.cpp" "submodules/stb_image/*.h")

# creating the static lib
add_library(SodaEngine STATIC ${SODA_SOURCES} ${STBI_SOURCES})


# setting up libraries
add_subdirectory(submodules/glad)
add_subdirectory(submodules/glfw)
add_subdirectory(submodules/imgui)

target_link_libraries(SodaEngine PRIVATE glad glfw imgui)


# Build specific stuff
target_compile_definitions(SodaEngine PRIVATE $<$<CONFIG:Debug>:SD_DEBUG>)
target_compile_definitions(SodaEngine PRIVATE $<$<CONFIG:RELEASE>:SD_RELEASE>)
target_compile_definitions(SodaEngine PRIVATE $<$<CONFIG:Dist>:SD_DIST>)


# pre compiled header
set(PCH_HEADER "src/SD_PCH.h")
set(PCH_SOURCE "src/SD_PCH.cpp")

target_precompile_headers(SodaEngine PRIVATE ${PCH_HEADER})


# specifying the include directories
include_directories(src)
include_directories(submodules/glfw/include)
include_directories(submodules/glad/include)
include_directories(submodules/imgui)
include_directories(submodules/spdlog/include)
include_directories(submodules/glm/include)
include_directories(submodules/stb_image)