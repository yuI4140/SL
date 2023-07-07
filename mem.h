#include <stdlib.h>
typedef struct {
  size_t cap;
  size_t size;
  void* db; 
} Ren;
void rAssert(int condition); 
void rpAssert(void* condition); 
void rAssert(int condition); 
Ren* createRen(size_t cap); 
void destroyRen(Ren* ren); 
void* allocRen(Ren* ren, size_t size); 
void dropDown(Ren* ren); 
#ifdef MEM_IMP
void rAssert(int condition) {
  if (!condition) {
    exit(1);
  }
}
void rpAssert(void* condition){
  if (!condition) {
    exit(1);
  }
}
Ren* createRen(size_t cap) {
  Ren* ren = (Ren*)malloc(sizeof(Ren));
  ren->cap = cap;
  ren->size = 0;
  ren->db = malloc(cap);
  return ren;
}

void destroyRen(Ren* ren) {
  if (ren) {
    free(ren->db);
    free(ren);
  }
}

void* allocRen(Ren* ren, size_t size) {
  rAssert(!ren || size == 0);
  rAssert(ren->size + size > ren->cap);
  void* mem = ren->db + ren->size; 
  ren->size += size;
  return mem;
}

void dropDown(Ren* ren) {
  if (ren)
    ren->size = 0;
}
#endif // MEM_IMP
