//
// Created by Fish on 2020-09-08.
//

#include "tiny_log.h"

TINY_LOG_LOG_SECTION void tiny_log(int logLevel, const char* fmt, ...) {
  if (logLevel < TINY_LOG_LOG_LEVEL) {
    return;
  }

}