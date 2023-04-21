#include "mem.c"
#include <ctype.h>
typedef struct {
  void *ptr;
  size_t sz;
} string;

string newStr(size_t sz) {
  string newstring;
  newstring.ptr = hAlloc(sz);
  newstring.sz = sz;
  return newstring;
}
string newStrView(size_t sz) {
  Chunk newChunk = chunkAlloc(sz);
  string newStr = {.ptr = newChunk.ptr, .sz = newChunk.sz};
  return newStr;
}
void freeStr(string *str) {
  hFree(str->ptr, str->sz);
  str->ptr = null;
  str->sz = 0;
}

size_t strLength(const string *str) { return str->sz; }

void setCharAt(string *str, size_t index, char c) {
  if (index < str->sz) {
    ((char *)str->ptr)[index] = c;
  }
}

char getCharAt(const string *str, size_t index) {
  if (index < str->sz) {
    return ((char *)str->ptr)[index];
  }
  return '\0';
}

void copyString(const string *src, string *dest) {
  if (src->sz <= dest->sz) {
    memcpy(dest->ptr, src->ptr, src->sz);
  }
}

// Function to compare two strings
b8 compareStr(const string *str1, const string *str2) {
  size_t minSz = str1->sz < str2->sz ? str1->sz : str2->sz;
  int result = memcmp(str1->ptr, str2->ptr, minSz);
  if (result == 0) {
    if (str1->sz < str2->sz) {
      result = false;
    } else if (str1->sz > str2->sz) {
      result = true;
    }
  }
  return result;
}
b8 hasNullTerm(const string *str) {
  for (size_t i = 0; i < str->sz; ++i) {
    if (((char *)str->ptr)[i] == '\0') {
      return true;
    }
  }
  return false;
}
void appendStr(string *str, char c) {
  if (str->sz > 0) {
    str->ptr = hReAlloc(str->ptr, str->sz, str->sz + 1);
  } else {
    str->ptr = hAlloc(1);
  }
  ((char *)str->ptr)[str->sz++] = c;
}

// Function to concatenate two strings
void concatenateStr(const string *str1, const string *str2, string *dest) {
  size_t totalSz = str1->sz + str2->sz;
  dest->ptr = hReAlloc(dest->ptr, str1->sz, totalSz);
  memcpy((char *)dest->ptr + str1->sz, str2->ptr, str2->sz);
  dest->sz = totalSz;
}

// Function to find the index of a substring in a string
b8 findSubStr(const string *str, const string *sub) {
  if (sub->sz == 0) {
    return false;
  }
  for (size_t i = 0; i <= str->sz - sub->sz; ++i) {
    if (memcmp((char *)str->ptr + i, sub->ptr, sub->sz) == 0) {
      return i;
    }
  }
  return false;
}

void reverseStr(string *str) {
  size_t left = 0;
  size_t right = str->sz - 1;
  while (left < right) {
    char temp = ((char *)str->ptr)[left];
    ((char *)str->ptr)[left] = ((char *)str->ptr)[right];
    ((char *)str->ptr)[right] = temp;
    ++left;
    --right;
  }
}
string subStr(const string *str, size_t index, size_t length) {
  if (index >= str->sz) {
    string lStr = newStr(0);
    return lStr;
  }

  if (index + length > str->sz) {
    // If length exceeds the remaining length of the string, adjust length
    length = str->sz - index;
  }

  string substr;
  substr.ptr = (char *)str->ptr + index;
  substr.sz = length;
  return substr;
}
void replace(string *str, const string *oldSub, const string *newSub) {
  size_t oldSubLen = oldSub->sz;
  size_t newSubLen = newSub->sz;

  size_t index = 0;
  while ((index = findSubStr(str, oldSub)) != false) {
    // Find the next occurrence of oldSub
    // Replace it with newSub
    memcpy((char *)str->ptr + index, newSub->ptr, newSubLen);
    if (oldSubLen != newSubLen) {
      // If the lengths of oldSub and newSub are different, adjust the size of
      // the string
      size_t newSize = str->sz + newSubLen - oldSubLen;
      str->ptr = hReAlloc(str->ptr, str->sz, newSize);
      str->sz = newSize;
    }
  }
}
const char *to_cstr(const string *src) {
  const char *cstr = (const char *)src->ptr;
  return cstr;
}