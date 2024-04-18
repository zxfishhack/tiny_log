//
// Created by Fish on 2020-09-09.
//

#include <stdio.h>
#include <stdint.h>

#ifdef WIN32
#include <sysinfoapi.h>
#else
#include <sys/time.h>
#endif

extern "C" uint32_t  GetTick() {
#ifdef WIN32
  return GetTickCount();
#else
  struct timeval tv;
  if (gettimeofday(&tv, NULL) == 0) {
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
  }
#endif
  return 0;
}

extern "C" int PutChar(char ch) {
  return putchar(ch);
}
