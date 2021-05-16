cmake_minimum_required(VERSION 3.19)

set(executable_name "sphere")

project(
    ${executable_name}
    VERSION 1.0
    LANGUAGES CXX
)

include(make-executable)

make_executable(${executable_name} ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(
  ${executable_name}
  PUBLIC
    ostl
)
