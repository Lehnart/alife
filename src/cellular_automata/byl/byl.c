#include <stdbool.h>

#include "../../tools/cell_array.h"
#include "../../tools/window.h"
#include "../../tools/cell_array_drawer.h"

#define W 720
#define H 720
#define CELL_WIDTH 6
#define STATE_COUNT 6
#define FRAME_DELAY_MS 50

#define CA_INITIAL_CONFIG_FILE "res/byl_array.txt"
#define CA_RULE_FILE "res/byl_rule.txt"

const static int R[STATE_COUNT] = {0, 192, 0, 0, 192, 192};
const static int G[STATE_COUNT] = {0, 0, 192, 0, 0, 192};
const static int B[STATE_COUNT] = {0, 0, 0, 192, 192, 0};

int main() {

    Window *window = window_create("Byl", W, H, FRAME_DELAY_MS);

    CellArray *ca = ca_create(W/CELL_WIDTH, H/CELL_WIDTH);
    ca_init_from_file(ca, CA_INITIAL_CONFIG_FILE);

    CellArrayRule *ca_rule = ca_rule_create(NB_FIVE);
    ca_rule_init_from_file(ca_rule, CA_RULE_FILE);

    CellArrayDrawer *ca_drawer = ca_drawer_create(R, G, B, CELL_WIDTH, true);

    bool should_exit = false;

    while (!should_exit) {
        should_exit = window_handle_events(window);
        ca_evolve(ca, ca_rule);
        ca_drawer_draw(ca_drawer, ca, window);
        window_update(window);
    }

    window_destroy(window);
    return 0;
}