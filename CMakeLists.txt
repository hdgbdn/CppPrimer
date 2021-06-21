cmake_minimum_required(VERSION 3.20)
project("CppPrimer")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB children ABSOULTE "${CMAKE_CURRENT_LIST_DIR}/src/*")
foreach(child ${children})
    if(IS_DIRECTORY ${child})
        add_subdirectory(${child})
    endif()
endforeach()
