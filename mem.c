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
#define ALIGN_POINTER(ptr)                                                     \
  ((void *)(((ptrdiff_t)(ptr) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1)))

#define H_CAP 1000000
#define CHNK_CAP 1000000

i8 heap[H_CAP] = {0};
i8 chunker[CHNK_CAP] = {0};
size_t chunkerSize = 0;
size_t heapSize = 0;

typedef struct {
  void *ptr;
  size_t sz;
} Chunk;

Chunk chunkAlloc(size_t sz) {
  void *chunk = chunker + chunkerSize;
  chunkerSize += sz;
  Chunk newChunk = {.ptr = chunk, .sz = sz};
  return newChunk;
}

void *hAlloc(size_t sz) {
  if (heapSize + sz > H_CAP) {
    return NULL; // Memory allocation failed
  }
  void *h = heap + heapSize;
  heapSize += sz;
  return h;
}

void passHeap() {
  memcpy(heap, chunker, chunkerSize);
  heapSize = chunkerSize;
  chunkerSize = 0;
}

void bringDown() { memset(chunker, 0, chunkerSize); }

void hFree(void *ptr, size_t sz) {
  memset(ptr, 0, sz);
  heapSize -= sz;
}

void *hReAlloc(void *ptr, size_t oldSz, size_t newSz) {
  if (newSz <= oldSz) {
    return ptr;
  }

  void *newPtr = hAlloc(newSz);
  if (newPtr != NULL) {
    memcpy(newPtr, ptr, oldSz);
    hFree(ptr, oldSz);
  }
  return newPtr;
}

size_t hSize(void *ptr) {
  if (ptr >= heap && ptr < heap + H_CAP) {
    size_t index = (i8 *)ptr - heap;
    size_t sz = 0;

    for (size_t i = index; i < heapSize; ++i) {
      if (heap[i] == 0) {
        sz = i - index;
        break;
      }
    }

    if (sz == 0) {
      sz = heapSize - index;
    }

    return sz;
  } else if (ptr >= chunker && ptr < chunker + CHNK_CAP) {
    size_t index = (i8 *)ptr - chunker;
    size_t sz = 0;

    for (size_t i = index; i < chunkerSize; ++i) {
      if (chunker[i] == 0) {
        sz = i - index;
        break;
      }
    }

    if (sz == 0) {
      sz = chunkerSize - index;
    }

    return sz;
  } else {
    return 0;
  }
}
void *moveToChunk(void *ptr) {
  ptrdiff_t offset = ALIGN_OFFSET(ptr);
  void *alignedPtr = ALIGN_POINTER(ptr);
  size_t alignedSz = hSize(ptr);

  for (size_t i = 0; i < heapSize; i += alignedSz) {
    if (heap + i == alignedPtr) {
      Chunk newChunk = chunkAlloc(alignedSz);
      memcpy(newChunk.ptr, alignedPtr, alignedSz);
      memset(alignedPtr, 0, alignedSz);
      heapSize -= alignedSz;
      return newChunk.ptr + offset;
    }
  }

  return NULL;
}

void *hCalloc(size_t count, size_t size) {
  size_t totalSize = count * size;
  void *ptr = hAlloc(totalSize);
  if (ptr != NULL) {
    memset(ptr, 0, totalSize);
  }
  return ptr;
}

size_t hAvailable() { return H_CAP - heapSize; }

size_t hChunkAvailable() { return CHNK_CAP - chunkerSize; }

void *hMalloc(size_t sz) {
  void *ptr = hAlloc(sz);
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

void *hRealloc(void *ptr, size_t sz) {
  void *newPtr = hReAlloc(ptr, hSize(ptr), sz);
  if (newPtr == NULL) {
    // Handle memory reallocation error
    // You can add your own error handling logic here
  }
  return newPtr;
}

void h_Free(void *ptr) {
  size_t sz = hSize(ptr);
  hFree(ptr, sz);
}

void *hAlignedAlloc(size_t alignment, size_t size) {
  void *ptr = hAlloc(size + alignment - 1);
  if (ptr == NULL) {
    // Handle memory allocation error
    // You can add your own error handling logic here
    return NULL;
  }
  void *alignedPtr = ALIGN_POINTER(ptr);
  ptrdiff_t offset = ALIGN_OFFSET(alignedPtr);
  if (offset != 0) {
    // Adjust aligned pointer forward
    alignedPtr = (void *)((i8 *)alignedPtr + alignment - offset);
  }
  return alignedPtr;
}

void *hAlignedRealloc(void *ptr, size_t alignment, size_t size) {
  void *newPtr = hReAlloc(ptr, hSize(ptr), size + alignment - 1);
  if (newPtr == NULL) {
    // Handle memory reallocation error
    // You can add your own error handling logic here
    return NULL;
  }
  void *alignedPtr = ALIGN_POINTER(newPtr);
  ptrdiff_t offset = ALIGN_OFFSET(alignedPtr);
  if (offset != 0) {
    // Adjust aligned pointer forward
    alignedPtr = (void *)((i8 *)alignedPtr + alignment - offset);
  }
  return alignedPtr;
}

void hAlignedFree(void *ptr) { hFree(ptr, hSize(ptr)); }

size_t hAlignedSize(void *ptr) {
  size_t size = hSize(ptr);
  ptrdiff_t offset = ALIGN_OFFSET(ptr);
  return size - offset;
}

void *hMemdup(const void *src, size_t sz) {
  void *dst = hAlloc(sz);
  if (dst != NULL) {
    memcpy(dst, src, sz);
  }
  return dst;
}

void hMemswap(void *ptr1, void *ptr2, size_t sz) {
  void *tmp = hAlloc(sz);
  if (tmp != NULL) {
    memcpy(tmp, ptr1, sz);
    memcpy(ptr1, ptr2, sz);
    memcpy(ptr2, tmp, sz);
    hFree(tmp, sz);
  }
}

void *hMemmove(void *dst, const void *src, size_t sz) {
  void *tmp = hMemdup(src, sz);
  if (tmp != NULL) {
    memcpy(dst, tmp, sz);
    hFree(tmp, sz);
  }
  return dst;
}

int hMemcmp(const void *ptr1, const void *ptr2, size_t sz) {
  return memcmp(ptr1, ptr2, sz);
}

void hMemset(void *ptr, int value, size_t sz) { memset(ptr, value, sz); }

void hMemcpy(void *dst, const void *src, size_t sz) { memcpy(dst, src, sz); }

void hMemclr(void *ptr, size_t sz) { memset(ptr, 0, sz); }

void *hMemchr(const void *ptr, int value, size_t sz) {
  return memchr(ptr, value, sz);
}

void *hMemrchr(const void *ptr, int value, size_t sz) {
  const unsigned char *p = (const unsigned char *)ptr;
  for (size_t i = sz; i > 0; --i) {
    if (p[i - 1] == (unsigned char)value) {
      return (void *)(p + i - 1);
    }
  }
  return NULL;
}

int hMemcasecmp(const void *ptr1, const void *ptr2, size_t sz) {
  const unsigned char *p1 = (const unsigned char *)ptr1;
  const unsigned char *p2 = (const unsigned char *)ptr2;
  for (size_t i = 0; i < sz; ++i) {
    int diff = tolower(p1[i]) - tolower(p2[i]);
    if (diff != 0) {
      return diff;
    }
  }
  return 0;
}

void *hMemmem(const void *haystack, size_t haystack_sz, const void *needle,
              size_t needle_sz) {
  const unsigned char *h = (const unsigned char *)haystack;
  const unsigned char *n = (const unsigned char *)needle;
  if (needle_sz == 0) {
    return (void *)haystack; // Match empty needle
  }
  if (needle_sz > haystack_sz) {
    return NULL; // Needle is longer than haystack, no match
  }
  const unsigned char first = *n;
  const unsigned char *end = h + haystack_sz - needle_sz + 1;
  for (; h < end; ++h) {
    if (*h == first && memcmp(h, n, needle_sz) == 0) {
      return (void *)h;
    }
  }
  return NULL; // No match found
}

void hMemswapRange(void *ptr1, void *ptr2, size_t sz) {
  size_t numChunks = sz / sizeof(size_t);
  size_t *p1 = (size_t *)ptr1;
  size_t *p2 = (size_t *)ptr2;
  for (size_t i = 0; i < numChunks; ++i) {
    size_t tmp = p1[i];
    p1[i] = p2[i];
    p2[i] = tmp;
  }
}

void hReverseBytes(void *ptr, size_t sz) {
  unsigned char *p = (unsigned char *)ptr;
  size_t i = 0;
  size_t j = sz - 1;
  while (i < j) {
    unsigned char tmp = p[i];
    p[i] = p[j];
    p[j] = tmp;
    ++i;
    --j;
  }
}