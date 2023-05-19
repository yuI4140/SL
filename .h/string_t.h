#pragma once
#include "../mem.c"
#include "defines.h"
#include <ctype.h>
typedef struct {
  void *ptr;
  size_t sz;
} string;

string newStr(size_t sz);
string newStrView(size_t sz);
void freeStr(string *str);
size_t strLength(const string *str);
void setCharAt(string *str, size_t index, char c);
char getCharAt(const string *str, size_t index);
void copyString(const string *src, string *dest);
b8 compareStr(const string *str1, const string *str2);
b8 hasNullTerm(const string *str);
void appendStr(string *str, char c);
void concatenateStr(const string *str1, const string *str2, string *dest);
size_t findSubStr(const string *str, const string *sub);
void reverseStr(string *str);
string subStr(const string *str, size_t index, size_t length);
void replace(string *str, const string *oldSub, const string *newSub);
const char *to_cstr(const string *src);
