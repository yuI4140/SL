#pragma once
// Unsigned int types.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned long _u64;
// Signed int types.
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef signed long _s64;
// Regular int types.
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef long _i64;
// Floating point types
typedef float f32;
typedef double f64;
// Boolean types
typedef u8  b8;
typedef u32 b32;
// stirng types
typedef i8* str;
typedef const str cstr;
typedef u16 wchar_t;
// Void function type
typedef void void_func(void);
typedef void (*void_func_ptr)(void);
#define true 1
#define false 0
#define null 0
#define WCHAR_MAX 0xffff
#define nullptr ((void *)0)
#define UNUSED(var) ((void)(var))
#define DEPRECATED(msg) __attribute__((deprecated(msg)))
#ifdef DEF_ARRAY
#define ArrayCount(a) (sizeof(a) / sizeof(a[0]))
#define Slice_Prototype(type) typedef struct type##_slice { type* elems; u32 len; } type##_slice;
#define slice(type) type##_slice
#define Iterate(array, var) for (int var = 0; var < array.len; var++)
#define IteratePtr(array, var) for (int var = 0; var < array->len; var++)
// SizeofArray macro to get the number of elements in an array
#define SizeofArray(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif /*DEF_ARRAY*/
#ifdef COLORS
#define RED newRgb(0xFF,0,0)
#define GREEN newRgb(0,0xFF,0)
#define BLUE newRgb(0,0,0xFF)
#define WHITE newRgb(0xFF,0xFF,0xFF)
#define BLACK newRgb(0x00, 0x00, 0x00)
#define YELLOW newRgb(0xFF, 0xFF, 0x00)
#define CYAN newRgb(0x00, 0xFF, 0xFF)
#define MAGENTA newRgb(0xFF, 0x00, 0xFF)
#define ORANGE newRgb(0xFF, 0xA5, 0x00)
#define PINK newRgb(0xFF, 0xC0, 0xCB)
#define PURPLE newRgb(0x80, 0x00, 0x80)
#define GOLD newRgb(0xFF, 0xD7, 0x00)
#define GRAY newRgb(0x80, 0x80, 0x80)
#define LIGHT_GRAY newRgb(0xD3, 0xD3, 0xD3)
#define DARK_GRAY newRgb(0xA9, 0xA9, 0xA9)
#define SILVER newRgb(0xC0, 0xC0, 0xC0)
#define BEIGE newRgb(0xF5, 0xF5, 0xDC)
#define BROWN newRgb(0xA5, 0x2A, 0x2A)
#define MAROON newRgb(0x80, 0x00, 0x00)
#define OLIVE newRgb(0x80, 0x80, 0x00)
#define NAVY newRgb(0x00, 0x00, 0x80)
#define FUCHSIA newRgb(0xFF,0x00,0xFF)
#define TEAL newRgb(0x00, 0x80, 0x80)
#define CORAL newRgb(0xFF,0x7F,0x50)
#define TOMATO newRgb(0xFF,0x63,0x47)
#define DARKORANGE newRgb(0xFF,0x8C,0x00)
#define DARK_GREEN newRgb(0x00, 0x64, 0x00)
#define LIGHT_GREEN newRgb(0x90, 0xEE, 0x90)
#define FOREST_GREEN newRgb(0x22, 0x8B, 0x22)
#define SEA_GREEN newRgb(0x2E, 0x8B, 0x57)
#define SKY_BLUE newRgb(0x87, 0xCE, 0xEB)
#define LIGHT_BLUE newRgb(0xAD, 0xD8, 0xE6)
#define STEEL_BLUE newRgb(0x46, 0x82, 0xB4)
#define ROYAL_BLUE newRgb(0x41, 0x69, 0xE1)
#define INDIGO newRgb(0x4B, 0x00, 0x82)
#define TURQUOISE newRgb(0x40, 0xE0, 0xD0)
#define LIGHT_CYAN newRgb(0xE0, 0xFF, 0xFF)
#define DARK_CYAN newRgb(0x00, 0x8B, 0x8B)
#define CORAL newRgb(0xFF, 0x7F, 0x50)
#define SALMON newRgb(0xFA, 0x80, 0x72)
#define FIREBRICK newRgb(0xB2,0x22,0x22)
#define INDIANRED newRgb(0xCD,0x5C,0x5C)
#define LIGHTCORAL newRgb(0xF0,0x80,0x80)
#define SALMON newRgb(0xFA,0x80,0x72)
#define DARKSALMON newRgb(0xE9,0x96,0x7A)
#define LIGHTSALMON newRgb(0xFF,0xA0,0x7A)
#define HOTPINK newRgb(0xFF,0x69,0xB4)
#define PINK newRgb(0xFF,0xC0,0xCB)
#define DEEPPINK newRgb(0xFF,0x14,0x93)
#define MEDIUMVIOLETRED newRgb(0xC7,0x15,0x85)
#define PALEVIOLETRED newRgb(0xDB,0x70,0x93)
#define LIGHTPINK newRgb(0xFF,0xB6,0xC1)
#define ROYALBLUE newRgb(0x41,0x69,0xE1)
#define BLUEVIOLET newRgb(0x8A,0x2B,0xE2)
#define INDIGO newRgb(0x4B,0x00,0x82)
#define DARKSLATEBLUE newRgb(0x48,0x3D,0x8B)
#define MEDIUMSLATEBLUE newRgb(0x7B,0x68,0xEE)
#define SLATEBLUE newRgb(0x6A,0x5A,0xCD)
#define GHOSTWHITE newRgb(0xF8,0xF8,0xFF)
#define CRIMSON newRgb(0xDC, 0x14, 0x3C)
#endif /*COLORS*/
#ifdef DEF_STR
// Stringification macros
#define Stringify(x) #x
#define StringifyMacro(x) Stringify(x)
#endif /*DEF_STR*/

#ifdef DEF_MATH
#define RoundUp(value, alignment) (((value) + (alignment) - 1) & ~((alignment) - 1))
// RoundDown macro to round a value down to the nearest multiple of a specified alignment
#define RoundDown(value, alignment) ((value) & ~((alignment) - 1))
#define u32_max 4294967295
#define PATH_MAX 4096
#define Clamp(a,x,b) (((x)<(a))?(a):((b)<(x))?(b):(x))
#define ClampTop(a,b) Min(a,b)
#define ClampBot(a,b) Max(a,b)
#define ReverseClamp(a,x,b) (((x)<(a))?(b):((b)<(x))?(a):(x))
#define Wrap(a,x,b) ReverseClamp(a,x,b)
#define Gigabytes(count) (u64) (count * 1024 * 1024 * 1024)
#define Megabytes(count) (u64) (count * 1024 * 1024)
#define Kilobytes(count) (u64) (count * 1024)
#define Min(a,b) (((a)<(b))?(a):(b))
#define Max(a,b) (((a)>(b))?(a):(b))
// Alignment macros
#define AlignDown(x, alignment) ((x) & ~((alignment)-1))
#define AlignUp(x, alignment) (((x) + (alignment)-1) & ~((alignment)-1))
#define Swap(a, b) do { typeof(a) temp = (a); (a) = (b); (b) = temp; } while (0)
#endif /*DEF_MATH*/

#ifdef DEF_MEM
#define Err
#include "Err.c"
#define defmemcpy(dest, src, n) \
do { \
    CHECK_MSG(dest == nullptr || src == NULL,"Null pointer detected"); \
    CHECK_MSG(n == 0,"Invalid argument"); \
    memcpy(dest, src, n); \
} while(0)

#define defmemmove(dest, src, n) \
do { \
    CHECK_MSG(dest == nullptr || src == NULL,"Null pointer detected"); \
    CHECK_MSG(n == 0,"Invalid argument"); \
    memmove(dest, src, n); \
} while(0)

#define defmemset(ptr, value, n) \
do { \
    CHECK_MSG(ptr == NULL,"Null pointer detected"); \
    CHECK_MSG(n == 0,"Invalid argument"); \
    memset(ptr, value, n); \
} while(0)
// OffsetOf macro to get the offset of a member in a struct
#define OffsetOf(type, member) ((size_t)(&((type*)0)->member))
// ContainerOf macro to get the pointer to the parent struct from a member
#define ContainerOf(ptr, type, member) ((type*)((char*)(ptr) - OffsetOf(type, member)))
#define MemoryCopy(d,s,z) memmove((d), (s), (z))
#define MemoryCopyStruct(d,s) MemoryCopy((d),(s), Min(sizeof(*(d)) , sizeof(*(s))))
#define MemoryZero(d,z) memset((d), 0, (z))
#define MemoryZeroStruct(d,s) MemoryZero((d),sizeof(s))
#endif /*DEF_MEM*/

#ifdef DEF_BIT
#define BitSet(x, n) ((x) |= (1ULL << (n)))
#define BitClear(x, n) ((x) &= ~(1ULL << (n)))
#define BitToggle(x, n) ((x) ^= (1ULL << (n)))
#define BitCheck(x, n) ((x) & (1ULL << (n)))
// Byte order macros
#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN 4321
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define BYTE_ORDER LITTLE_ENDIAN
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define BYTE_ORDER BIG_ENDIAN
#endif
#endif /* DEF_BIT*/

