cmake_minimum_required(VERSION 3.20)
project("Query")

add_executable(${PROJECT_NAME} main.cpp "AndQuery.h"  "OrQuery.h")
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

install(FILES "text.txt"
    DESTINATION Debug/)