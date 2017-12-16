cmake_minimum_required(VERSION 2.6)


include(CheckCXXCompilerFlag)

project(tsc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB APP_SOURCES "src/[a-zA-Z]*.cpp")

include_directories(${tsc_SOURCE_DIR})

set(SOURCES
    ${APP_SOURCES}
)

add_definitions("-Wall -std=c++11")
add_executable(tsc ${SOURCES})


