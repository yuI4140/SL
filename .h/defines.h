#pragma once
#include<stdint.h>
// Unsigned int types.
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef unsigned long _u64;
// Signed int types.
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef signed long _s64;
// Regular int types.
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef long _i64;
// Floating point types
typedef float f32;
typedef double f64;
// Boolean types
typedef u8 b8;
typedef u32 b32;
// stirng types
// char*
typedef char *str;
// const char*
typedef const str cstr;
// void
typedef void vd;
// void Func
typedef void vFn(void);
// void Func pointer
typedef void (*vFnp)(void);
#define true 1
#define false 0
#define null 0
#define nullptr ((void *)0)
#define UNUSED(var) ((void)(var))
#define DEPRECATED(msg) __attribute__((deprecated(msg)))
#ifdef DEF_ARRAY
#define Slice_Prototype(type)                                                  \
  typedef struct type##_slice {                                                \
    type *elems;                                                               \
    u32 len;                                                                   \
  } type##_slice;
#define slice(type) type##_slice
#define Iterate(array, var) for (int var = 0; var < array.len; var++)
#define IteratePtr(array, var) for (int var = 0; var < array->len; var++)
// SizeofArray macro to get the number of elements in an array
#define SizeofArray(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif /*DEF_ARRAY*/
#ifdef DEF_STR
// Stringification macros
#define Stringify(x) #x
#define StringifyMacro(x) Stringify(x)
#endif /*DEF_STR*/
#ifdef DEF_BOOL
#define BOOL_IMP
#include "./bool.h"
#endif /* DEF_BOOL */
#ifdef DEF_DIR
#include <dirent.h>
#include <stdio.h>

// DIr pointer
typedef DIR *Dirp;
// file pointer
typedef FILE *Filep;
// dir entity pointer
typedef struct dirent *Direp;
#endif
#ifdef DEF_MATH
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define RoundUp(value, alignment) (((value) + (alignment)-1) & ~((alignment)-1))
// RoundDown macro to round a value down to the nearest multiple of a specified
// alignment
#define RoundDown(value, alignment) ((value) & ~((alignment)-1))
#define u32_max 4294967295
#define PATH_MAX 4096
#define Clamp(a, x, b) (((x) < (a)) ? (a) : ((b) < (x)) ? (b) : (x))
#define ClampTop(a, b) Min(a, b)
#define ClampBot(a, b) Max(a, b)
#define ReverseClamp(a, x, b) (((x) < (a)) ? (b) : ((b) < (x)) ? (a) : (x))
#define Wrap(a, x, b) ReverseClamp(a, x, b)
#define Gigabytes(count) (u64)(count * 1024 * 1024 * 1024)
#define Megabytes(count) (u64)(count * 1024 * 1024)
#define Kilobytes(count) (u64)(count * 1024)
#define Min(a, b) (((a) < (b)) ? (a) : (b))
#define Max(a, b) (((a) > (b)) ? (a) : (b))
// Alignment macros
#define AlignDown(x, alignment) ((x) & ~((alignment)-1))
#define AlignUp(x, alignment) (((x) + (alignment)-1) & ~((alignment)-1))
// only it support numerical types
#define Swap(a, b)                                                             \
  do {                                                                         \
    a ^= b;                                                                    \
    b ^= a;                                                                    \
    a ^= b;                                                                    \
  } while (0)
// OffsetOf macro to get the offset of a member in a struct
#define OffsetOf(type, member) ((size_t)(&((type *)0)->member))
// ContainerOf macro to get the pointer to the parent struct from a member
#define ContainerOf(ptr, type, member)                                         \
  ((type *)((char *)(ptr)-OffsetOf(type, member)))
#define MemoryCopy(d, s, z) memmove((d), (s), (z))
#define MemoryCopyStruct(d, s)                                                 \
  MemoryCopy((d), (s), Min(sizeof(*(d)), sizeof(*(s))))
#define MemoryZero(d, z) memset((d), 0, (z))
#define MemoryZeroStruct(d, s) MemoryZero((d), sizeof(s))
#endif /*DEF_MATH*/

#ifdef DEF_MEM
#define Sawp_s(a, b, size)                                                     \
  do {                                                                         \
    if ((a) != NULL && (b) != NULL && (a) != (b)) {                            \
      if ((size) > 0) {                                                        \
        union {                                                                \
          char c[size];                                                        \
          short s[size / sizeof(short)];                                       \
          int i[size / sizeof(int)];                                           \
          long l[size / sizeof(long)];                                         \
          float f[size / sizeof(float)];                                       \
          double d[size / sizeof(double)];                                     \
          char *cp[size / sizeof(char *)];                                     \
          const char *ccp[size / sizeof(const char *)];                        \
          wchar_t wc[size / sizeof(wchar_t)];                                  \
          unsigned long long ull[size / sizeof(unsigned long long)];           \
          /* Add additional data types as needed */                            \
        } u;                                                                   \
        memcpy(&u, (a), (size));                                               \
        memcpy((a), (b), (size));                                              \
        memcpy((b), &u, (size));                                               \
      }                                                                        \
    }                                                                          \
  } while (0)
#include "Err.c"
#define defmemcpy(dest, src, n)                                                \
  do {                                                                         \
    CHECK_MSG(dest == nullptr || src == NULL, "Null pointer detected");        \
    CHECK_MSG(n == 0, "Invalid argument");                                     \
    memcpy(dest, src, n);                                                      \
  } while (0)

#define defmemmove(dest, src, n)                                               \
  do {                                                                         \
    CHECK_MSG(dest == nullptr || src == NULL, "Null pointer detected");        \
    CHECK_MSG(n == 0, "Invalid argument");                                     \
    memmove(dest, src, n);                                                     \
  } while (0)

#define defmemset(ptr, value, n)                                               \
  do {                                                                         \
    CHECK_MSG(ptr == NULL, "Null pointer detected");                           \
    CHECK_MSG(n == 0, "Invalid argument");                                     \
    memset(ptr, value, n);                                                     \
  } while (0)
#endif /*DEF_MEM*/

#ifdef DEF_BIT
#define XOR(a, b) ((a) ^ (b))
#define AND(a, b) ((a) & (b))
#define OR(a, b) ((a) | (b))
#define NOT(x) (~(x))
#define BitSet(x, n) ((x) |= (1ULL << (n)))
#define BitClear(x, n) ((x) &= ~(1ULL << (n)))
#define BitToggle(x, n) ((x) ^= (1ULL << (n)))
#define BitCheck(x, n) ((x) & (1ULL << (n)))
// Byte order macros
#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN 4321
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) &&             \
    (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define BYTE_ORDER LITTLE_ENDIAN
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) &&              \
    (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define BYTE_ORDER BIG_ENDIAN
#endif
#endif /* DEF_BIT*/
