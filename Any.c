#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct{
    size_t size;
    void* data;
} Any;

Any createAny(size_t size) {
    Any any;
    any.size = size;
    any.data = malloc(size);
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
	
