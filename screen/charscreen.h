#ifndef CHARSCREEN_H
#define CHARSCREEN_H

typedef char Character;

typedef struct CharScreen {
    int height;
    int width;
    char *screen_chars;
} CharScreen;

CharScreen cscreen_init(int width, int height, Character empty_fill_char);

void cscreen_dealloc(CharScreen charscreen);

Character *cscreen_trender(CharScreen screen);
void cscreen_print(CharScreen screen);

int cscreen_putchar(CharScreen screen, int x, int y, Character c);

#endif // CHARSCREEN_H