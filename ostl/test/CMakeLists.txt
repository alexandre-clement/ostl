cmake_minimum_required(VERSION 3.10)

include(subdirectory-glob)

message(STATUS "including tests :")
glob_subdirectory(${CMAKE_CURRENT_SOURCE_DIR})
