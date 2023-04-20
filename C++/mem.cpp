#pragma once
#define DEF_MATH
#define DEF
#define NORMAL
#include "core.hpp"
#include "hash.cpp"

static std::array<i8, Gigabytes(1)> heap;
static std::array<i8, Gigabytes(1)> chunker;
size_t chunkerSize, heapSize;
typedef struct {
  void *ptr;
  size_t sz;
} Chunk;
Chunk chunkAlloc(size_t sz) {
  void *chunk = chunker + sz;
  chunkerSize += sz;
  Chunk newChunk = {.ptr = chunk, .sz = sz};
  return newChunk;
}
void *hAlloc(size_t sz) {
  void *h = heap + sz;
  heapSize += sz;
  return h;
}

Chunk hAllocChunk(size_t sz) {
  void *h = heap + sz;
  heapSize += sz;
  Chunk newBox = {h,sz};
  return newBox;
}
void passHeap() {
  for (i32 i = 0; i < chunkerSize; ++i) {
    heap[i] = chunker[i];
  }
  heapSize = chunkerSize;
  chunkerSize = null;
}

void bringDown() {
  for (i32 i = 0; i < chunkerSize; ++i) {
    chunker[i] = null;
  }
}
void hFree(void *ptr, size_t sz) {
  memset(ptr, 0, sz);
  heapSize -= sz;
}
void *hReAlloc(void *ptr, size_t oldSz, size_t newSz) {
  if (newSz <= oldSz) {
    return ptr;
  }

  void *newPtr = hAlloc(newSz);
  memcpy(newPtr, ptr, oldSz);
  hFree(ptr, oldSz);

  return newPtr;
}
void *moveToChunk(void *ptr) {
  for (size_t i = 0; i < heapSize; ++i) {
    if (heap + i == ptr) {
      size_t sz = 0;
      // Find the size of the chunk to move
      for (size_t j = i; j < heapSize; ++j) {
        if (heap[j] == 0) {
          sz = j - i;
          break;
        }
      }

      if (sz == 0) {
        // The chunk extends to the end of the heap
        sz = heapSize - i;
      }

      // Move the chunk to the chunker
      Chunk newChunk = chunkAlloc(sz);
      memcpy(newChunk.ptr, ptr, sz);

      // Clear the original chunk in the heap
      memset(ptr, 0, sz);

      // Update heapSize
      heapSize -= sz;

      return newChunk.ptr;
    }
  }

  return nullptr;
}