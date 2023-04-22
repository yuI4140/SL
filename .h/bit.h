#pragma once
#include <stdio.h>

void FLIP(void *ptr, int times);
void TOGGLE(void *ptr, int wpos);
void SET(void *ptr, int pos);
void CLEAR(void *ptr, int pos);
void OnesToZeros(void *ptr);
void ELS(void *ptr);
void COPY(void *dest, void *src, int n);
void CountOnes(void *ptr, int *n);
void print_bits(void *x, size_t size);
