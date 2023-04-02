#include <SDL2/SDL.h>
#include <stdbool.h>
#include <unistd.h>

#include "../../tools/cell_array.h"
#include "../../tools/window.h"
#include "../../tools/cell_array_drawer.h"
#include "../../tools/cell_array_terminal_drawer.h"

#define W 120
#define H 120
#define STATE_COUNT 8
#define FRAME_DELAY_MS 50

#define CA_INITIAL_CONFIG_FILE "res/langton_array.txt"
#define CA_RULE_FILE "res/langton_rule.txt"

//#define GUI

const static int R[STATE_COUNT] = {0, 192, 0, 0, 192, 192, 0, 192};
const static int G[STATE_COUNT] = {0, 0, 192, 0, 0, 192, 192, 192};
const static int B[STATE_COUNT] = {0, 0, 0, 192, 192, 0, 192, 192};

const static Pair pairs [STATE_COUNT]= {
        {1,COLOR_BLACK, COLOR_BLACK},
        {2,COLOR_RED, COLOR_BLACK},
        {3,COLOR_GREEN, COLOR_BLACK},
        {4,COLOR_BLUE, COLOR_BLACK},
        {5,COLOR_MAGENTA, COLOR_BLACK},
        {6,COLOR_YELLOW, COLOR_BLACK},
        {7,COLOR_CYAN, COLOR_BLACK},
        {8,COLOR_WHITE, COLOR_BLACK}
};

const static char chars [STATE_COUNT]= {'#','-','#','x','o','/','#','+'};

int main() {

#ifdef GUI
    Window *window = window_create("Langton", W, H, FRAME_DELAY_MS);
    CellArrayDrawer *ca_drawer = ca_drawer_create(R, G, B, 1, false);
#endif
#ifndef GUI
    CellArrayTermDrawer* ca_drawer = ca_term_drawer_create(pairs, chars,STATE_COUNT);
#endif

    CellArray *ca = ca_create(W, H);
    ca_init_from_file(ca, CA_INITIAL_CONFIG_FILE);

    CellArrayRule *ca_rule = ca_rule_create(NB_FIVE);
    ca_rule_init_from_file(ca_rule, CA_RULE_FILE);

    bool should_exit = false;
    while (!should_exit) {
        ca_evolve(ca, ca_rule);

#ifndef GUI
        ca_term_drawer_draw(ca_drawer, ca);
        usleep(100000);
#endif

#ifdef GUI
        should_exit = window_handle_events(window);
        ca_drawer_draw(ca_drawer, ca, window);
        window_update(window);
#endif
    }

#ifdef GUI
    window_destroy(window);
#endif
    return 0;
}