cmake_minimum_required(VERSION 3.20)
project("CppPrimer")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/3rd/fmt")

macro(ADD_SINGLE_FILE_TARGET SOURCES_FILE)
    get_filename_component(SOURCES_FILE_NAME ${SOURCES_FILE} NAME_WE)
    add_executable(${SOURCES_FILE_NAME} "${SOURCES_FILE}")
    target_link_libraries(${SOURCES_FILE_NAME} fmt)
endmacro(ADD_SINGLE_FILE_TARGET SOURCES_FILE)

file(GLOB children ABSOULTE "${CMAKE_CURRENT_LIST_DIR}/src/*")
foreach(child ${children})
    if(IS_DIRECTORY ${child})
        add_subdirectory(${child})
    endif()
endforeach()
