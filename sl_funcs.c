#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdbool.h>
#include "Color.c"
int toInt(char *str) {
  errno = 0;
  long result = strtol(str, NULL, 10);
  if (errno != 0 || result > INT_MAX || result < INT_MIN) {
    fprintf(stderr, "Error converting string '%s' to integer\n", str);
    exit(EXIT_FAILURE);
  }
  return (int)result;
}

float toFloat(char *str) {
  errno = 0;
  char *endptr;
  float result = strtof(str, &endptr);
  if (errno != 0 || *endptr != '\0') {
    fprintf(stderr, "Error converting string '%s' to float\n", str);
    exit(EXIT_FAILURE);
  }
  return result;
}

double toDouble(char *str) {
  errno = 0;
  char *endptr;
  double result = strtod(str, &endptr);
  if (errno != 0 || *endptr != '\0') {
    fprintf(stderr, "Error converting string '%s' to double\n", str);
    exit(EXIT_FAILURE);
  }
  return result;
}

char *intToString(int num) {
  char *str = malloc(12 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  sprintf(str, "%d", num);
  return str;
}

char *floatToString(float num) {
  char *str = malloc(32 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  sprintf(str, "%f", num);
  return str;
}

char *doubleToString(double num) {
  char *str = malloc(32 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  sprintf(str, "%lf", num);
  return str;
}
char* substr(char* src, int start, int end) {
    int len = strlen(src);
    if (end < 0) {
        end = len + end;
    }
    if (start < 0) {
        start = len + start;
    }

    if (start >= len || start >= end || end > len || end < 0) {
       return NULL;
    }

    int subLen = end - start;
    char* subStr = malloc(subLen + 1);

    if (!subStr) {
        return NULL;
    }

    strncpy(subStr, src + start, subLen);
    subStr[subLen] = '\0';

    return subStr;
}
int contains(char* str1, char* str2) {
    if (strstr(str1, str2) != NULL) {
        return 1;
    }
    return 0;
}

char* replace(char* oldStr, char* newStr, char* src) {
    char* result;char* ins;char* tmp;int lenOld;
    int lenNew;int lenSrc;int count;

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

void exception(const char* msg, ...) {
    va_list argp;
    va_start(argp, msg);
    vfprintf(stderr, msg, argp);
    va_end(argp);
    exit(1);
}
void cPrint(Rgb rgb, const char* format, ...) {
    printf("\x1b[38;2;%d;%d;%dm", rgb.r, rgb.g, rgb.b);

    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);

    if (ret < 0) {
        fprintf(stderr, "Error occurred during print.\n");
        return;
    }

    printf("\x1b[0m");
}

void cException(Rgb rgb, const char* msg, ...) {
    printf("\x1b[38;2;%d;%d;%dm", rgb.r, rgb.g, rgb.b);
    va_list argp;
    va_start(argp, msg);
    vfprintf(stderr, msg, argp);
    va_end(argp);
    printf("\x1b[0m");
    exit(1);
}
void* ToType(void* anyType, const char* dest) {
    if (strcmp(dest, "char*") == 0) {
        return (char*) anyType;
    } else if (strcmp(dest, "int") == 0) {
        return (int*) anyType;
    } else if (strcmp(dest, "float") == 0) {
        return (float*) anyType;
    } else if (strcmp(dest, "double") == 0) {
        return (double*) anyType;
    } else if (strcmp(dest, "uint") == 0) {
        return (unsigned int*) anyType;
    } else if (strstr(dest, "[]") != NULL) {
         int elementSize;
        const char* elementTypeStr = strtok((char*)dest, "[]");
        if (strcmp(elementTypeStr, "char*") == 0) {
            elementSize = sizeof(char*);
        } else if (strcmp(elementTypeStr, "int") == 0) {
            elementSize = sizeof(int);
        } else if (strcmp(elementTypeStr, "float") == 0) {
            elementSize = sizeof(float);
        } else if (strcmp(elementTypeStr, "double") == 0) {
            elementSize = sizeof(double);
        } else if (strcmp(elementTypeStr, "uint") == 0) {
            elementSize = sizeof(unsigned int);
        } else {
            return NULL;
        }

        const char* lengthStr = strtok(NULL, "[]");
        if (lengthStr == NULL) {
            return NULL;
        }
        int length = atoi(lengthStr);

        void* array = malloc(length * elementSize);
        if (array == NULL) {
            return NULL;
        }

        memcpy(array, anyType, length * elementSize);

        return array;
    } else {
        return NULL;
    }
}
