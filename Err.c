#pragma once
#include "sl_funcs.c"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ERROR_MSG_LENGTH 0x100
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
typedef void (*ErrorHandler)(Error);

void handle_error(ErrorHandler handler, Error error) {
  if (handler != NULL) {
    handler(error);
  } else {
    default_error_handler(error);
  }
}
void cHandleErr(Rgb color, ErrorHandler handler, Error error) {
  if (handler != NULL) {
    handler(error);
  } else {
    defErr err = getDefErr(color, error);
    cException(err.color, err.message);
    exit(err.code);
  }
}

#define MAKE_ERROR(code, message) make_error(code, message, __FILE__, __LINE__)

Error make_error(int code, const char *message, const char *file, int line) {
  Error error;
  error.code = code;
  snprintf(error.message, MAX_ERROR_MSG_LENGTH, "%s (%s:%d)", message, file,
           line);
  return error;
}

#define CHECK_NULL(pointer)                                                    \
  do {                                                                         \
    if ((pointer) == NULL) {                                                   \
      handle_error(NULL, MAKE_ERROR(1, "Null pointer"));                       \
    }                                                                          \
  } while (0)

#define CHECK_FILE(file, mode)                                                 \
  do {                                                                         \
    if ((file) == NULL) {                                                      \
      handle_error(NULL, MAKE_ERROR(errno, strerror(errno)));                  \
    }                                                                          \
  } while (0)

#define CHECK(condition, code, message)                                        \
  do {                                                                         \
    if ((condition)) {                                                         \
      handle_error(NULL, MAKE_ERROR(code, message));                           \
    }                                                                          \
  } while (0)

#define CHECK_MSG(condition, message)                                          \
  do {                                                                         \
    if ((condition)) {                                                         \
      handle_error(NULL, MAKE_ERROR(1, message));                              \
    }                                                                          \
  } while (0)
#define CCHECK_MSG(color, condition, message)                                  \
  do {                                                                         \
    if ((condition)) {                                                         \
      cHandleErr(color, NULL, MAKE_ERROR(1, message));                         \
    }                                                                          \
  } while (0)

#define CHECK_BODY(condition, body)                                            \
  do {                                                                         \
    if ((condition)) {                                                         \
      body;                                                                    \
    }                                                                          \
  } while (0)
#define TRY(func)                                                              \
  do {                                                                         \
    Error __error__;                                                           \
    if ((__error__ = func).code != 0) {                                        \
      handle_error(NULL, __error__);                                           \
    }                                                                          \
  } while (0)

#define TRY_WITH_HANDLER(func, handler)                                        \
  do {                                                                         \
    Error __error__;                                                           \
    if ((__errr__ = func).code != 0) {                                         \
      handle_error(handler, __error__);                                        \
    }                                                                          \
  } while (0)