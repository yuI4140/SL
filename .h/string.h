#pragma once
#define DEF
#define NORMAL
#include "core.h"
typedef struct {
  const void **pos;
  int total;
} Contains;

void insert_char(const char *str, int index, void *inst);
Contains countAndFind(const void *arr, int size, const void *element, size_t elemSize);
str substr(str src, i32 start, i32 end);
b8 contains(str str1, str str2);
char *replace(char *oldStr, char *newStr, char *src);
cstr add_all(str *argv, i32 start_index, b32 add_space);
b8 isPtrInArray(void *ptr, void *arr, size_t arrSize);
