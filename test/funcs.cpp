//
// Created by Fish on 2020-09-09.
//

#include <stdio.h>
#include <stdint.h>
#include <sysinfoapi.h>

extern "C" uint32_t  GetTick() {
  return GetTickCount();
}

extern "C" int PutChar(char ch) {
  return putchar(ch);
}
