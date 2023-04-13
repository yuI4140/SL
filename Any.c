#pragma once
#define NORMAL
#include "core.h"
typedef struct{
    size_t size;
    void* data;
} Any;

Any createAny(void* data,size_t size) {
Any any;
    any.size = size;
    any.data =data;
    return any;
}

void freeAny(Any* any) {
    free(any->data);
}

void* getAny(Any any) {
    return any.data;
}

void setAny(Any* any, void* data) {
    memcpy(any->data, data, any->size);
}
	
