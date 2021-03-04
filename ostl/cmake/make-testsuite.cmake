macro(make_testsuite _testsuite_name _directory)
    file(GLOB_RECURSE source_files_list "${_directory}/src/*.cpp" "${_directory}/src/*.hpp")
    add_executable(${_testsuite_name} ${source_files_list})
    target_compile_features(${_testsuite_name} PUBLIC ${cxx_version})

    include(warning)
    set_project_warnings(${_testsuite_name})

    include(GoogleTest)

    gtest_add_tests(
        TARGET
            ${_testsuite_name}
        TEST_LIST
            ${_testsuite_name}
        WORKING_DIRECTORY
            ${_directory}
    )

endmacro()