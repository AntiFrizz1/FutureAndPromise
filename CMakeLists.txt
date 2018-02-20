cmake_minimum_required(VERSION 3.8)
project(FutureAndPromise)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-D_GLIBCXX_DEBUG)
add_definitions(-D_GTEST)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

file(GLOB_RECURSE SOURCE_FILES source/*.cpp tests/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h tests/*.h)

include_directories(include)

if ("$ENV{GTEST}" STREQUAL "y")
    message("!Gtests're enabled!")

    find_package(GTest REQUIRED)

    include_directories(tests)
    add_definitions(-D_GTEST)
endif ()

set(SOURCE_FILES main.cpp include/future.h include/shared_state.h include/promise.h promise_test.cpp include/flatten.h flatten_test.cpp include/map.h include/thread_pool.h map_test.cpp include/flatten_tuple.h)
add_executable(FutureAndPromise ${SOURCE_FILES})

if ("$ENV{GTEST}" STREQUAL "y")
    target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} gmock)
endif ()

target_link_libraries(${PROJECT_NAME} pthread)

target_link_libraries(${PROJECT_NAME} gtest gtest_main)