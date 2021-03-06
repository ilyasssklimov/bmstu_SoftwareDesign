cmake_minimum_required (VERSION 3.10)
project(klimov_ilya)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

option(WITH_TESTS "Build tests")
if (WITH_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    set(BUILD_TESTS ON)
endif()

add_subdirectory(lib/logger)
add_subdirectory(lib/business_logic)
add_subdirectory(lib/data_access_layer)

add_executable(main src/main.cpp)
target_link_libraries(main business_logic)
target_link_libraries(main data_access_layer)
