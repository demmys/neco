#include <curses.h>
#include <unistd.h>

#define NECO_COLS 11
#define NECO_LINES 4

static const char NECO_WAIT_1[NECO_LINES][NECO_COLS] = {
    " \\    /\\  \0",
    "  )  ( ') \0",
    " (  /  )  \0",
    "  \\(__)l  \0"
};
static const char NECO_WAIT_2[NECO_LINES][NECO_COLS] = {
    "  /   /\\  \0",
    " (   ( ') \0",
    "  ) /  )  \0",
    "  \\(__)l  \0"
};
static const char NECO_WALK_1[NECO_LINES][NECO_COLS] = {
    " \\     /\\ \0",
    "  )___( ')\0",
    "  /____ ) \0",
    " / l  / l \0"
};
static const char NECO_WALK_2[NECO_LINES][NECO_COLS] = {
    " (     /\\ \0",
    "  )___( ')\0",
    "  (____ ) \0",
    "  l\\   l\\ \0"
};
static const char NECO_WALK_3[NECO_LINES][NECO_COLS] = {
    "   )   /\\ \0",
    "  (___( ')\0",
    "  /____ ) \0",
    " / l  / l \0"
};
static const char NECO_STAND_1[NECO_LINES][NECO_COLS] = {
    " \\     /\\ \0",
    "  )___( ')\0",
    " / ____ ) \0",
    " Ll    lL \0",
};
static const char NECO_STAND_2[NECO_LINES][NECO_COLS] = {
    " \\    /V\\ \0",
    "  )__('.')\0",
    " / ____ ) \0",
    " Ll    lL \0",
};
static const char NECO_STAND_3[NECO_LINES][NECO_COLS] = {
    " \\    /V\\ \0",
    "  )__(   )\0",
    " / ____ ) \0",
    " Ll    lL \0",
};

void mvaddstr_displayed(int y, int x, char *str) {
    for ( ; x < 0; ++x, ++str) {
        if (!*str) {
            return;
        }
    }
    for ( ; *str; ++str, ++x) {
        mvaddch(y, x, *str);
    }
}

void draw_neco(int x, int y, char neco[][NECO_COLS]) {
    int i;
    for (i = 0; i < NECO_LINES; ++i) {
        mvaddstr_displayed(y + i, x, neco[i]);
    }
    refresh();
}

int walk_right(int x, int y, int len) {
    int i;
    for (i = 0; i < len; ++i) {
        draw_neco(++x, y, NECO_WALK_1);
        usleep(200000);
        draw_neco(++x, y, NECO_WALK_2);
        usleep(200000);
        draw_neco(++x, y, NECO_WALK_3);
        usleep(200000);
        draw_neco(++x, y, NECO_WALK_2);
        usleep(200000);
    }
    return x;
}

void stand(int x, int y, int len) {
    int i;
    for (i = 0; i < len; ++i) {
        draw_neco(x, y, NECO_STAND_1);
        usleep(1000000);
        draw_neco(x, y, NECO_STAND_2);
        usleep(500000);
        draw_neco(x, y, NECO_STAND_1);
        usleep(500000);
        draw_neco(x, y, NECO_STAND_3);
        usleep(500000);
        draw_neco(x, y, NECO_STAND_1);
        usleep(1000000);
    }
}

void sit_down(int x, int y, int len) {
    int i;
    for (i = 0; i < len; ++i) {
        draw_neco(x, y, NECO_WAIT_1);
        usleep(1000000);
        draw_neco(x, y, NECO_WAIT_2);
        usleep(200000);
    }
}

int main(int argc, char const* argv[]) {
    initscr();
    curs_set(0);
    int x = -NECO_COLS;
    int y = LINES / 2 - NECO_LINES / 2;
    int walk_len = COLS / 2 - NECO_COLS / 2 - x;
    x = walk_right(x, y, walk_len / 4);
    stand(x, y, 1);
    while (1) {
        sit_down(x, y, 5);
    }
    endwin();
    return 0;
}
