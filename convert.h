#include <errno.h>
#include <limits.h>
#define DEF
#define NORMAL
#include ".h/core.h"
i32 toInt(str string);
f32 toFloat(str str);
f64 toDouble(str str);
str intToString(i32 num);
str floatToString(f32 num);
str floatToString_s(f32 num,i32 precision);
str doubleToString(f64 num);
#ifdef D_CONVERT
i32 toInt(str string) {
  errno = 0;
  _i64 result = strtol(string, NULL, 10);
  if (errno != 0 || result > INT_MAX || result < INT_MIN) {
    fprintf(stderr, "Error converting string '%s' to integer\n", string);
    exit(EXIT_FAILURE);
  }
  return (i32)result;
}
f32 toFloat(str str) {
  errno = 0;
  str endPtr;
  f32 result = strtof(str, &endptr);
  if (errno != 0 || *endptr != '\0') {
    fprintf(stderr, "Error converting string '%s' to float\n", str);
    exit(EXIT_FAILURE);
  }
  return result;
}

f64 toDouble(str str) {
  errno = 0;
  char *endptr;
  double result = strtod(str, &endptr);
  if (errno != 0 || *endptr != '\0') {
    fprintf(stderr, "Error converting string '%s' to double\n", str);
    exit(EXIT_FAILURE);
  }
  return result;
}

str intToString(int num) {
  char *str = malloc(12 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  sprintf(str, "%d", num);
  return str;
}
//  you should use floatToString_s if this not work
str floatToString(float num) {
  char *str = malloc(32 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  sprintf(str, "%f", num);
  return str;
}
str floatToString_s(float num, int precision) {
  char *str = malloc(64 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  snprintf(str, 64, "%.*g", precision, num);
  return str;
}
str doubleToString(double num) {
  char *str = malloc(32 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  sprintf(str, "%lf", num);
  return str;
}
#endif /* ifdef D_CONVERT */
