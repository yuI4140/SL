#pragma once
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct {
    int r;
    int g;
    int b;
} Rgb;

typedef struct  {
    char* value;
} Hex;
Rgb newRgb(int r, int g, int b){
    Rgb color={r,g,b};
return color;
}
#define RED newRgb(0xFF,0,0)
#define GREEN newRgb(0,0xFF,0)
#define BLUE newRgb(0,0,0xFF)
#define WHITE newRgb(0xFF,0xFF,0xFF)
Rgb hexToRgb(Hex hex) {
    Rgb rgb = {0, 0, 0};
    if (strlen(hex.value) == 7 && hex.value[0] == '#') {
        char r_str[3], g_str[3], b_str[3];
        strncpy(r_str, hex.value + 1, 2);
        strncpy(g_str, hex.value + 3, 2);
        strncpy(b_str, hex.value + 5, 2);
        rgb.r = strtol(r_str, NULL, 16);
        rgb.g = strtol(g_str, NULL, 16);
        rgb.b = strtol(b_str, NULL, 16);
    }
    return rgb;
}

