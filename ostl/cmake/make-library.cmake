macro(make_library _library_name _directory)
	file(GLOB header_files_list CONFIGURE_DEPENDS "${_directory}/include/*")
	file(GLOB_RECURSE source_files_list "${_directory}/src/*.cpp" "${_directory}/src/*.hpp")

	add_library(${_library_name} ${source_files_list} ${header_files_list})
	target_include_directories(${_library_name} PUBLIC "include")
	target_compile_features(${_library_name} PUBLIC ${cxx_version})

    include(warning)
    set_project_warnings(${_library_name})
endmacro()