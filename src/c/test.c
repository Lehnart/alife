#include "turtle.h"
#include "tools.h"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(){
    SDL_Window *p_window = create_window("test", 640, 480);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    TurtlePainter * turtle_painter = turtle_new(NULL, WINDOW_WIDTH,WINDOW_HEIGHT,p_surf->format);
    turtle_goto(turtle_painter, 320,240);
    turtle_pen_down(turtle_painter);

    bool is_over = false;
    while (!is_over) {

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                is_over = true;
            }
        }

        SDL_LockSurface(p_surf);
        Uint32 *pixels = (Uint32 *) p_surf->pixels;
        turtle_set_pixels(turtle_painter, pixels, WINDOW_WIDTH, WINDOW_HEIGHT, p_surf->format);
        turtle_set_direction(turtle_painter, rand_double()*360);
        turtle_set_pen_color(
                turtle_painter,
                (int) round(255.*rand_double()),
                (int)round(255.*rand_double()),
                (int)round(255.*rand_double())
                );
        turtle_forward(turtle_painter,5);
        SDL_UnlockSurface(p_surf);
        SDL_UpdateWindowSurface(p_window);
        SDL_Delay(50);
    }

    SDL_DestroyWindow(p_window);

    SDL_Quit();
    return 0;
}
