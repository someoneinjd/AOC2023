cmake_minimum_required(VERSION 3.24)
project(aoc2023 LANGUAGES CXX)

if(APPLE)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE full_version_string)
    string(REGEX REPLACE "([A-Za-z]+) clang version.*" "\\1" HOMEBREW_CLANG ${full_version_string})
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

string(REPLACE "-O3" "-O2" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

foreach(day RANGE 1 25)
    if(${day} LESS "10")
        string(PREPEND day "day0")
    else()
        string(PREPEND day "day")
    endif()
    add_executable(${day} "${CMAKE_CURRENT_SOURCE_DIR}/src/${day}.cpp")
    target_include_directories(${day} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    if(APPLE AND (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
        target_include_directories(${day} PRIVATE "/usr/local/opt/llvm/include/c++/v1")
        target_link_directories(${day} PRIVATE "/usr/local/opt/llvm/lib/c++/")
    endif()
    target_compile_options(${day} PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>,/W4,-Wall>
                                          $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>
                                          $<$<CXX_COMPILER_ID:MSVC>:/constexpr:steps16777216>
                                          $<$<CXX_COMPILER_ID:AppleClang,Clang>:-fconstexpr-steps=16777216>
                                          $<$<CXX_COMPILER_ID:GNU>:-fconstexpr-loop-limit=16777216 -fconstexpr-ops-limit=16777216>)
endforeach()
