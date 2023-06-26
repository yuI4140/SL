#include <stdlib.h>
#include <stdio.h>
struct bl {
  char value;
};
bool newBool(char v); 
bool checkBool(bool *bl); 
int checkNotBool(char v); 
#ifdef BOOL_IMP
typedef struct bl bool;
bool newBool(char v) {
  if (v > 1 || v < 0) {
    printf("ERROR: passed value is not bool.\n");
    exit(1);
  }
  bool ret = {v};
  return ret;
}
bool checkBool(bool *bl) {
  if (bl->value > 1 || bl->value < 0) {
    printf("ERROR: passed value is not bool.\n");
    exit(1);
  }
  bool newBl = {bl->value};
  return newBl;
}
int checkNotBool(char v) {
  if (v > 1 || v < 0) {
    printf("ERROR: passed value is not bool.\n");
    exit(1);
  }
  return v;
}

#endif
