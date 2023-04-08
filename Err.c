#pragma once
#define Err
#define COLORS
#include "core.h"
void exception(const char *msg, ...) {
  va_list argp;
  va_start(argp, msg);
  vfprintf(stderr, msg, argp);
  va_end(argp);
  exit(1);
}
void cException(Rgb rgb, const char *msg, ...) {
  printf("\x1b[38;2;%d;%d;%dm", rgb.r, rgb.g, rgb.b);
  va_list argp;
  va_start(argp, msg);
  vfprintf(stderr, msg, argp);
  va_end(argp);
  printf("\x1b[0m");
  exit(1);
}
typedef struct {
  int code;
  char message[MAX_ERROR_MSG_LENGTH];
} Error;
typedef struct {
  int code;
  char message[MAX_ERROR_MSG_LENGTH];
  Rgb color;
} defErr;
defErr getDefErr(Rgb color, Error error) {
  char defBuf[MAX_ERROR_MSG_LENGTH];
  sprintf(defBuf, "Error %d: %s\n", error.code, error.message);
  defErr def = {.code = error.code, .color = color};
  strcpy(def.message, defBuf);
  return def;
}
void default_error_handler(Error error) {
  char defBuf[MAX_ERROR_MSG_LENGTH];
  sprintf(defBuf, "Error %d: %s\n", error.code, error.message);
  cException(WHITE, defBuf);
  exit(error.code);
}
void handle_error(ErrorHandler handler, Error error) {
  if (handler != nullptr) {
    handler(error);
  } else {
    default_error_handler(error);
  }
}
void cHandleErr(Rgb color, ErrorHandler handler, Error error) {
  if (handler != nullptr) {
    handler(error);
  } else {
    defErr err = getDefErr(color, error);
    cException(err.color, err.message);
    exit(err.code);
  }
}
Error make_error(int code, const char *message, const char *file, int line) {
  Error error;
  error.code = code;
  snprintf(error.message, MAX_ERROR_MSG_LENGTH, "%s (%s:%d)", message, file,
           line);
  return error;
}