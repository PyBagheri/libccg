#ifndef PIXELSCREEN_H
#define PIXELSCREEN_H

typedef struct Pixel {
    unsigned char r, g, b;
} Pixel;

typedef struct PixelScreen {
    int height;
    int width;
    Pixel *pixels;
} PixelScreen;


PixelScreen ps_init(int width, int height, Pixel empty_fill_pixel);

void ps_dealloc(PixelScreen screen);

void ps_fill(PixelScreen screen, Pixel empty_fill_pixel);

Pixel *ps_trender(PixelScreen screen);
void ps_print(PixelScreen screen);

int ps_putpixel(PixelScreen screen, int x, int y, Pixel pixel);

#endif // PIXELSCREEN_H