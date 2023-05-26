#define DEF
#define VARIANTIC
#define NORMAL
#include ".h/core.h"
#define COLORS
#include "Color.c"
#include "string.c"
str RgbToAnsi(Rgb rgb) {
  i32 R = rgb.r;
  i32 G = rgb.g;
  i32 B = rgb.b;

  i32 r = (R * 5 / 255);
  i32 g = (G * 5 / 255);
  i32 b = (B * 5 / 255);
  i32 colorIndex = 16 + (r * 36) + (g * 6) + b;

  str ansiCode = (str)malloc(20);
  sprintf(ansiCode, "\033[38;5;%dm", colorIndex);

  return ansiCode;
}
void print(cstr format, ...) {
  va_list args;
  va_start(args, format);

  i8 buffer[256];
  vsprintf(buffer, format, args);

  for (i32 i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] == '%') {
      switch (buffer[i + 1]) {
      case 'r': {
        Rgb rgb = va_arg(args, Rgb);
        str ansiCode = RgbToAnsi(rgb);
        printf("%s", ansiCode);
        i++;
        break;
      }
      default: {
        printf("INVALID FORMAT");
        return;
      }
      }
    } else {
      putchar(buffer[i]);
    }
  }

  va_end(args);
}
// not stable yet
str format(cstr format, ...) {
  va_list args;
  va_start(args, format);

  char buffer[256];
  for (int i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] == '%') {
      switch (buffer[i + 1]) {
      case 'r': {
        Rgb rgb = va_arg(args, Rgb);
        char *ansiCode = RgbToAnsi(rgb);
        return ansiCode;
        i++;
        break;
      }
      default: {
        printf("INVALID FORMAT");
        return "\0";
      }
      }
    } else {
      putchar(buffer[i]);
    }
  }
  str cbuffer = buffer;
  return cbuffer;
  va_end(args);
}
void input(char *buffer, int size) {
  if (size <= 0) {
    printf("Invalid size.\n");
    return; // Invalid size, print error message and return
  }

  if (fgets(buffer, size, stdin) != NULL) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0'; // Remove trailing newline
      len--;
    }

    if (len == size - 1 && buffer[len] != '\0' && buffer[len] != '\n') {
      int c;
      while ((c = getchar()) != '\n' && c != EOF) {
      }
    }

    printf("Input received successfully.\n");
  } else {
    printf("Error in input.\n");
  }
}