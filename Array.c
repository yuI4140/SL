#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t size;
    size_t capacity;
    void** data;
} Array;

Array createArray(size_t capacity) {
    Array array;
    array.size = 0;
    array.capacity = capacity;
    array.data = (void**) malloc(capacity * sizeof(void*));
    return array;
}

void freeArray(Array* array) {
    for (int i = 0; i < array->size; i++) {
        free(array->data[i]);
    }
    free(array->data);
}

void pushBackArray(Array* array, void* data) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = (void**) realloc(array->data, array->capacity * sizeof(void*));
    }
    array->data[array->size++] = data;
}

void* getArray(Array array, int index) {
    return array.data[index];
}

void setArray(Array* array, int index, void* data) {
    free(array->data[index]);
    array->data[index] = data;
}
