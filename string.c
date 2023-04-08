#pragma once
#include "core.h"
char *substr(char *src, int start, int end) {
  int len = strlen(src);
  if (end < 0) {
    end = len + end;
  }
  if (start < 0) {
    start = len + start;
  }

  if (start >= len || start >= end || end > len || end < 0) {
    return nullptr;
  }

  int subLen = end - start;
  char *subStr = malloc(subLen + 1);
  if (!subStr) {
    return NULL;
  }

  strncpy(subStr, src + start, subLen);
  subStr[subLen] = '\0';

  return subStr;
}
int contains(char *str1, char *str2) {
  if (strstr(str1, str2) != NULL) {
    return 1;
  }
  return 0;
}

char *replace(char *oldStr, char *newStr, char *src) {
  char *result;
  char *ins;
  char *tmp;
  int lenOld;
  int lenNew;
  int lenSrc;
  int count;

  if (!oldStr || !newStr || !src) {
    return NULL;
  }

  lenOld = strlen(oldStr);
  if (lenOld == 0) {
    return NULL;
  }

  lenNew = strlen(newStr);
  lenSrc = strlen(src);

  ins = src;
  for (count = 0; (tmp = strstr(ins, oldStr)); ++count) {
    ins = tmp + lenOld;
  }

  tmp = result = malloc(lenSrc + (lenNew - lenOld) * count + 1);
  if (!result) {
    return NULL;
  }

  while (count--) {
    ins = strstr(src, oldStr);
    lenSrc = ins - src;
    tmp = strncpy(tmp, src, lenSrc) + lenSrc;
    tmp = strcpy(tmp, newStr) + lenNew;
    src += lenSrc + lenOld;
  }
  strcpy(tmp, src);

  return result;
}