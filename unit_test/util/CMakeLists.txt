cmake_minimum_required(VERSION 3.0)

project(zcv_gtest_util)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ZCV_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

find_package(GTest REQUIRED)
include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${ZCV_DIR}/include
    )

add_executable(gtest_tinydir_more
    ${CMAKE_CURRENT_LIST_DIR}/gtest_main_tinydir_more.cpp
    ${ZCV_DIR}/src/util/tinydir_more.cpp
    )

target_link_libraries(gtest_tinydir_more
    ${GTEST_LIBRARIES}
    pthread
    )
