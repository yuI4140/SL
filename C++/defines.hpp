#pragma once
// Unsigned int types.
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using _u64 = unsigned long;

// Signed int types.
using s8 = signed char;
using s16 = signed short;
using s32 = signed int;
using s64 = signed long long;
using _s64 = signed long;

// Regular int types.
using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;
using _i64 = long;

// Floating point types.
using f32 = float;
using f64 = double;

// Alternative Boolean types.
using b8 = u8;
using b32 = u32;
#define ctrue 1
#define cfalse 0

// C-style strings types.
using str=i8*;
using cstr=const str;

// Void function type.
typedef void void_func(void);
typedef void (*void_func_ptr)(void);

// C-style nulls
#define cNullptr ((void*)0)
#define cNull 0

#define WCHAR_MAX 0xffff
#define UNUSED(var) ((void)(var))
#define DEPRECATED(msg) [[deprecated(msg)]]
//-------------------------------------------------
// macros from defines.h
//-------------------------------------------------

#ifdef DEF_ARRAY
#define ArrayCount(a) (sizeof(a) / sizeof(a[0]))
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
