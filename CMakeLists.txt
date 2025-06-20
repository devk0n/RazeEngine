cmake_minimum_required(VERSION 3.20)

project(RazeEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies (using system packages)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

# Manually add Eigen include path
include_directories("/usr/include/eigen3")

# Gather sources
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
set(INCLUDE_DIRS "")
foreach(header ${HEADERS})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        Vulkan::Vulkan
)

