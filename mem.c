#include ".h/mem.h"
i8 heap[H_CAP] = {0};
i8 chunker[CHNK_CAP] = {0};
size_t chunkerSize, heapSize;
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

Box *hAllocBox(size_t sz) {
  void *h = heap + sz;
  heapSize += sz;
  Box newBox = {.ptr = h, .sz = sz};
  Box *sBox = &newBox;
  return sBox;
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
