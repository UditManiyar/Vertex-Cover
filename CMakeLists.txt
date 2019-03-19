cmake_minimum_required(VERSION 3.10)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(Pace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#" -Wall")

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(EXECUTABLE_NAME "pace")


include_directories(include/)
file(GLOB_RECURSE SOURCES "src/*.cpp")
set(SOURCES ${SOURCES} "main.cpp")

add_executable(${EXECUTABLE_NAME} ${SOURCES})


target_link_libraries(${EXECUTABLE_NAME})
