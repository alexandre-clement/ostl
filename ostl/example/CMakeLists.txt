cmake_minimum_required(VERSION 3.19)

include(subdirectory-glob)

message(STATUS "including ostl examples :")
glob_subdirectory(${CMAKE_CURRENT_SOURCE_DIR})
