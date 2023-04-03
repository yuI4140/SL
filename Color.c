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

typedef struct {
    Rgb rgb;
    Hex hex;
} Color;

Color createColor(Rgb rgb, Hex hex) {
    Color color;
    color.rgb = rgb;
    color.hex = hex;
    return color;
}

void cprint(Color color) {
    printf("\033[38;2;%d;%d;%dm", color.rgb.r, color.rgb.g, color.rgb.b);
}

void freeColor(Color color) {
    free(color.hex.value);
}
