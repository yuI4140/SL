#include ".h/hash.h"
typedef struct {
  cstr key;
  vd *value;
} Entry;
Entry hashTable[HASH_TABLE_SIZE];
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
    return NULL;
  }
}
