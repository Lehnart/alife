#include <SDL2/SDL.h>
#include <malloc.h>
#include <sys/time.h>
#include "../../tools/cell_array.h"
#include "../../tools/tools.h"

#define CA_W 120
#define CA_H 120

#define W 840
#define H 840
#define STATE_COUNT 9
#define FRAME_DELAY_MS 0

#define LOOP_SIZE 17
#define LOOP_X0 40
#define LOOP_Y0 40
#define CA_COUNT 49

void read_rule(int *rule) {
    FILE *file = fopen("res/evoloop_rule.txt", "R");

    char buffer[10] = {0};
    fgets(buffer, 10, file);

    while (buffer[0] >= '0' && buffer[0] <= '9') {
        int s = 0;
        s += (buffer[0] - '0') * 10000;
        s += (buffer[1] - '0') * 1000;
        s += (buffer[2] - '0') * 100;
        s += (buffer[3] - '0') * 10;
        s += (buffer[4] - '0') * 1;
        rule[s] = buffer[5] - '0';

        s = 0;
        s += (buffer[0] - '0') * 10000;
        s += (buffer[4] - '0') * 1000;
        s += (buffer[1] - '0') * 100;
        s += (buffer[2] - '0') * 10;
        s += (buffer[3] - '0') * 1;
        rule[s] = buffer[5] - '0';

        s = 0;
        s += (buffer[0] - '0') * 10000;
        s += (buffer[3] - '0') * 1000;
        s += (buffer[4] - '0') * 100;
        s += (buffer[1] - '0') * 10;
        s += (buffer[2] - '0') * 1;
        rule[s] = buffer[5] - '0';


        s = 0;
        s += (buffer[0] - '0') * 10000;
        s += (buffer[2] - '0') * 1000;
        s += (buffer[3] - '0') * 100;
        s += (buffer[4] - '0') * 10;
        s += (buffer[1] - '0') * 1;
        rule[s] = buffer[5] - '0';

        buffer[0] = '\0';
        fgets(buffer, 10, file);
    }
    fclose(file);
}

void init_ca(CellArray *ca, int x0, int y0, int size) {
    // upper part
    for (int i = 1; i < size - 1; i++) {
        ca_set(ca, x0 + i, y0, 2);
        if (i > 1 && i < size - 2) ca_set(ca, x0 + i, y0 + 2, 2);
    }

    // bottom part
    for (int i = 1; i < size - 1; i++) {
        ca_set(ca, x0 + i, y0 + size - 1, 2);
        if (i > 1 && i < size - 2) ca_set(ca, x0 + i, y0 + size - 3, 2);
    }

    // left part
    for (int j = 1; j < size - 1; j++) {
        ca_set(ca, x0, y0 + j, 2);
        if (j > 1 && j < size - 2) ca_set(ca, x0 + 2, y0 + j, 2);
    }

    // right part
    for (int j = 1; j < size - 1; j++) {
        ca_set(ca, x0 + size - 1, y0 + j, 2);
        if (j > 1 && j < size - 2) ca_set(ca, x0 + size - 3, y0 + j, 2);
    }

    ca_set(ca, x0 + size - 2, y0 + size - 1, 5);


    int genes[] = {0, 7, 1, 1, 1, 1, 0, 7, 1, 0, 7, 1, 0, 7, 1, 0, 7, 1, 0, 7, 1, 0, 7, 1, 0, 7, 1, 0, 7, 1, 0, 7, 1,
                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4, 1, 0, 4, 1};
    int good_genes[] = {0, 1, 4, 7};
    int genome_size = 4 * (LOOP_SIZE - 3);

    for (int i = 0; i < genome_size; i++) genes[i] = 1;
    for (int i = 2; i < 16; i++) {
        if (rand_double() > 0.33) {
            genes[i * 3] = 0;
            genes[(i * 3) + 1] = 7;
        }
    }

    genes[0] = 0;
    genes[1] = 7;
    genes[2] = 1;
    genes[50] = 0;
    genes[51] = 4;
    genes[52] = 1;
    genes[53] = 0;
    genes[54] = 4;
    genes[55] = 1;
    int genome_index = 0;

    printf("genome : ");
    for (int i = 0; i < genome_size; i++) { printf("%d", genes[i]); }
    printf("\n");

    for (int j = size - 3; j > 0; j--) {
        ca_set(ca, x0 + size - 2, y0 + j, genes[genome_index]);
        genome_index++;
    }

    for (int i = size - 3; i > 0; i--) {
        ca_set(ca, x0 + i, y0 + 1, genes[genome_index]);
        genome_index++;
    }

    for (int j = 2; j < size - 1; j++) {
        ca_set(ca, x0 + 1, y0 + j, genes[genome_index]);
        genome_index++;
    }

    for (int i = 2; i < size - 1; i++) {
        ca_set(ca, x0 + i, y0 + size - 2, genes[genome_index]);
        genome_index++;
    }

}

long evolve(CellArray *pCA, const int *rule) {

    int *intermediate_array = malloc(pCA->w * pCA->h * sizeof(int));

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            CellNeighborhood cn = ca_get_neighborhood(pCA, x, y);
            int s = 0;
            s += cn.m * 10000;
            s += cn.t * 1000;
            s += cn.r * 100;
            s += cn.b * 10;
            s += cn.l * 1;

            if (cn.m == 8) intermediate_array[x + (pCA->w * y)] = 0;
            else if (cn.t == 8 || cn.b == 8 || cn.l == 8 || cn.r == 8) {
                if (cn.m == 0 || cn.m == 1) {
                    if (
                            (cn.t >= 2 && cn.t <= 7) ||
                            (cn.r >= 2 && cn.r <= 7) ||
                            (cn.b >= 2 && cn.b <= 7) ||
                            (cn.l >= 2 && cn.l <= 7)
                            )
                        intermediate_array[x + (pCA->w * y)] = 8;
                    else intermediate_array[x + (pCA->w * y)] = cn.m;
                } else if (cn.m == 2 || cn.m == 3 || cn.m == 5) intermediate_array[x + (pCA->w * y)] = 0;
                else if (cn.m == 4 || cn.m == 6 || cn.m == 7) intermediate_array[x + (pCA->w * y)] = 1;
            } else intermediate_array[x + (pCA->w * y)] = rule[s];
        }
    }

    long count_modif = 0;
    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            if (pCA->array[x + (pCA->w * y)] != intermediate_array[x + (pCA->w * y)]) {
                count_modif++;
            }
            pCA->array[x + (pCA->w * y)] = intermediate_array[x + (pCA->w * y)];
        }
    }

    free(intermediate_array);

    return count_modif;
}

int main() {

    SDL_Window *p_window = create_window("Evoloop", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    if (p_window == NULL) { return 1; }

    CellArray *cas[CA_COUNT];
    for (int i = 0; i < CA_COUNT; i++) {
        cas[i] = ca_create(CA_W, CA_H);
    }

    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long m1 = te.tv_usec / 1000;
    gettimeofday(&te, NULL); // get current time
    long long m2 = te.tv_usec / 1000;
    gettimeofday(&te, NULL); // get current time
    long long m3 = te.tv_usec / 1000;
    rand_seed(m1, m2, m3);

    for (int i = 0; i < CA_COUNT; i++) init_ca(cas[i], LOOP_X0, LOOP_Y0, LOOP_SIZE);

    int r[STATE_COUNT] = {0, 128, 255, 255, 0, 0, 0, 255, 255};
    int g[STATE_COUNT] = {0, 128, 255, 0, 255, 0, 255, 255, 0};
    int b[STATE_COUNT] = {0, 128, 255, 0, 0, 255, 255, 0, 255};

    int rule[100000] = {0};
    for (int i = 0; i < 100000; i++) { if (i > 9999) rule[i] = 8; }
    read_rule(rule);

    Uint32 ticks = SDL_GetTicks();
    int is_over = 1;

    while (is_over) {

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                is_over = 0;
            }
        }

        Uint32 *pixels;
        int i, j;

        SDL_LockSurface(p_surf);
        pixels = (Uint32 *) p_surf->pixels;
        for (int ca_index = 0; ca_index < CA_COUNT; ca_index++) {
            CellArray *ca = cas[ca_index];
            int i0 = (ca_index % 7) * CA_W;
            int j0 = (ca_index / 7) * CA_H;
            for (i = 0; i < CA_W; i++) {
                for (j = 0; j < CA_H; j++) {

                    int s = ca_get(ca, i, j);
                    if (s > 0) s = ((s + ca_index) % (STATE_COUNT - 1)) + 1;
                    pixels[(i + i0) + ((j + j0) * W)] = SDL_MapRGBA(p_surf->format, r[s], g[s], b[s], 255);
                }
            }
            long modif_count = evolve(ca, rule);
            if (modif_count < 1l) {
                ca_reset(ca);
                init_ca(ca, LOOP_X0, LOOP_Y0, LOOP_SIZE);
            }
        }
        SDL_UnlockSurface(p_surf);
        SDL_UpdateWindowSurface(p_window);
        Uint32 delay = (SDL_GetTicks() - ticks);
        if (delay < FRAME_DELAY_MS) {
            SDL_Delay(FRAME_DELAY_MS - delay);
        }
        ticks = SDL_GetTicks();

    }

    SDL_DestroyWindow(p_window);
    SDL_Quit();

    return 0;
}