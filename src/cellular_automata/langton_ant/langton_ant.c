#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../../tools/cell_array.h"
#include "../../tools/window.h"
#include "../../tools/cell_array_drawer.h"

#define W 640
#define H 640
#define CELL_WIDTH 5
#define STATE_COUNT 10
#define FRAME_DELAY_MS 0

#define CA_INITIAL_CONFIG_FILE "res/langton_ant_array.txt"
#define CA_RULE_FILE "res/langton_ant_rule.txt"

const static int R[STATE_COUNT] = {255, 0,  0,  0, 192,192, 192,   0, 96, 0};
const static int G[STATE_COUNT] = {255, 0,192,  0, 0,    0, 192, 192, 96, 0};
const static int B[STATE_COUNT] = {255, 0,  0,192, 0,  192,   0, 192, 96, 96};

int main() {

    Window *window = window_create("Langton ant", W, H, FRAME_DELAY_MS);

    CellArray *ca = ca_create(W/CELL_WIDTH, H/CELL_WIDTH);
    ca_init_from_file(ca, CA_INITIAL_CONFIG_FILE);

    CellArrayRule *ca_rule = ca_rule_create(NB_FIVE);
    ca_rule_init_from_file(ca_rule, CA_RULE_FILE);

    CellArrayDrawer *ca_drawer = ca_drawer_create(R, G, B, CELL_WIDTH, true);

    bool should_exit = false;

    while (!should_exit) {
        should_exit = window_handle_events(window);
        ca_drawer_draw(ca_drawer, ca, window);
        window_update(window);
        ca_evolve(ca, ca_rule);
    }

    window_destroy(window);
    return 0;
}