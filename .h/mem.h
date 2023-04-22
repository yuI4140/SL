#pragma once
#define DEF_MATH
#define DEF
#define NORMAL

#include "core.h"
#include "hash.h"
#include "random.h"

#define H_CAP Gigabytes(1)
#define CHNK_CAP Kilobytes(7)

typedef struct {
    void* ptr;
    size_t sz;
} Chunk;

typedef struct {
    void* ptr;
    size_t sz;
} Box;

Chunk chunkAlloc(size_t sz);
void* hAlloc(size_t sz);
Box* hAllocBox(size_t sz);
void passHeap();
void bringDown();
void hFree(void* ptr, size_t sz);
void* hReAlloc(void* ptr, size_t oldSz, size_t newSz);
void* moveToChunk(void* ptr);
