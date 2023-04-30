#define DEF
#define VARIANTIC
#define NORMAL
#include ".h/core.h"
#define COLORS
#include "Color.c"
#include "string.c"
char *RgbToAnsi(Rgb rgb) {
  int R = rgb.r;
  int G = rgb.g;
  int B = rgb.b;

  // Calculate the closest color in the 216-color cube
  int r = (R * 5 / 255);
  int g = (G * 5 / 255);
  int b = (B * 5 / 255);
  int colorIndex = 16 + (r * 36) + (g * 6) + b;

  // Convert the color index to an ANSI escape code
  char *ansiCode = (char *)malloc(20);
  sprintf(ansiCode, "\033[38;5;%dm", colorIndex);

  return ansiCode;
}
void print(const char *format, ...) {
  va_list args;
  va_start(args, format);

  char buffer[256];
  vsprintf(buffer, format, args);

  for (int i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] == '%') {
      switch (buffer[i + 1]) {
      case 'r': {
        Rgb rgb = va_arg(args, Rgb);
        char *ansiCode = RgbToAnsi(rgb);
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
str format(const char *format, ...) {
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
