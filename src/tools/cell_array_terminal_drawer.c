#include "cell_array_terminal_drawer.h"
#include "malloc.h"
#include "memory.h"
#include "unistd.h"
void init_ncurses(CellArrayTermDrawer * term_drawer);

CellArrayTermDrawer *ca_term_drawer_create(const Pair *pairs, const char *chars, int size){
    CellArrayTermDrawer init_ca_drawer = {pairs, chars, size};
    CellArrayTermDrawer *ca_drawer = malloc(sizeof(CellArrayTermDrawer));
    memcpy(ca_drawer, &init_ca_drawer, sizeof(CellArrayTermDrawer));

    init_ncurses(ca_drawer);
    return ca_drawer;
}

void init_ncurses(CellArrayTermDrawer * term_drawer){
    initscr();
    start_color();
    noecho();

    for(int i=0; i<term_drawer->size; i++){
        init_pair(term_drawer->pairs[i].index, term_drawer->pairs[i].fg_color, term_drawer->pairs[i].bg_color);
    }
}

void ca_term_drawer_draw(CellArrayTermDrawer *ca_drawer, CellArray *ca){
    for (int i = 0; i < ca->w; i++) {
        for (int j = 0; j < ca->h; j++) {
            int s = ca_get(ca, i, j);
            //if(i>=LINES || j >= COLS) continue;
            move(j,i);
            attron(COLOR_PAIR(s+1));
            addch(ca_drawer->chars[s]);
            attroff(COLOR_PAIR(s+1));
        }
    }
    refresh();
}