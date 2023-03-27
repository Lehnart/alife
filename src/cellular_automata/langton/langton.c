#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../../tools/cell_array.h"
#include "../../tools/window.h"
#include "../../tools/cell_array_drawer.h"

#define W 120
#define H 120
#define STATE_COUNT 8
#define FRAME_DELAY_MS 50

#define CA_INITIAL_CONFIG_FILE "res/langton_array.txt"
#define CA_RULE_SIZE 100000
#define CA_RULE_FILE "res/langton_rule.txt"

const static int R[STATE_COUNT] = {0, 192, 0, 0, 192, 192, 0, 192};
const static int G[STATE_COUNT] = {0, 0, 192, 0, 0, 192, 192, 192};
const static int B[STATE_COUNT] = {0, 0, 0, 192, 192, 0, 192, 192};

int main() {

    Window *window = window_create("Langton", W, H, FRAME_DELAY_MS);

    CellArray *ca = ca_create(W, H);
    ca_init_from_file(ca, CA_INITIAL_CONFIG_FILE);

    CellArrayRule *ca_rule = ca_rule_create(CA_RULE_SIZE);
    ca_rule_init_from_file(ca_rule, CA_RULE_FILE);

    CellArrayDrawer *ca_drawer = ca_drawer_create(R, G, B);

    bool should_exit = false;

    while (!should_exit) {
        should_exit = window_handle_events(window);
        ca_evolve(ca, ca_rule);
        ca_drawer_draw(ca_drawer, ca, window);
        window_update(window);
    }

    SDL_DestroyWindow(window->sdl_window);
    SDL_Quit();

    return 0;
}