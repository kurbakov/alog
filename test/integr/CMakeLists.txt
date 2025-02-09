cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_CXX_STANDARD 23)

project(ALog VERSION 0.0.1)


include(FetchContent)

set(ALOG_LANE_LEN 1024)
set(ALOG_CHANNEL_LEN 1024)
set(ALOG_CPU_ID -1)
set(ALOG_LEVEL ::alog::Level::INFO)

FetchContent_Declare(
        alog
        GIT_REPOSITORY https://github.com/kurbakov/alog
        GIT_TAG origin/main
)

FetchContent_MakeAvailable(alog)


add_executable(main main.cpp)
target_link_libraries(main PRIVATE alog)
