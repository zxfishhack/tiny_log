//
// Created by Fish on 2020-09-08.
//

#include "tiny_log.h"
#include <stdarg.h>

TINY_LOG_LOG_SECTION_RO static const char lvl_name[] = "DVIWEF";

volatile int g_logLevel = TINY_LOG_LOG_LEVEL;

static void tiny_log_num(uint32_t u32, uint8_t zero, uint32_t hex, uint32_t width);

TINY_LOG_LOG_SECTION void tiny_log(int logLevel, const char* fmt, ...) {
  if (logLevel < g_logLevel && logLevel < LOG_NONE) {
    return;
  }
  // leave when enter hook return non-zero value.
  if (TinyLogEnterHook() != 0) {
    return;
  }
  tiny_log_num(GetTick(), '0', 0, 8);
  PutChar(' ');
  PutChar(lvl_name[logLevel]);
  PutChar(':');
  va_list args;
  va_start(args, fmt);
  uint8_t  *p, zero;
  int d;
  uint32_t width, sign, hex, frac_width, scale, n, len;
  int32_t i32;
  uint32_t u32, frac;
  double f;

  while(*fmt) {
    if (*fmt == '%') {
      i32 = 0;
      u32 = 0;

      zero = (uint8_t) ((*++fmt == '0') ? '0' : ' ');
      width = 0;
      sign = 1;
      hex = 0;
      frac_width = 0;

      while (*fmt >= '0' && *fmt <= '9') {
        width = width * 10 + (*fmt++ - '0');
      }
      for (;;) {
        switch (*fmt) {
          case 'u':
            sign = 0;
            fmt++;
            continue;

          case 'X':
            hex = 2;
            sign = 0;
            fmt++;
            continue;

          case 'x':
            hex = 1;
            sign = 0;
            fmt++;
            continue;

          case '.':
            fmt++;
            while (*fmt >= '0' && *fmt <= '9') {
              frac_width = frac_width * 10 + (*fmt++ - '0');
            }
            break;

          default:
            break;
        }
        break;
      }

      switch (*fmt) {
        case 's':
          p = va_arg(args, uint8_t*);
          while(*p) {
            PutChar(*p++);
          }
          fmt++;
          continue;
        case 'd':
          if (sign) {
            i32 = (int32_t) va_arg(args, int);
          } else {
            u32 = (uint32_t) va_arg(args, uint32_t);
          }
          break;
        case 'f':
          f = va_arg(args, double);
#if TINY_LOG_ENABLE_FLOAT
          if (f < 0) {
            PutChar('-');
            f = -f;
          }
          uint64_t u64 = (int64_t) f;
          frac = 0;

          if (frac_width) {
            scale = 1;
            for(n = frac_width; n; n --) {
              scale *= 10;
            }

            frac = (uint64_t)((f - (float) u64) * scale + 0.5);

            if (frac == scale) {
              u64 ++;
              frac = 0;
            }
          }

          tiny_log_num(u64, zero, 0, width);

          if (frac_width) {
            PutChar('.');
            tiny_log_num(frac, '0', 0, frac_width);
          }
#endif
          fmt++;
          continue;
        case  'p':
          u32 = (uintptr_t) va_arg(args, void *);
          hex = 2;
          sign = 0;
          zero = '0';
          width = 2 * sizeof(void *);
          break;

        case '%':
          PutChar('%');
          fmt ++;
          continue;

        default:
          PutChar(*fmt++);
          continue;
      }

      if (sign) {
        if (i32 < 0) {
          PutChar('-');
          u32 = (uint32_t) -i32;
        } else {
          u32 = i32;
        }
      }

      tiny_log_num(u32, zero, hex, frac_width);

      fmt ++;
    } else {
      PutChar(*fmt++);
    }
  }
  if (fmt[-1] != '\n' && fmt[-2] != '\r') {
    PutChar('\r');
    PutChar('\n');
  }
  TinyLogLeaveHook();
}

TINY_LOG_LOG_SECTION_RO static const char hex[2][16] = {
  "0123456789abcdef",
  "0123456789ABCDEF",
};

#define INT32_LEN   (sizeof("-2147483648") - 1)
#define INT64_LEN   (sizeof("-9223372036854775808") - 1)

TINY_LOG_LOG_SECTION void tiny_log_num(uint32_t u32, uint8_t zero, uint32_t hexadecimal, uint32_t width) {
  uint8_t *p, temp[INT32_LEN + 1];
  uint8_t len;
  p = temp + INT32_LEN;
  *p = 0;
  if (hexadecimal == 0) {
    do {
      *--p = (char) (u32 % 10 + '0');
    } while (u32 /= 10);
  } else {
    do {
      *--p = hex[hexadecimal - 1][(uint32_t) (u32 & 0xf)];
    } while (u32 >>= 4);
  }
  len = (temp + INT32_LEN) - p;
  while (len ++ < width && zero != 0) {
    PutChar(zero);
  }
  while(*p) {
    PutChar(*p++);
  }
}

TINY_LOG_LOG_SECTION __attribute__((weak)) uint32_t GetTick() {
  return 0;
}
TINY_LOG_LOG_SECTION __attribute__((weak)) int PutChar(char ch) {
  return ch;
}

TINY_LOG_LOG_SECTION int __attribute((weak)) TinyLogEnterHook() {
  return 0;
}

TINY_LOG_LOG_SECTION void __attribute((weak)) TinyLogLeaveHook() {

}
