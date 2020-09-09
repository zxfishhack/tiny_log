cmake_minimum_required(VERSION 3.0)

if(NOT TINY_LOG_LEVEL)
    set(TINY_LOG_LEVEL LOG_NONE)
endif()

if(NOT TINY_LOG_ENABLE_FLOAT)
    SET(TINY_LOG_ENABLE_FLOAT 0)
endif()

message("log level is ${TINY_LOG_LEVEL}")

if(NOT TINY_LOG_TEST)
    message("CMAKE_CURRENT_LIST_DIR is ${CMAKE_CURRENT_LIST_DIR}")
    CONFIGURE_FILE(${CMAKE_CURRENT_LIST_DIR}/include/tiny_log_config.h.cmake ${CMAKE_BINARY_DIR}/tiny_log/include/config.h)
    CONFIGURE_FILE(${CMAKE_CURRENT_LIST_DIR}/include/tiny_log.h ${CMAKE_BINARY_DIR}/tiny_log/include/tiny_log.h)
    CONFIGURE_FILE(${CMAKE_CURRENT_LIST_DIR}/src/tiny_log.c ${CMAKE_BINARY_DIR}/tiny_log/src/tiny_log.c)

    set(TINY_LOG_INCLUDE ${CMAKE_BINARY_DIR}/tiny_log/include)

    set(TINY_SOURCES ${CMAKE_BINARY_DIR}/tiny_log/src/tiny_log.c)
else()
    CONFIGURE_FILE(include/tiny_log_config.h.cmake include/config.h)

    set(TINY_LOG_INCLUDE "${CMAKE_SOURCE_DIR}/include" "${CMAKE_BINARY_DIR}/include")

    set(TINY_SOURCES src/tiny_log.c)
endif()