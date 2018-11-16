cmake_minimum_required (VERSION 2.8)
project (liblight)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions (-std=c++11)
include_directories(inc)
aux_source_directory (src DIR_SRCS)

add_subdirectory(tools/glfw)
add_subdirectory(test)

#-------------------------------------------------------------------#
#                             liblight                              #
#-------------------------------------------------------------------#
add_library (light SHARED ${DIR_SRCS})


#-------------------------------------------------------------------#
#                             install                               #
#-------------------------------------------------------------------#
install(TARGETS light DESTINATION lib)
install(DIRECTORY inc/ DESTINATION inc/)
install(DIRECTORY tools/math/inc/ DESTINATION tools/math/inc/)

