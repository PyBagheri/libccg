#ifndef PIXELSCREEN_H_
#define PIXELSCREEN_H_

typedef struct Pixel {
    unsigned char r, g, b;
} Pixel;

typedef struct PixelScreen {
    int height;
    int width;
    Pixel* pixels;
} PixelScreen;


PixelScreen pscreen_init(int width, int height, Pixel empty_fill_pixel);

void pscreen_dealloc(PixelScreen screen);

Pixel* pscreen_trender(PixelScreen screen);
void pscreen_print(PixelScreen screen);

int pscreen_putpixel(PixelScreen screen, int x, int y, Pixel pixel);

#endif // PIXELSCREEN_H_