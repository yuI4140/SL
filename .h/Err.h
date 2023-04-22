#pragma once
#define NORMAL
#define VARIANTIC
#define DEF
#include "core.h"
#define COLORS
#include "color.h"

#define MAX_ERROR_MSG_LENGTH 0x100

void exception(const char *msg, ...);
void cException(Rgb rgb, const char *msg, ...);

typedef struct {
  int code;
  char message[MAX_ERROR_MSG_LENGTH];
} Error;

typedef struct {
  int code;
  char message[MAX_ERROR_MSG_LENGTH];
  Rgb color;
} defErr;

typedef void (*ErrorHandler)(Error);
defErr getDefErr(Rgb color, Error error);
void default_error_handler(Error error);
void cHandleErr(Rgb color, ErrorHandler handler, Error error);
Error make_error(int code, const char *message, const char *file, int line);

#define CHECK_BODY(condition, body) do { if ((condition)) { body; } } while (0)
#define TRY(func) do { Error __error__; if ((__error__ = func).code != 0) { handle_error(NULL, __error__); } } while (0)
#define TRY_WITH_HANDLER(func, handler) do { Error __error__; if ((__errr__ = func).code != 0) { handle_error(handler, __error__); } } while (0)
void handle_error(ErrorHandler handler, Error error);
#define CCHECK_MSG(color, condition, message) do { if ((condition)) { cHandleErr(color, NULL, MAKE_ERROR(1, message)); } } while (0)
#define CHECK_MSG(condition, message) do { if ((condition)) { handle_error(NULL, MAKE_ERROR(1, message)); } } while (0)
#define CHECK(condition, code, message) do { if ((condition)) { handle_error(NULL, MAKE_ERROR(code, message)); } } while (0)
#define CHECK_FILE(file, mode) do { if ((file) == NULL) { handle_error(NULL, MAKE_ERROR(errno, strerror(errno))); } } while (0)
#define MAKE_ERROR(code, message) make_error(code, message, __FILE__, __LINE__)
#define CHECK_NULL(pointer) do { if ((pointer) == nullptr) { handle_error(nullptr,MAKE_ERROR(1,"Null pointer")); } } while (0)
void EXCEPTION_MSG(cstr message);

