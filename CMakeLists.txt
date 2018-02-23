cmake_minimum_required(VERSION 2.6)

# Project name
project(YAP)

# TODO: Setup version numbers
#set(VERSION_MAJOR 0)
#set(VERSION_MINOR 0)
#set(VERSION_PATCH 1)

option(BUILD_TESTS "Whether to generate the tests or not." ON)
option(BUILD_DOC "Whether to generate the documentation or not." ON)
option(BUILD_EXAMPLES "Whether to generate the examples or not." ON)

# Change the required C++ standard
set(CMAKE_CXX_STANDARD 17)

# Make the compiler more strict
set(CXX_STRICT_WARNINGS "-fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall -Werror -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Winit-self")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_STRICT_WARNINGS}")

# Add the YAP header path
message(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add the subdirectories
add_subdirectory(src/YAP)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
#if(BUILD_DOC)
#    add_subdirectory(doc)
#endif()

# Configure the library
file(GLOB YAP_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/YAP/*" "src/YAP/*")
set(YAP_SOURCES ${YAP_HEADERS})
add_library(YAP ${YAP_SOURCES})
