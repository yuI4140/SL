#include "random.hpp"
void fisher_yates_shuffle(std::vector<int> &arr) {
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int i = arr.size() - 1; i > 0; --i) {
    std::uniform_int_distribution<int> dis(0, i);
    int j = dis(gen);
    std::swap(arr[i], arr[j]);
  }
}

i32 getRand(i32 start, i32 end) {
  static std::vector<int> num_array(100);
  static bool initialized = false;

  if (!initialized) {
    auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    for (int i = 0; i < 100; ++i) {
      num_array[i] = i;
    }
    fisher_yates_shuffle(num_array);
    initialized = true;
  }

  static int index = 0;
  int result = num_array[index] % (end - start + 1) + start;
  index = (index + 1) % 100;
  return result;
}
