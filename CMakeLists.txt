cmake_minimum_required (VERSION 2.8)
project (liblight)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(tools/glfw)
add_subdirectory(test)

include_directories(inc)
FILE(GLOB_RECURSE HPP_LIST "inc/*.hpp")
aux_source_directory (src DIR_SRCS)


#-------------------------------------------------------------------#
#                             liblight                              #
#-------------------------------------------------------------------#
add_library (light SHARED ${DIR_SRCS} ${HPP_LIST})


#-------------------------------------------------------------------#
#                             install                               #
#-------------------------------------------------------------------#
install(TARGETS light DESTINATION lib)
install(DIRECTORY inc/ DESTINATION inc/)
install(DIRECTORY tools/math/inc/ DESTINATION tools/math/inc/)

