#include <screen/charscreen.h>
#include <stdlib.h>
#include <stdio.h>


CharScreen cs_init(int width, int height, Character empty_fill_char) {
    char (*screen_chars)[width] = malloc(sizeof(char) * width * height);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            screen_chars[j][i] = empty_fill_char;
        }
    }

    CharScreen charscreen = { .height=height, .width=width, .screen_chars=(char*)screen_chars };

    return charscreen;
}


void cs_dealloc(CharScreen screen) {
    free((char (*)[screen.width])screen.screen_chars);
}


void cs_print(CharScreen screen) {
    // explicit casting to suppress warnings
    char (*s)[screen.width] = (char (*)[screen.width])screen.screen_chars;

    for (int j = 0; j < screen.height; j++) {
        for (int i = 0; i < screen.width; i++) {
            putchar(s[j][i]);
        }

        putchar('\n');
    }
}

// TODO
// void cscreen_trender(CharScreen screen) {

// }


int cs_putchar(CharScreen screen, int x, int y, char c) {
    char (*s)[screen.width] = (char (*)[screen.width])screen.screen_chars;

    s[screen.height / 2 - y][screen.width / 2 + x] = c;
}
