cmake_minimum_required(VERSION 3.10)

project(bfprt-qsort)

find_package(GTest REQUIRED)

add_executable(samples/sort samples/sort.cc)
add_executable(samples/profile samples/profile.cc)

add_executable(test_bfprt_qsort tests/test_bfprt_qsort.cc)
target_link_libraries(test_bfprt_qsort GTest::GTest GTest::Main)
