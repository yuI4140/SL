#pragma once
#define DEF
#define DEF_MATH
#define NORMAL

#include "core.h"

#define HASH_TABLE_SIZE Kilobytes(7)
i32 hash(cstr key);
void insert(cstr key, void *value);
void *get(cstr key);
i32 hash(cstr key) {
  const u8 *str = (const u8 *)key;
  u32 hash = 5381;

  while (*str) {
    hash = (hash << 5) + hash + *str++;
  }

  return hash;
}
