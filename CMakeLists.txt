cmake_minimum_required(VERSION 3.20)

# tiny log begin

if (NOT TINY_LOG_LEVEL)
  set(TINY_LOG_LEVEL LOG_INFO)
endif ()

option(TINY_LOG_ENABLE_FLOAT "enable float output" OFF)
option(TINY_LOG_TEST "enable tiny log test" OFF)
if (TINY_LOG_ENABLE_FLOAT)
  message(STATUS "enable float output")
  set(TINY_LOG_ENABLE_FLOAT 1)
else ()
  message(STATUS "disable float output")
  set(TINY_LOG_ENABLE_FLOAT 0)
endif ()


# tiny log end

message(STATUS "log level is ${TINY_LOG_LEVEL}")
if(TINY_LOG_SECTION)
  message(STATUS "custom section: ${TINY_LOG_SECTION}")
endif ()
CONFIGURE_FILE(include/tiny_log_config.h.cmake include/tinylog_config.h)
set(TINY_SOURCES src/tiny_log.c)
set(TINY_LOG_INCLUDE include)

project(tiny_log)

include_directories(${TINY_LOG_INCLUDE} ${CMAKE_CURRENT_BINARY_DIR}/include)

add_library(tiny_log ${TINY_SOURCES})
if (TINY_LOG_TEST)
add_executable(tiny_log_test test/funcs.cpp test/test.cpp)
add_dependencies(tiny_log_test tiny_log)
target_link_libraries(tiny_log_test tiny_log)
endif ()