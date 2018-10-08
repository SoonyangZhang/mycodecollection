PROJECT(project)
cmake_minimum_required(VERSION 2.6)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall  -O2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DNS3_LOG_ENABLE)
add_definitions(-std=c++11)
include_directories(${CMAKE_SOURCE_DIR}/ns3log)
set(log_FILES
${CMAKE_SOURCE_DIR}/ns3log/log.cc
${CMAKE_SOURCE_DIR}/ns3log/fatal-impl.cc
)
add_library(ns3log STATIC ${log_FILES})
set(EXECUTABLE_NAME "t_log")
add_executable(${EXECUTABLE_NAME} ${CMAKE_SOURCE_DIR}/main.cc)
target_link_libraries(${EXECUTABLE_NAME} ns3log)
