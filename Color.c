#pragma once
#include "core.h"
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
#ifdef COLORS
#define RED newRgb(0xFF,0,0)
#define GREEN newRgb(0,0xFF,0)
#define BLUE newRgb(0,0,0xFF)
#define WHITE newRgb(0xFF,0xFF,0xFF)
#define BLACK newRgb(0x00, 0x00, 0x00)
#define YELLOW newRgb(0xFF, 0xFF, 0x00)
#define CYAN newRgb(0x00, 0xFF, 0xFF)
#define MAGENTA newRgb(0xFF, 0x00, 0xFF)
#define ORANGE newRgb(0xFF, 0xA5, 0x00)
#define PINK newRgb(0xFF, 0xC0, 0xCB)
#define PURPLE newRgb(0x80, 0x00, 0x80)
#define GOLD newRgb(0xFF, 0xD7, 0x00)
#define GRAY newRgb(0x80, 0x80, 0x80)
#define LIGHT_GRAY newRgb(0xD3, 0xD3, 0xD3)
#define DARK_GRAY newRgb(0xA9, 0xA9, 0xA9)
#define SILVER newRgb(0xC0, 0xC0, 0xC0)
#define BEIGE newRgb(0xF5, 0xF5, 0xDC)
#define BROWN newRgb(0xA5, 0x2A, 0x2A)
#define MAROON newRgb(0x80, 0x00, 0x00)
#define OLIVE newRgb(0x80, 0x80, 0x00)
#define NAVY newRgb(0x00, 0x00, 0x80)
#define FUCHSIA newRgb(0xFF,0x00,0xFF)
#define TEAL newRgb(0x00, 0x80, 0x80)
#define CORAL newRgb(0xFF,0x7F,0x50)
#define TOMATO newRgb(0xFF,0x63,0x47)
#define DARKORANGE newRgb(0xFF,0x8C,0x00)
#define DARK_GREEN newRgb(0x00, 0x64, 0x00)
#define LIGHT_GREEN newRgb(0x90, 0xEE, 0x90)
#define FOREST_GREEN newRgb(0x22, 0x8B, 0x22)
#define SEA_GREEN newRgb(0x2E, 0x8B, 0x57)
#define SKY_BLUE newRgb(0x87, 0xCE, 0xEB)
#define LIGHT_BLUE newRgb(0xAD, 0xD8, 0xE6)
#define STEEL_BLUE newRgb(0x46, 0x82, 0xB4)
#define ROYAL_BLUE newRgb(0x41, 0x69, 0xE1)
#define INDIGO newRgb(0x4B, 0x00, 0x82)
#define TURQUOISE newRgb(0x40, 0xE0, 0xD0)
#define LIGHT_CYAN newRgb(0xE0, 0xFF, 0xFF)
#define DARK_CYAN newRgb(0x00, 0x8B, 0x8B)
#define CORAL newRgb(0xFF, 0x7F, 0x50)
#define SALMON newRgb(0xFA, 0x80, 0x72)
#define FIREBRICK newRgb(0xB2,0x22,0x22)
#define INDIANRED newRgb(0xCD,0x5C,0x5C)
#define LIGHTCORAL newRgb(0xF0,0x80,0x80)
#define SALMON newRgb(0xFA,0x80,0x72)
#define DARKSALMON newRgb(0xE9,0x96,0x7A)
#define LIGHTSALMON newRgb(0xFF,0xA0,0x7A)
#define HOTPINK newRgb(0xFF,0x69,0xB4)
#define PINK newRgb(0xFF,0xC0,0xCB)
#define DEEPPINK newRgb(0xFF,0x14,0x93)
#define MEDIUMVIOLETRED newRgb(0xC7,0x15,0x85)
#define PALEVIOLETRED newRgb(0xDB,0x70,0x93)
#define LIGHTPINK newRgb(0xFF,0xB6,0xC1)
#define ROYALBLUE newRgb(0x41,0x69,0xE1)
#define BLUEVIOLET newRgb(0x8A,0x2B,0xE2)
#define INDIGO newRgb(0x4B,0x00,0x82)
#define DARKSLATEBLUE newRgb(0x48,0x3D,0x8B)
#define MEDIUMSLATEBLUE newRgb(0x7B,0x68,0xEE)
#define SLATEBLUE newRgb(0x6A,0x5A,0xCD)
#define GHOSTWHITE newRgb(0xF8,0xF8,0xFF)
#define CRIMSON newRgb(0xDC, 0x14, 0x3C)
#endif /*COLORS*/

