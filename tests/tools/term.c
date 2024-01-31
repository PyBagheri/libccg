#include <tests/tools/term.h>
#include <stdlib.h>
#include <stdio.h>


TScreen init_tscreen(int width, int height, char empty_fill_char) {
    char (*screen_chars)[width] = malloc(sizeof(char) * width * height);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            screen_chars[j][i] = empty_fill_char;
        }
    }

    TScreen screen = { .height=height, .width=width, .screen_chars=(char*)screen_chars };

    return screen;
}


void dealloc_tscreen(TScreen screen) {
    free((char (*)[screen.width])screen.screen_chars);
}


void tscreen_print(TScreen screen) {
    // explicit casting to suppress warnings
    char (*s)[screen.width] = (char (*)[screen.width])screen.screen_chars;

    for (int j = 0; j < screen.height; j++) {
        for (int i = 0; i < screen.width; i++) {
            putchar(s[j][i]);
        }

        putchar('\n');
    }
}


// put char in the 'data'.
// "put screen char"
int putschar(TScreen screen, int x, int y, char c) {
    char (*s)[screen.width] = (char (*)[screen.width])screen.screen_chars;

    s[screen.height / 2 - y][screen.width / 2 + x] = c;
}
