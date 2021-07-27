cmake_minimum_required(VERSION 3.10)

project(bfprt-qsort)

set(CMAKE_CXX_STANDARD 11)
find_package(GTest REQUIRED)

add_executable(sort samples/sort.cc)
add_executable(profile samples/profile.cc)
set_target_properties(sort profile PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/samples/")

add_executable(test_bfprt_qsort tests/test_bfprt_qsort.cc)
target_link_libraries(test_bfprt_qsort GTest::GTest GTest::Main)

include_directories(sort PRIVATE include/)