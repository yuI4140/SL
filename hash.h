#define DEF
#define DEF_MATH
#define NORMAL
#include ".h/core.h"
#define HASH_TABLE_SIZE Kilobytes(7)
i32 hash(cstr key);
void insert(cstr key, void *value);
void *get(cstr key);
i32 hash(cstr key); 
typedef struct {
  str key;
  vd *value;
} Entry;
#ifdef D_HASH
Entry hashTable[HASH_TABLE_SIZE];
i32 hash(cstr key) {
  const u8 *str = (const u8 *)key;
  u32 hash = 5381;

  while (*str) {
    hash = (hash << 5) + hash + *str++;
  }

  return hash;
}
void insert(cstr key, void *value) {
  u32 index = hash(key) % HASH_TABLE_SIZE;
  hashTable[index].key = key;
  hashTable[index].value = value;
}
vd *get(cstr key) {
  u32 index = hash(key) % HASH_TABLE_SIZE;
  if (hashTable[index].key && strcmp(hashTable[index].key, key) == 0) {
    return hashTable[index].value;
  } else {
    return nullptr;
  }
}
#endif /* ifdef D_HASH */
