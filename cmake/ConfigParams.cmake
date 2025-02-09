if(NOT DEFINED ALOG_LANE_LEN)
    set(ALOG_LANE_LEN 1024)
endif ()

if(NOT DEFINED ALOG_CHANNEL_LEN)
    set(ALOG_CHANNEL_LEN 1024)
endif ()

if(NOT DEFINED ALOG_CPU_ID)
    set(ALOG_CPU_ID -1)
endif ()

# what levels are available see: inc/alog/Defs.hpp
if(NOT DEFINED ALOG_LEVEL)
    set(ALOG_LEVEL ::alog::Level::INFO)
endif()

configure_file(${CMAKE_CURRENT_LIST_DIR}/../inc/config/ALogConfig.hpp.in ${CMAKE_CURRENT_LIST_DIR}/../inc/gen/config/ALogConfig.hpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../inc/gen/config/)
