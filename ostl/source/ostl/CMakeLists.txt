cmake_minimum_required(VERSION 3.10)

set(library_name "ostl")

project(
    ${library_name}
    VERSION 1.0
    LANGUAGES CXX
)

include(make-executable)

make_executable(${library_name} ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(
  ${library_name}
  PRIVATE
    Vulkan::Vulkan
)