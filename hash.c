#define DEF
#define DEF_MATH
#define NORMAL
#include "core.h"
#define HASH_TABLE_SIZE Kilobytes(7)
i32 hash(cstr key) {
  const u8 *str = (const u8 *)key;
  u32 hash = 5381;

  while (*str) {
    hash = (hash << 5) + hash + *str++;
  }

  return hash;
}

// Hash table entry structure
typedef struct {
  const char *key;
  void *value;
} Entry;

Entry hashTable[HASH_TABLE_SIZE];

void insert(cstr key, void *value) {
  u32 index = hash(key) % HASH_TABLE_SIZE;
  hashTable[index].key = key;
  hashTable[index].value = value;
}

void *get(cstr key) {
  u32 index = hash(key) % HASH_TABLE_SIZE;
  if (hashTable[index].key && strcmp(hashTable[index].key, key) == 0) {
    return hashTable[index].value;
  } else {
    return NULL;
  }
}
