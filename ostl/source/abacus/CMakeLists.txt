cmake_minimum_required(VERSION 3.19)

set(library_name "abacus")

project(
    ${library_name}
    VERSION 1.0
    LANGUAGES CXX
)

include(make-library)

make_library(${library_name} ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(
  ${library_name}
  PRIVATE
)
