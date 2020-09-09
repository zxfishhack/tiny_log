//
// Created by Fish on 2020-09-09.
//
#include "tiny_log.h"
#include <stdio.h>

int main() {
  log_info("test %ss %.2f", "123", 12.3);
  GetTick();
  PutChar(12);
  return 0;
}