cmake_minimum_required(VERSION 3.0.0)
project(bubblesort VERSION 0.1.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(CTest)
enable_testing()

add_executable(bubblesorttest bubblesort/bubbletest.cpp)
add_executable(quicksorttest quicksort/quicktest.cpp)
add_executable(bubblesortbenchmark bubblesort/bubblebenchmark.cpp)
add_executable(quicksortbenchmark quicksort/quicksortbenchmark.cpp)

target_link_libraries(bubblesorttest PRIVATE ${CONAN_LIBS})
target_link_libraries(quicksorttest PRIVATE ${CONAN_LIBS})
target_link_libraries(bubblesortbenchmark PRIVATE ${CONAN_LIBS})
target_link_libraries(quicksortbenchmark PRIVATE ${CONAN_LIBS})

add_test(NAME bubblesorttest COMMAND bubblesorttest)
add_test(NAME quicksorttest COMMAND quicksorttest)

target_compile_options(bubblesortbenchmark PRIVATE -Wall -Wextra -Werror -pedantic -Weffc++ -Ofast)
target_include_directories(bubblesortbenchmark PRIVATE .)
target_include_directories(bubblesorttest PRIVATE .)
target_compile_options(quicksortbenchmark PRIVATE -Wall -Wextra -Werror -pedantic -Weffc++ -Ofast)
target_include_directories(quicksortbenchmark PRIVATE .)
target_include_directories(quicksorttest PRIVATE .)

set_target_properties(bubblesorttest bubblesortbenchmark quicksortbenchmark quicksorttest PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    )

add_custom_target(quick
    COMMAND 
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/quicksortbenchmark --benchmark_out_format=json --benchmark_out=${PROJECT_SOURCE_DIR}/quick.json
    DEPENDS
        .${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/quicksortbenchmark
    BYPRODUCTS
        ${PROJECT_SOURCE_DIR}/quick.json)

add_custom_target(bubble
    COMMAND 
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bubblesortbenchmark --benchmark_out_format=json --benchmark_out=${PROJECT_SOURCE_DIR}/bubble.json
    DEPENDS
        .${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bubblesortbenchmark
    BYPRODUCTS
        ${PROJECT_SOURCE_DIR}/bubble.json)

add_custom_target(plotter
   COMMAND
        mvn clean compile assembly:single
   WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}/plotter/speed_plotter)

add_custom_target(graph
   COMMAND
        java -cp target/speed_plotter-1.0-jar-with-dependencies.jar bubblesort.App ${PROJECT_SOURCE_DIR}/quick.json ${PROJECT_SOURCE_DIR}/bubble.json
   WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}/plotter/speed_plotter
   DEPENDS
        plotter quick bubble)
