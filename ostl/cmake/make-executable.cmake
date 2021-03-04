macro(make_executable _executable_name _directory)
    file(GLOB_RECURSE source_files_list "${_directory}/src/*.cpp" "${_directory}/src/*.hpp")
    add_executable(${_executable_name} ${source_files_list} )
    target_compile_features(${_executable_name} PUBLIC ${cxx_version})

    include(warning)
    set_project_warnings(${_executable_name})
endmacro()