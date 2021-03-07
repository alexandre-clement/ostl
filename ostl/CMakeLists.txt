cmake_minimum_required(VERSION 3.10)

project(
    "OSTL"
    VERSION 1.0
    LANGUAGES CXX
    DESCRIPTION "OSTL is an open source C++ sphere tracing library."
)

set(cxx_version cxx_std_20)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

include(${CMAKE_TOOLCHAIN_FILE})

enable_testing()

find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glfw3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory("source")
add_subdirectory("test")
add_subdirectory("example")

