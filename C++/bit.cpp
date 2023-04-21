#include <iostream>

void FLIP(void* ptr, int times) {
    auto value = reinterpret_cast<unsigned long long*>(ptr);
    *value = (1ull << times) ^ *value;
}

void TOGGLE(void* ptr, int wpos) {
    auto value = reinterpret_cast<unsigned long long*>(ptr);
    *value = (1ull << wpos) ^ *value;
}

void SET(void* ptr, int pos) {
    auto value = reinterpret_cast<unsigned long long*>(ptr);
    *value = (1ull << pos) | *value;
}

void CLEAR(void* ptr, int pos) {
    auto value = reinterpret_cast<unsigned long long*>(ptr);
    *value = ~(1ull << pos) & *value;
}

void OnesToZeros(void* ptr) {
    auto value = reinterpret_cast<unsigned long long*>(ptr);
    *value = (*value) & ((*value) - 1);
}

void ELS(void* ptr) {
    auto value = reinterpret_cast<unsigned long long*>(ptr);
    *value = (*value) & (-(*value));
}

void COPY(void* dest, void* src, int n) {
    auto mask = ~(~0ull << n);
    auto srcValue = reinterpret_cast<unsigned long long*>(src);
    auto destValue = reinterpret_cast<unsigned long long*>(dest);
    *destValue = (*destValue & mask) | (*srcValue & ~mask);
}

void CountOnes(void* ptr, int* n) {
    int count = 0;
    auto value = reinterpret_cast<unsigned long long*>(ptr);
    for (auto i = 0; *value != 0; ++i) {
        *value &= (*value) - 1;
        ++count;
    }
    *n = count;
}

void print_bits(void* x, size_t size) {
    auto p = reinterpret_cast<unsigned char*>(x);
    int i, j;
    for (i = size - 1; i >= 0; --i) {
        for (j = 7; j >= 0; --j) {
            std::cout << ((p[i] >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}
