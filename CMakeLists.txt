cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_CXX_STANDARD 23)

project(ALog VERSION 0.0.1)

include(cmake/FindBenchmark.cmake)
include(cmake/FindGTest.cmake)
enable_testing()

include(cmake/SanitizersFlags.cmake)

# ========================================
# Add config header
# ========================================
include_directories(./inc)
include(cmake/ConfigParams.cmake)

# ========================================
# Static library
# ========================================
set(LIB_NAME alog)
file(GLOB_RECURSE LIB_SRC "src/*.cpp")
add_library(${LIB_NAME} STATIC ${LIB_SRC})
target_include_directories(${LIB_NAME} PUBLIC ./inc)
target_include_directories(${LIB_NAME} PUBLIC ./inc/gen/config/)

# ========================================
# Unit tests
# ========================================
set(UNIT_TEST ${LIB_NAME}_ut)
file(GLOB_RECURSE UNIT_TEST_SRC "test/unit/*.ut.cpp")
add_executable(${UNIT_TEST} ${UNIT_TEST_SRC})

target_link_libraries(${UNIT_TEST} PRIVATE
        GTest::gtest_main
        ${LIB_NAME}
)

include(GoogleTest)
gtest_discover_tests(${UNIT_TEST}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/unit/
)

# ========================================
# Functional tests
# ========================================
# Log all logger levels
add_executable(Logger.levels.ft test/func/LoggerLevels.ft.cpp)
target_link_libraries(Logger.levels.ft PRIVATE ${LIB_NAME})

# Log all logger levels
add_executable(Logger.FATAL.ft test/func/LoggerFatal.ft.cpp)
target_link_libraries(Logger.FATAL.ft PRIVATE ${LIB_NAME})

# Single Thread
add_executable(Logger.st.ft test/func/LoggerST.ft.cpp)
target_link_libraries(Logger.st.ft PRIVATE ${LIB_NAME})

# Multi Threads
add_executable(Logger.mt.ft test/func/LoggerMT.ft.cpp)
target_link_libraries(Logger.mt.ft PRIVATE ${LIB_NAME})

# ========================================
# Benchmark tests
# ========================================
set(BENCH_TEST ${LIB_NAME}_bt)
file(GLOB_RECURSE BENCH_TEST_SRC "test/bench/*.bt.cpp")
add_executable(${BENCH_TEST} ${BENCH_TEST_SRC})

target_link_libraries(${BENCH_TEST} PRIVATE
        benchmark::benchmark_main
        ${LIB_NAME}
)
