#pragma once
#define DEF
#define DEF_MATH
#define NORMAL

#include "core.h"

#define HASH_TABLE_SIZE Kilobytes(7)

i32 hash(cstr key);
void insert(cstr key, void *value);
void* get(cstr key);
