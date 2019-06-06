cmake_minimum_required (VERSION 2.8.11)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14")
#message("UBEDEBUG: CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")

SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_SOURCE_DIR})
#LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/sm_lib ${CMAKE_BINARY_DIR}/sm_filter)

project (sm01)

#add_subdirectory (sm_lib)
add_subdirectory (test01)

