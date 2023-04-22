#pragma once
#define NORMAL
#define DEF
#include "core.h"
typedef struct {
    size_t size;
    size_t capacity;
    void** data;
} Array;

Array create_a(size_t capacity);
void pushBack_a(Array* array, void* data);
void* get_a(Array* array, int index);
void set_a(Array* array, int index, void* data);
