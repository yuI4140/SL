#include ".h/random.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void fisher_yates_shuffle(i32 *arr, i32 n);
i32 getRand(i32 start, i32 end);

#ifdef D_RANDOM
void fisher_yates_shuffle(i32 *arr, i32 n) {
  for (int i = n - 1; i > 0; --i) {
    int j = rand() % (i + 1);
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

i32 getRand(i32 start, i32 end) {
  static i32 num_array[100];
  static b8 initialized = false;

  if (!initialized) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    srand(ts.tv_nsec);
    for (i32 i = 0; i < 100; ++i) {
      num_array[i] = i;
    }
    fisher_yates_shuffle(num_array, 100);
    initialized = true;
  }

  static i32 index = 0;
  int result = num_array[index] % (end - start + 1) + start;
  index = (index + 1) % 100;
  return result;
}
#endif /* ifdef D_RANDOM */
