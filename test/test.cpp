//
// Created by Fish on 2020-09-09.
//
#include <cstdio>
#include "tiny_log.h"

int main() {
  log_info("test %ss %.2f", "123", 12.3);
  GetTick();
  PutChar('1');
  printf("\n");
  return 0;
}