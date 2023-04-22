#include ".h/color.h"
Rgb newRgb(int r, int g, int b) {
  Rgb color = {r, g, b};
  return color;
}
Rgb hexToRgb(Hex hex) {
  Rgb rgb = {0, 0, 0};
  if (strlen(hex.value) == 7 && hex.value[0] == '#') {
    char r_str[3], g_str[3], b_str[3];
    strncpy(r_str, hex.value + 1, 2);
    strncpy(g_str, hex.value + 3, 2);
    strncpy(b_str, hex.value + 5, 2);
    rgb.r = strtol(r_str, nullptr, 16);
    rgb.g = strtol(g_str, nullptr, 16);
    rgb.b = strtol(b_str, nullptr, 16);
  }
  return rgb;
}