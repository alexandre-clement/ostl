cmake_minimum_required(VERSION 3.10)

set(executable_name "abacus-test")

project(
    ${executable_name}
    VERSION 1.0
    LANGUAGES CXX
)

include(make-testsuite)

make_testsuite(${executable_name} ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(
  ${executable_name}
  PUBLIC
      abacus
      GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main
)
