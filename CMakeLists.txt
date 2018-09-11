cmake_minimum_required(VERSION 3.12)
project(photo_processing)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        "H:\\source\\boost_1_68_0"
        "G:\\Downloads\\OpenCV\\opencv\\build\\include"
        "H:\\source\\RxCpp-4.1.0\\Rx\\v2\\src")

link_directories(
        "H:\\source\\boost_1_68_0\\lib64-msvc-14.1"
        "G:\\Downloads\\OpenCV\\opencv\\build\\x64\\vc15\\lib")

link_libraries("opencv_world341d.lib")

add_executable(photo_processing main.cpp thread_pool.cpp)