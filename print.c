#pragma once
#include "Err.c"
#include <stdarg.h>
#include <stdio.h>
#define MAX_FORMAT_SIZE 0x100
#define MAX_STRING_SIZE 0xFF * 0x3

void print(const char *format, ...) {
  char format_buffer[MAX_FORMAT_SIZE];
  char string_buffer[MAX_STRING_SIZE];

  int format_index = 0, i = 0;
  va_list args;
  va_start(args, format);

  while (format[i] != '\0' && format_index < MAX_FORMAT_SIZE - 2) {
    if (format[i] == '{' && format[i + 1] == '}') {
      if (format[i + 2] == 's') {
        char *arg_str = va_arg(args, char*);
        int arg_str_len = strlen(arg_str);
        if (arg_str_len > MAX_STRING_SIZE) {
          arg_str_len = MAX_STRING_SIZE;
        }
        strncpy(string_buffer, arg_str, arg_str_len);
        string_buffer[arg_str_len] = '\0';
        format_buffer[format_index++] = '%';
        format_buffer[format_index++] = 's';
        i += 3;
      } else if (format[i + 2] == 'f') {
        double arg_double = va_arg(args, double);
        snprintf(string_buffer, MAX_STRING_SIZE, "%f", arg_double);
        format_buffer[format_index++] = '%';
        format_buffer[format_index++] = 's';
        i += 3;
      } else if (format[i + 2] == 'd') {
        int arg_int = va_arg(args, int);
        snprintf(string_buffer, MAX_STRING_SIZE, "%d", arg_int);
        format_buffer[format_index++] = '%';
        format_buffer[format_index++] = 's';
        i += 3;
      } else if (format[i + 2] == 'c') {
        int arg_char = va_arg(args, int);
        snprintf(string_buffer, MAX_STRING_SIZE, "%c", arg_char);
        format_buffer[format_index++] = '%';
        format_buffer[format_index++] = 's';
        i += 3;
      } else if (format[i + 2] == 'b') {
        bool arg_bool = va_arg(args, int);
        snprintf(string_buffer, MAX_STRING_SIZE, "%s", arg_bool ? "true" : "false");
        format_buffer[format_index++] = '%';
        format_buffer[format_index++] = 's';
        i += 3;
      } else if (format[i + 2] == 'l' && format[i + 3] == 's') {
        wchar_t *arg_wstr = va_arg(args, wchar_t*);
        int arg_wstr_len = wcslen(arg_wstr);
        if (arg_wstr_len > MAX_STRING_SIZE) {
          arg_wstr_len = MAX_STRING_SIZE;
        }
        wcstombs(string_buffer, arg_wstr, arg_wstr_len);
        string_buffer[arg_wstr_len] = '\0';
        format_buffer[format_index++] = '%';
        format_buffer[format_index++] = 's';
        i += 4;
      } else {
        format_buffer[format_index++] = format[i++];
      }
    } else {
      format_buffer[format_index++] = format[i++];
    }
  }

  format_buffer[format_index] = '\0';

  va_end(args);
  int string_length =
      vsnprintf(string_buffer, MAX_STRING_SIZE, format_buffer, args);
  va_end(args);
  CHECK(string_length < 0, 1, "vsnprintf error");
  CHECK(string_length >= MAX_STRING_SIZE, 1, "Error: string too long\n");
  CHECK_MSG(fwrite(string_buffer, string_length, 1, stdout) != 1,
            "fwrite error");
}
