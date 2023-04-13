#include <SDL2/SDL.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "../tools/cell_array.h"
#include "../tools/window.h"
#include "../tools/cell_array_drawer.h"
#include "../tools/cell_array_terminal_drawer.h"

#include "config.h"

int main() {

#ifdef GUI
    Window *window = window_create("Langton", W, H, FRAME_DELAY_MS);
    CellArrayDrawer *ca_drawer = ca_drawer_create(R, G, B, CELL_WIDTH, true);
#endif
#ifndef GUI
    CellArrayTermDrawer *ca_drawer = ca_term_drawer_create(pairs, chars, STATE_COUNT);
#endif

    CellArray *ca = ca_create(W / CELL_WIDTH, H / CELL_WIDTH);
    ca_init_from_file(ca, CA_INITIAL_CONFIG_FILE);

    CellArrayRule *ca_rule = ca_rule_create(NB_FIVE);
    ca_rule_init_from_file(ca_rule, CA_RULE_FILE);

    bool should_exit = false;
    while (!should_exit) {

#ifndef GUI
        ca_term_drawer_draw(ca_drawer, ca);
        usleep(100000);
#endif

#ifdef GUI
        should_exit = window_handle_events(window);
        ca_drawer_draw(ca_drawer, ca, window);
        window_update(window);
#endif
        ca_evolve(ca, ca_rule);
    }

#ifdef GUI
    window_destroy(window);
#endif
    return 0;
}