#include <SDL2/SDL.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "../../tools/cell_array.h"
#include "../../tools/window.h"
#include "../../tools/cell_array_drawer.h"
#include "../../tools/cell_array_terminal_drawer.h"

#define W 800
#define H 800
#define CELL_WIDTH 10
#define STATE_COUNT 2
#define FRAME_DELAY_MS 50
const static int R[STATE_COUNT] = {192, 0};
const static int G[STATE_COUNT] = {192, 0};
const static int B[STATE_COUNT] = {192, 0};

int game_of_life_rule(CellNeighborhood cn){
    int sum = 0;
    sum += cn.t;
    sum += cn.tr;
    sum += cn.r;
    sum += cn.br;
    sum += cn.b;
    sum += cn.bl;
    sum += cn.l;
    sum += cn.tl;

    if(cn.m == 1){
        if(sum <=1) return 0;
        if(sum >3) return 0;
        return 1;
    }

    if(cn.m == 0){
        if (sum == 3) return 1;
        return 0;
    }
}

int main() {


    Window *window = window_create("Cellular automata", W, H, FRAME_DELAY_MS);
    CellArrayDrawer *ca_drawer = ca_drawer_create(R, G, B, CELL_WIDTH, true);

    const int states[] = {0, 1};
    const double probas[] = {0.75, 1.};
    CellArray *ca = random_cell_array(W/CELL_WIDTH, H/CELL_WIDTH, states, probas);

    bool should_exit = false;
    while (!should_exit) {
        should_exit = window_handle_events(window);
        ca_drawer_draw(ca_drawer, ca, window);
        window_update(window);

        ca_custom_evolve(ca, game_of_life_rule);
    }

    window_destroy(window);
    return 0;
}