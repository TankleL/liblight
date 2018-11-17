set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#-------------------------------------------------------------------#
#                               GLFW                                #
#-------------------------------------------------------------------#
link_libraries(glfw)
include_directories(${glfw_INCLUDE_DIRS})

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories("${GLFW_SOURCE_DIR}/deps")


set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
         "${GLFW_SOURCE_DIR}/deps/glad.c")				

				
#-------------------------------------------------------------------#
#                           test liblight                           #
#-------------------------------------------------------------------#
aux_source_directory(. SRCS)
add_definitions (-std=c++11)
add_executable(test ${SRCS} ${GLAD})
target_link_libraries(test light)