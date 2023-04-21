#define BIT
#define DEF
#include "core.h"
void FLIP(void* ptr, int times) {
    unsigned long long value = *(unsigned long long*)ptr;
    value = (1 << times) ^ value;
    *(unsigned long long*)ptr = value;
}

void TOGGLE(void* ptr, int wpos) {
    unsigned long long value = *(unsigned long long*)ptr;
    value = (1 << wpos) ^ value;
    *(unsigned long long*)ptr = value;
}

void SET(void* ptr, int pos) {
    unsigned long long value = *(unsigned long long*)ptr;
    value = (1 << pos) | value;
    *(unsigned long long*)ptr = value;
}

void CLEAR(void* ptr, int pos) {
    unsigned long long value = *(unsigned long long*)ptr;
    value = ~(1 << pos) & value;
    *(unsigned long long*)ptr = value;
}

void OnesToZeros(void* ptr) {
    unsigned long long value = *(unsigned long long*)ptr;
    value = (value & (value - 1));
    *(unsigned long long*)ptr = value;
}

void ELS(void* ptr) {
    unsigned long long value = *(unsigned long long*)ptr;
    value = (value & (-value));
    *(unsigned long long*)ptr = value;
}

void COPY(void* dest, void* src, int n) {
    unsigned long long mask = ~(~0 << n);
    unsigned long long srcValue = *(unsigned long long*)src;
    unsigned long long destValue = *(unsigned long long*)dest;
    destValue = (destValue & mask) | (srcValue & ~mask);
    *(unsigned long long*)dest = destValue;
}

void CountOnes(void* ptr, int* n) {
    int count = 0;
    unsigned long long value = *(unsigned long long*)ptr;
    for (int i = 0; value != 0; ++i) {
        value &= value - 1;
        ++count;
    }
    *n = count;
}
void print_bits(void* x, size_t size) {
    unsigned char* p = (unsigned char*)x;
    int i, j;
    for (i = size - 1; i >= 0; --i) {
        for (j = 7; j >= 0; --j) {
            printf("%d", (p[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

