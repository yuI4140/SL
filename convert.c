#include ".h/convert.h"
#include <errno.h>
#include <limits.h>

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

char *intToString(int num) {
  char *str = malloc(12 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  sprintf(str, "%d", num);
  return str;
}
//  you should use floatToString_s if this not work
char *floatToString(float num) {
  char *str = malloc(32 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  sprintf(str, "%f", num);
  return str;
}
char *floatToString_s(float num, int precision) {
  char *str = malloc(64 * sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    exit(EXIT_FAILURE);
  }
  snprintf(str, 64, "%.*g", precision, num);
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