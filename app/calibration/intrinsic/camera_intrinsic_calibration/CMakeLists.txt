cmake_minimum_required(VERSION 3.0)

project(demo_opencv_intrisic_calibration)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ZCV_DIR ../../../..)

find_package(OpenCV)
message("${OpenCV_INCLUDE_DIRS}")

include_directories(
    ${ZCV_DIR}/include
    ${ZCV_DIR}/3rd-party
    ${OpenCV_INCLUDE_DIRS}
    )

add_executable(
    camera_intrinsic_calibration
    camera_calibration.cpp
    ${ZCV_DIR}/src/util/zcv_log.c
    ${ZCV_DIR}/src/util/basic_ret_code_string.c
    ${BACKWARD_ENABLE}
    )

target_link_libraries(
    camera_intrinsic_calibration
    ${OpenCV_LIBS}
    dw
    )
