#ifndef TERM_H_
#define TERM_H_

typedef struct TScreen {
    int height;
    int width;
    char* screen_chars;
} TScreen;

TScreen init_tscreen(int width, int height, char empty_fill_char);
void dealloc_tscreen(TScreen screen);

void tscreen_print(TScreen screen);

int putschar(TScreen screen, int x, int y, char c);

#endif // TERM_H_