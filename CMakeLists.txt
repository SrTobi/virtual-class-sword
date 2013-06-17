cmake_minimum_required( VERSION 2.8 )

project(virtual-class-sword)


#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")



################### setup options ###################
set(Option_DEFAULT_MAKE_DOXYGEN_TARGET ON)

if(MSVC)
set(Boost_USE_STATIC_LIBS ON)
set(Option_DEFAULT_MAKE_DOXYGEN_TARGET OFF)
endif(MSVC)


option(vcs_USE_PRE_COMPILED_HEADER		"Use precompiled header for compilation" ON)
option(vcs_MAKE_DOXYGEN_TARGET			"Create a doxygen build target" ${Option_DEFAULT_MAKE_DOXYGEN_TARGET})


################### setup pre compiled header macro ###################
if(vcs_USE_PRE_COMPILED_HEADER)
	add_subdirectory("extras/pch")
	add_definitions(-DVCS_USE_PRECOMPILED_HEADER)
else(vcs_USE_PRE_COMPILED_HEADER)

	# simply set an empty macro
	macro(ADD_PRECOMPILED_HEADER _targetName _input)
	endmacro()

endif(vcs_USE_PRE_COMPILED_HEADER)

################### add c++11 support ###################
if(NOT MSVC)
	add_definitions("-std=c++0x")
endif(NOT MSVC)


################### set definitions ###################
if(NOT Boost_USE_STATIC_LIBS)
	add_definitions(-DBOOST_TEST_DYN_LINK) 
endif(NOT Boost_USE_STATIC_LIBS)
add_definitions( -DBOOST_ALL_NO_LIB )


################### find packages ###################
find_package(Boost COMPONENTS system thread serialization unit_test_framework filesystem REQUIRED)


################### setup target directories ###################
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)



################### add c++11 support ###################
set(vcs_pch_file				"${PROJECT_SOURCE_DIR}/library/includes.hpp")


################### setup additional include directories ###################
include_directories(${Boost_INCLUDE_DIRS})


################### setup link directories ###################
link_directories(${Boost_LIBRARY_DIRS})
link_directories(${BOOST_LIBRARYDIR})

################### set dependencies for vcs ###################
set(vcs_dependency_libs ${Boost_LIBRARIES})


################### setup media copy support ###################

function(NEED_MEDIA _target _resource)
	
		set(res "${PROJECT_SOURCE_DIR}/media/${_resource}")
		
		if(NOT EXISTS ${res})
			message(SEND_ERROR "[${_resource}] does not exist in media!")
		endif()
		
		if(IS_DIRECTORY ${res})
			set(copy_command  copy_directory)
		else()
			set(copy_command copy_if_different)
		endif()

		add_custom_command(	TARGET ${_target} POST_BUILD
							COMMAND ${CMAKE_COMMAND} -E ${copy_command}
							${res}
							$<TARGET_FILE_DIR:${_target}>)
endfunction()

################### add directories with source###################
add_subdirectory(src)



################### setup documentation target ###################
# add a target to generate API documentation with Doxygen
if(vcs_MAKE_DOXYGEN_TARGET)
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc.doxy ${CMAKE_CURRENT_BINARY_DIR}/doc.doxy @ONLY)
		add_custom_target(documentation ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc.doxy
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	endif(DOXYGEN_FOUND)
endif(vcs_MAKE_DOXYGEN_TARGET)
