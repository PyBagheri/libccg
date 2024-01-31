#ifndef SCREEN_H_
#define SCREEN_H_

typedef struct TScreen {
    int height;
    int width;
    char* screen_chars;
} TScreen;

TScreen tscreen_init(int width, int height, char empty_fill_char);
void tscreen_dealloc(TScreen screen);

void tscreen_print(TScreen screen);

int tscreen_putchar(TScreen screen, int x, int y, char c);

#endif // SCREEN_H_