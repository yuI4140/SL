#pragma once
#define COLORS
#include "core.h"
#include "color.c"
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
        if (*format == '%' && *(format + 1) >= '1' && *(format + 1) <= '9') {
            int arg_index = *(format + 1) - '1';
            format += 2;
            switch (arg_index) {
                case 0:
                    printf("%d", va_arg(args, int));
                    break;
                case 1:
                    printf("%s", va_arg(args, const char*));
                    break;
                case 2:
                    printf("%.2f", va_arg(args, double));
                    break;
                case 3:
                    printf("%s", va_arg(args, const char*));
                    break;
                case 4:
                    wprintf(L"%ls", va_arg(args, const wchar_t*));
                    break;
                case 5:
                    printf("%.1f", va_arg(args, double));
                    break;
                case 6:
                    printf("%c", va_arg(args, int));
                    break;
                case 7:
                    printf("%ld", va_arg(args, long));
                    break;
                case 8:
                    printf("%lld", va_arg(args, long long));
                    break;
                case 9:
                    printf("%u", va_arg(args, unsigned int));
                    break;
                case 10:
                    printf("%f", va_arg(args, double));
                    break;
                case 11:
                    printf("%c", va_arg(args, int));
                    break;
                case 12:
                    printf("%lu", va_arg(args, unsigned long));
                    break;
                case 13:
                    printf("%llu", va_arg(args, unsigned long long));
                    break;
                case 14:
                    printf("%d", va_arg(args, int));
                    break;
                case 15:
                    printf("%u", va_arg(args, unsigned int));
                    break;
                case 16:
                    printf("%d", va_arg(args, int));
                    break;
                case 17:
                    printf("%u", va_arg(args, unsigned int));
                    break;
                case 18:
                    printf("%s", va_arg(args, const char*));
                    break;
                default:
                    putchar('%');
                    putchar('0' + arg_index + 1);
                    break;
            }
        } else {
            putchar(*format);
            format++;
        }
    }

    va_end(args);
}
