#pragma once
#include <cstddef>
#include <cstring>
#include <array>

typedef char i8;
typedef int i32;

// Function declarations
struct Chunk {
  void *ptr;
  size_t sz;
};

Chunk chunkAlloc(size_t sz);
void *hAlloc(size_t sz);
Chunk hAllocChunk(size_t sz);
void passHeap();
void bringDown();
void hFree(void *ptr, size_t sz);
void *hReAlloc(void *ptr, size_t oldSz, size_t newSz);
void *moveToChunk(void *ptr);
