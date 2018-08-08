cmake_minimum_required (VERSION 2.8)
project (liblight)
add_definitions (-std=c++11)
aux_source_directory (src DIR_SRCS)

add_library (light SHARED ${DIR_SRCS})

