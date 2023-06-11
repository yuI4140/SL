#pragma once
// A wrapper for C Dynamic Mem Funcs
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void* wMalloc(size_t size);
void* wCalloc(size_t count, size_t size);
void* wRealloc(void* ptr, size_t size);
void  wFree(void* ptr);
#ifdef MEM_IMP
void* wMalloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("MEMORY_ERROR_ALLOCATION_FAILED\n");
    } 
    return ptr;
}
void* wCalloc(size_t count, size_t size) {
    void* ptr = calloc(count, size);
    if (ptr == NULL) {
        printf("MEMORY_ERROR_ALLOCATION_FAILED\n");
    }
    return ptr;
}
void* wRealloc(void* ptr, size_t size {
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        printf("MEMORY_ERROR_REALLOCATION_FAILED\n");
    } 
    return new_ptr;
}
void wFree(void* ptr) {
    free(ptr);
}
#endif
