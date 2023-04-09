#pragma once
#define COLORS
#include "core.h"
#include "color.c"
#include "string.c"
void cPrint(Rgb rgb, const char *format, ...) {
  printf("\x1b[38;2;%d;%d;%dm", rgb.r, rgb.g, rgb.b);

  va_list args;
  va_start(args, format);
  int ret = vprintf(format, args);
  va_end(args);

  if (ret < 0) {
    fprintf(stderr, "Error occurred during print.\n");
    return;
  }

  printf("\x1b[0m");
}
void print(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        Contains fcb = countAndFind(format, strlen(format), "{", sizeof("{") - 1);
        cstr newfmt = replace("{}", "", format);
        for (int i = 0; i < fcb.total; ++i) {
            fcb.pos[i] = (const void*)((intptr_t)fcb.pos[i] + 1);
            void* arg = va_arg(args, void*);
            insert_char(newfmt, (int)((intptr_t)fcb.pos[i]), arg);
        }
        format = newfmt;
    }
    printf(format);
    va_end(args);
}