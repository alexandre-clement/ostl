cmake_minimum_required(VERSION 3.10)

set(library_name "caldera")

project(
    ${library_name}
    VERSION 1.0
    LANGUAGES CXX
)

execute_process(
  COMMAND git --no-pager log -1 --format=%cd --date=format:%G%m%d
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE CALDERA_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "\t\tAdding definition -DCALDERA_VERSION=${CALDERA_VERSION}")
add_definitions("-DCALDERA_VERSION=${CALDERA_VERSION}")

include(make-library)

make_library(${library_name} ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(
  ${library_name}
  PUBLIC
      detail
      abacus
      glass
      Vulkan::Vulkan
      glfw ${GLFW_LIBRARIES}
      glslang::SPIRV glslang::glslang
)