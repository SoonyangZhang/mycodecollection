PROJECT(project)
cmake_minimum_required(VERSION 2.6)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall  -O2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-std=c++11)
include_directories(${CMAKE_SOURCE_DIR}/)

set(task_queue_FILES
criticalsection.cc
platform_thread.cc 
platform_thread_types.cc
taskqueue.cc
timeutils.cc
)
add_library(task_queue STATIC ${task_queue_FILES})
set(EXECUTABLE_NAME "test")
add_executable(${EXECUTABLE_NAME} main.cc)
target_link_libraries(${EXECUTABLE_NAME} task_queue  pthread)
