#pragma once
#include "Err.c"
#include <stdarg.h>
#include <stdio.h>

#define MAX_FORMAT_SIZE 256
#define MAX_STRING_SIZE 0xFF * 3

void print(const char *format, ...) {
  char format_buffer[MAX_FORMAT_SIZE];
  char string_buffer[MAX_STRING_SIZE];

  int format_index = 0, i = 0;
  while (format[i] != '\0' && format_index < MAX_FORMAT_SIZE - 2) {
    if (format[i] == '{' && format[i + 1] == '}') {
      format_buffer[format_index++] = '%';
      format_buffer[format_index++] = 's';
      i += 2;
    } else {
      format_buffer[format_index++] = format[i++];
    }
  }
  format_buffer[format_index] = '\0';

  va_list args;
  va_start(args, format);
  int string_length =
      vsnprintf(string_buffer, MAX_STRING_SIZE, format_buffer, args);
  va_end(args);
  CHECK(string_length < 0, 1, "vsnprintf error");
  CHECK(string_length >= MAX_STRING_SIZE, 1, "Error: string too long\n");
  CHECK_MSG(fwrite(string_buffer, string_length, 1, stdout) != 1,
            "fwrite error");
}
