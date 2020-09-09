#ifndef TINY_LOG_LIBRARY_H
#define TINY_LOG_LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_DEBUG   0
#define LOG_VERBOSE 1
#define LOG_INFO    2
#define LOG_WARNING 3
#define LOG_ERROR   4
#define LOG_FATAL   5
#define LOG_NONE    6
#include "config.h"
#include <stdint.h>

uint32_t __attribute((weak)) GetTick();
int __attribute((weak)) PutChar(char ch);

void tiny_log(int logLevel, const char* fmt, ...);

#if LOG_LEVEL <= LOG_DEBUG
#define log_debug(...) tiny_log(LOG_DEBUG, __VA_ARGS__)
#else
#define log_debug(...)
#endif // LOG_DEBUG

#if LOG_LEVEL <= LOG_VERBOSE
#define log_verbose(...) tiny_log(LOG_VERBOSE, __VA_ARGS__)
#else
#define log_verbose(...)
#endif // LOG_VERBOSE

#if LOG_LEVEL <= LOG_INFO
#define log_info(...) tiny_log(LOG_INFO, __VA_ARGS__)
#else
#define log_info(...)
#endif // LOG_INFO

#if LOG_LEVEL <= LOG_WARNING
#define log_warning(...) tiny_log(LOG_WARNING, __VA_ARGS__)
#else
#define log_warning(...)
#endif // LOG_WARNING

#if LOG_LEVEL <= LOG_ERROR
#define log_error(...) tiny_log(LOG_ERROR, __VA_ARGS__)
#else
#define log_error(...)
#endif // LOG_ERROR

#if LOG_LEVEL <= LOG_FATAL
#define log_fatal(...) tiny_log(LOG_FATAL, __VA_ARGS__)
#else
#define log_fatal(...)
#endif // LOG_FATAL

#ifdef __cplusplus
};
#endif

extern volatile int g_logLevel;

#endif //TINY_LOG_LIBRARY_H
