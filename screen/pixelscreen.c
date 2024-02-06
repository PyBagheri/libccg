#include <screen/pixelscreen.h>
#include <stdlib.h>
#include <stdio.h>


PixelScreen pscreen_init(int width, int height, Pixel empty_fill_pixel) {
    Pixel (*pixels)[width] = malloc(sizeof(Pixel) * width * height);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            pixels[j][i] = empty_fill_pixel;
        }
    }

    PixelScreen pixelscreen = { .height=height, .width=width, .pixels=(Pixel*)pixels };

    return pixelscreen;
}


void pscreen_dealloc(PixelScreen screen) {
    free((Pixel (*)[screen.width])screen.pixels);
}


void pscreen_fill(PixelScreen screen, Pixel empty_fill_pixel) {
    Pixel (*pixels)[screen.width] = (Pixel (*)[screen.width])screen.pixels;

    for (int j = 0; j < screen.height; j++) {
        for (int i = 0; i < screen.width; i++) {
            pixels[j][i] = empty_fill_pixel;
        }
    }
}


void print_terminal_char(Pixel upper, Pixel lower) {
    printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm▀", upper.r, upper.g, upper.b, lower.r, lower.g, lower.b);
}


void pscreen_print(PixelScreen screen) {
    // explicit casting to suppress warnings
    Pixel (*pixels)[screen.width] = (Pixel (*)[screen.width])screen.pixels;

    // we will assume each terminal character
    // a rectangle whose height is twice as long
    // as its width.
    for (int xj = 0; xj < screen.height; xj+=2) {
        for (int i = 0; i < screen.width; i++) {
            print_terminal_char(pixels[xj][i], pixels[xj+1][i]);
        }

        printf("\033[0m\n");
    }
}


// TODO
// void pscreen_trender(PixelScreen screen) {

// }


int pscreen_putpixel(PixelScreen screen, int x, int y, Pixel pixel) {
    Pixel (*pixels)[screen.width] = (Pixel (*)[screen.width])screen.pixels;

    pixels[screen.height / 2 - y][screen.width / 2 + x] = pixel;
}
