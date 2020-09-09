cmake_minimum_required(VERSION 3.5)

# tiny log begin
set(TINY_LOG_LEVEL LOG_INFO)
set(TINY_LOG_TEST 1)
set(TINY_LOG_ENABLE_FLOAT 1)
include(tiny_log.cmake)

# tiny log end

project(tiny_log)

include_directories(${TINY_LOG_INCLUDE})
file(GLOB_RECURSE SOURCES "test/*.*" ${TINY_SOURCES})

add_executable(tiny_log ${SOURCES})