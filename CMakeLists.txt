cmake_minimum_required(VERSION 3.10.2)

# VARIABLES
set(AUTHOR_NAME "Mert Acel")
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME "Data_Formating")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(BOOST_PATH "${CMAKE_SOURCE_DIR}/../boost/boost_1_68_0/")

# Set g++ Parameter
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra ")

# Project Information
project(${PROJECT_NAME} VERSION 1.0.1 DESCRIPTION ${PROJECT_NAME})

# Information
message(STATUS "AUTHOR_NAME          : ${AUTHOR_NAME}")
message(STATUS "PROJECT_NAME         : ${PROJECT_NAME}")
message(STATUS "CMAKE_SOURCE_DIR     : ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_SYSTEM         : ${CMAKE_SYSTEM}")

# Include Folders
include_directories(${BOOST_PATH}/include)

# Library Path
link_directories(${BOOST_PATH}/lib)

set(SOURCE_FILES src/main.cpp src/db/MySQL.cpp src/db/MySQL.hpp src/system/SystemCommand.cpp src/system/SystemCommand.hpp src/stringOp/StringOp.cpp src/stringOp/StringOp.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} mysqlcppconn)