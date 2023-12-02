cmake_minimum_required(VERSION 3.20)

find_program(CLANG "clang" REQUIRED)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
execute_process(COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE clang_full_version_string)
string(REGEX REPLACE ".*clang version ([0-9]+\\.[0-9]+).*" "\\1" CLANG_VERSION_STRING ${clang_full_version_string})
if(CLANG_VERSION_STRING VERSION_LESS 17.0.0)
    message(FATAL "clang 17+ is required, current version = ${CLANG_VERSION_STRING}")
endif()

if(APPLE)
    string(REGEX REPLACE "([A-Za-z]+) clang version.*" "\\1" HOMEBREW_CLANG ${clang_full_version_string})
endif()

project(aoc2023)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

foreach(day IN ITEMS day01)
    add_executable(${day} "${CMAKE_CURRENT_SOURCE_DIR}/src/${day}.cpp")
    if(APPLE AND (${HOMEBREW_CLANG} STREQUAL "Homebrew"))
        target_include_directories(${day} PRIVATE "/usr/local/opt/llvm/include/c++/v1")
        target_link_directories(${day} PRIVATE "/usr/local/opt/llvm/lib/c++/")
    endif()
    target_compile_options(${day} PRIVATE -fdiagnostics-color=always -Wall -O2 -fconstexpr-steps=16777216)
endforeach()
