#ifndef CHARSCREEN_H
#define CHARSCREEN_H

typedef char Character;

typedef struct CharScreen {
    int height;
    int width;
    char *screen_chars;
} CharScreen;

CharScreen cs_init(int width, int height, Character empty_fill_char);

void cs_dealloc(CharScreen charscreen);

Character *cs_trender(CharScreen screen);
void cs_print(CharScreen screen);

int cs_putchar(CharScreen screen, int x, int y, Character c);

#endif // CHARSCREEN_H