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

    if (!contains((char*)format, "{}")) {
        printf(format);
        va_end(args);
        return;
    }
      int total_args = 0;
    const char* format_ptr = format;
    while (*format_ptr != '\0') {
        Contains fcb = countAndFind(format_ptr, strlen(format_ptr), "{", sizeof("{") - 1);
        cstr newfmt = replace("{}", "", format_ptr);
        int newfmt_len = strlen(newfmt);
        for (int i = 0; i < fcb.total; ++i) {
            if ((intptr_t)fcb.pos[i] < newfmt_len) {
                fcb.pos[i] = (const void*)((intptr_t)fcb.pos[i] + 1);
                if (total_args > 0) {
                    void* arg = va_arg(args, void*);
                    insert_char(newfmt, (int)((intptr_t)fcb.pos[i]), arg);
                }
            }else {
                EXCEPTION_MSG("Index out of range\n");
            }
        }
        format_ptr = newfmt;
        total_args += fcb.total;
    }
    printf(format);
    va_end(args);
}

