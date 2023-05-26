#pragma once
#include ".h/defines.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIGNMENT 8
#define ALIGN_SIZE(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define ALIGN_OFFSET(ptr) (((ptrdiff_t)(ptr)) & (ALIGNMENT - 1))
#define ALIGN_POINTER(ptr) ((void *)(((ptrdiff_t)(ptr) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1)))

typedef struct {
  i8 *heap;
  i8 *chunker;
  size_t chunkerSize;
  size_t heapSize;
} Mem;

Mem *createMem(size_t heapCapacity, size_t chunkerCapacity) {
  Mem *mem = malloc(sizeof(Mem));
  if (mem == NULL) {
    return NULL;
  }
  
  mem->heap = malloc(heapCapacity * sizeof(i8));
  if (mem->heap == NULL) {
    free(mem);
    return NULL;
  }
  
  mem->chunker = malloc(chunkerCapacity * sizeof(i8));
  if (mem->chunker == NULL) {
    free(mem->heap);
    free(mem);
    return NULL;
  }
  
  mem->chunkerSize = 0;
  mem->heapSize = 0;
  
  return mem;
}

void destroyMem(Mem *mem) {
  free(mem->chunker);
  free(mem->heap);
  free(mem);
}

Chunk chunkAlloc(Mem *mem, size_t size) {
  void *chunk = mem->chunker + mem->chunkerSize;
  mem->chunkerSize += size;
  Chunk newChunk = {.ptr = chunk, .sz = size};
  return newChunk;
}

void *hAlloc(Mem *mem, size_t size) {
  if (mem->heapSize + size > H_CAP) {
    return NULL; // Memory allocation failed
  }
  
  void *h = mem->heap + mem->heapSize;
  mem->heapSize += size;
  return h;
}

void passHeap(Mem *mem) {
  memcpy(mem->heap, mem->chunker, mem->chunkerSize);
  mem->heapSize = mem->chunkerSize;
  mem->chunkerSize = 0;
}

void bringDown(Mem *mem) {
  memset(mem->chunker, 0, mem->chunkerSize);
}

void hFree(Mem *mem, void *ptr, size_t size) {
  memset(ptr, 0, size);
  mem->heapSize -= size;
}

void *hReAlloc(Mem *mem, void *ptr, size_t oldSize, size_t newSize) {
  if (newSize <= oldSize) {
    return ptr;
  }

  void *newPtr = hAlloc(mem, newSize);
  if (newPtr != NULL) {
    memcpy(newPtr, ptr, oldSize);
    hFree(mem, ptr, oldSize);
  }
  return newPtr;
}

size_t hSize(Mem *mem, void *ptr) {
  if (ptr >= mem->heap && ptr < mem->heap + H_CAP) {
    size_t index = (i8 *)ptr - mem->heap;
    size_t size = 0;

    for (size_t i = index; i < mem->heapSize; ++i) {
      if (mem->heap[i] == 0) {
        size = i - index;
        break;
      }
    }

    if (size == 0) {
      size = mem->heapSize - index;
    }

    return size;
  } else if (ptr >= mem->chunker && ptr < mem->chunker + CHNK_CAP) {
    size_t index = (i8 *)ptr - mem->chunker;
    size_t size = 0;

    for (size_t i = index; i < mem->chunkerSize; ++i) {
      if (mem->chunker[i] == 0) {
        size = i - index;
        break;
      }
    }

    if (size == 0) {
      size = mem->chunkerSize - index;
    }

    return size;
  } else {
    return 0;
  }
}

void *moveToChunk(Mem *mem, void *ptr) {
  ptrdiff_t offset = ALIGN_OFFSET(ptr);
  void *alignedPtr = ALIGN_POINTER(ptr);
  size_t alignedSize = hSize(mem, ptr);

  for (size_t i = 0; i < mem->heapSize; i += alignedSize) {
    if (mem->heap + i == alignedPtr) {
      Chunk newChunk = chunkAlloc(mem, alignedSize);
      memcpy(newChunk.ptr, alignedPtr, alignedSize);
      memset(alignedPtr, 0, alignedSize);
      mem->heapSize -= alignedSize;
      return newChunk.ptr + offset;
    }
  }

  return NULL;
}

void *hCalloc(Mem *mem, size_t count, size_t size) {
  size_t totalSize = count * size;
  void *ptr = hAlloc(mem, totalSize);
  if (ptr != NULL) {
    memset(ptr, 0, totalSize);
  }
  return ptr;
}

size_t hAvailable(Mem *mem) {
  return H_CAP - mem->heapSize;
}

size_t hChunkAvailable(Mem *mem) {
  return CHNK_CAP - mem->chunkerSize;
}

void *hMalloc(Mem *mem, size_t size) {
  void *ptr = hAlloc(mem, size);
  if (ptr == NULL) {
    // Handle memory allocation error
    // You can add your own error handling logic here
  }
  return ptr;
}

void hAbort() {
  // Handle an unrecoverable error situation
  // You can add your own error handling logic here
  exit(EXIT_FAILURE);
}

void *hRealloc(Mem *mem, void *ptr, size_t size) {
  void *newPtr = hReAlloc(mem, ptr, hSize(mem, ptr), size);
  if (newPtr == NULL) {
    // Handle memory reallocation error
    // You can add your own error handling logic here
  }
  return newPtr;
}

void hFree(Mem *mem, void *ptr) {
  size_t size = hSize(mem, ptr);
  hFree(mem, ptr, size);
}

void *hAlignedAlloc(Mem *mem, size_t size) {
  size_t alignedSize = ALIGN_SIZE(size);
  void *ptr = hAlloc(mem, alignedSize);
  if (ptr != NULL) {
    memset(ptr, 0, alignedSize);
  }
  return ptr;
}
