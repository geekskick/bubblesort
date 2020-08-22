cmake_minimum_required(VERSION 3.0.0)
project(bubblesort VERSION 0.1.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(bubblesorttest test.cpp)
add_executable(bubblebenchmark benchmark.cpp)

target_link_libraries(bubblesorttest PRIVATE ${CONAN_LIBS})
target_link_libraries(bubblebenchmark PRIVATE ${CONAN_LIBS})

set_target_properties(bubblesorttest bubblebenchmark PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    )

