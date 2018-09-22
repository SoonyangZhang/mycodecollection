PROJECT(project)
cmake_minimum_required(VERSION 2.6)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall  -O2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")
set(CMAKE_CXX_FLAGS "-fPIC")  
set(CMAKE_C_FLAGS "-fPIC") 
add_definitions(-std=c++11  )#-fno-rtti
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(.)
set(tcp_base_FILES
eventloop.cc
tcpcon.cc
tcplistener.cc
tcp.cc
)
add_library(tcp_base STATIC ${tcp_base_FILES})
set(EXECUTABLE_NAME "tcpserver")
add_executable(${EXECUTABLE_NAME} main.cc)
target_link_libraries(${EXECUTABLE_NAME} tcp_base)
set(EXECUTABLE_NAME "fileclient")
add_executable(${EXECUTABLE_NAME} filetransfer.cc)
