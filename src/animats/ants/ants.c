
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/time.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include  <SDL2/SDL2_rotozoom.h>
#include "../../tools/tools.h"
#include "ant.h"
#include "../../tools/image.h"

#define W 1280
#define H 720

#define FRAME_DELAY_MS 0

#define ANT_COUNT 50

void draw_ant(Ant *ant, SDL_Surface *image, SDL_Renderer *p_renderer, Uint8 r, Uint8 g, Uint8 b);

void draw_ant_carry(Ant *ant, SDL_Surface *image, SDL_Renderer *p_renderer);

int main() {

    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long time = 1000000 * tv.tv_sec + tv.tv_usec;
    rand_seed(time, time + 1, time + 2);

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_Window *p_window = create_window("ANTS", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);
    SDL_Renderer *p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *ant_image = SDL_LoadBMP("res/ant.bmp");
    SDL_Surface *ant_carry_image = SDL_LoadBMP("res/ant_carry.bmp");
    SDL_Surface *home_image = SDL_LoadBMP("res/home.bmp");
    SDL_Surface *target_image = SDL_LoadBMP("res/apple.bmp");

    int rs[5] = {0, 0, 0, 255, 255};
    int gs[5] = {0, 255, 0, 0, 255};
    int bs[5] = {0, 0, 255, 0, 0};
    int c_index = 0;

    Ant *ants[ANT_COUNT];
    for (int i = 0; i < ANT_COUNT; i++) ants[i] = ant_new((float) W, (float) H);
    AntInteraction interact;
    if (p_window == NULL) { return 1; }
    Uint32 ticks = SDL_GetTicks();
    int is_over = 0;
    while (!is_over) {

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                is_over = 1;
            }
        }

        SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(p_renderer);

        draw_image(target_image, TARGET_POS_X, TARGET_POS_Y, p_renderer);
        draw_image(home_image, HOME_POS_X, HOME_POS_Y, p_renderer);

        for (int i = 0; i < ANT_COUNT; i++) {
            interact = ant_interact(ants[i], ants, ANT_COUNT, i);
            if (interact.collision) c_index = 3;
            else if (interact.alignment) c_index = 2;
            else if (interact.seek) c_index = 4;
            else if (interact.cohesion) c_index = 1;
            else c_index = 0;
            if (ants[i]->is_carrying) draw_ant_carry(ants[i], ant_carry_image, p_renderer);
            else draw_ant(ants[i], ant_image, p_renderer, rs[c_index], gs[c_index], bs[c_index]);
            ant_update(ants[i], 0.002F, 0.F, 0.F, (float) W, (float) H);
        }

        SDL_RenderPresent(p_renderer);
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

void draw_ant(Ant *ant, SDL_Surface *image, SDL_Renderer *p_renderer, Uint8 r, Uint8 g, Uint8 b) {

    SDL_Surface *rotation = rotozoomSurface(image, -((ant_angle(ant) * 360.F / (2.F * PI))), 1.0, 1);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(p_renderer, rotation);
    SDL_SetTextureColorMod(texture, r, g, b);
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect rect = {((int) (ant->x)) - (w / 2), ((int) (ant->y)) - (h / 2), w, h};
    SDL_RenderCopy(p_renderer, texture, NULL, &rect);
    SDL_FreeSurface(rotation);
    SDL_DestroyTexture(texture);
}

void draw_ant_carry(Ant *ant, SDL_Surface *image, SDL_Renderer *p_renderer) {

    SDL_Surface *rotation = rotozoomSurface(image, -((ant_angle(ant) * 360.F / (2.F * PI))), 1.0, 1);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(p_renderer, rotation);
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect rect = {((int) (ant->x)) - (w / 2), ((int) (ant->y)) - (h / 2), w, h};
    SDL_RenderCopy(p_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(rotation);
}

