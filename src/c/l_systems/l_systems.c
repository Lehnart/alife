#include "../turtle.h"
#include "../tools.h"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

char state1[1000000] = "F";
char state2[1000000] = "F";
char state3[1000000] = "F";

char next_state1[1000000];
char next_state2[1000000];
char next_state3[1000000];

char rule1[] = "F[+F]F[-F]";
char rule2[] = "F[+F]F[-F][F]";
char rule3[] = "FF-[-F+F+F]+[+F-F-F]";


void next(char* state, char* next_state, char* rule){
    strcpy(next_state,"");
    for(int i=0; i < strlen(state); i++){
        if(state[i] == 'F'){
            strcat(next_state, rule);
        }
        else{
            char cs[2];
            cs[0] = state[i];
            cs[1] = '\0';
            strcat(next_state, cs);
        }
    }
    strcpy(state, next_state);
}

int main(){
    SDL_Window *p_window = create_window("test", 640, 480);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    TurtlePainter * turtle_painter1 = turtle_new(NULL, WINDOW_WIDTH,WINDOW_HEIGHT,p_surf->format);
    TurtlePainter * turtle_painter2 = turtle_new(NULL, WINDOW_WIDTH,WINDOW_HEIGHT,p_surf->format);
    TurtlePainter * turtle_painter3 = turtle_new(NULL, WINDOW_WIDTH,WINDOW_HEIGHT,p_surf->format);

    turtle_goto(turtle_painter1, 300,479);
    turtle_goto(turtle_painter2, 120,479);
    turtle_goto(turtle_painter3, 575,479);

    turtle_turn_left(turtle_painter1,-90);
    turtle_turn_left(turtle_painter2,-90);
    turtle_turn_left(turtle_painter3,-90);

    turtle_pen_down(turtle_painter1);
    turtle_pen_down(turtle_painter2);
    turtle_pen_down(turtle_painter3);

    for(int i =0; i<6;i++) next(state1, next_state1, rule1);
    for(int i =0; i<5;i++) next(state2, next_state2, rule2);
    for(int i =0; i<4;i++) next(state3, next_state3, rule3);

    int state_index = 0;
    bool is_over = false;
    while (!is_over) {

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                is_over = true;
            }
        }
        turtle_set_pen_color(
                turtle_painter1,
                (int) round(20.*rand_double()),
                (int)round(255.*rand_double()),
                (int)round(20.*rand_double())
        );

        turtle_set_pen_color(
                turtle_painter2,
                (int) round(20.*rand_double()),
                (int)round(255.*rand_double()),
                (int)round(128.*rand_double())
        );

        turtle_set_pen_color(
                turtle_painter3,
                (int) round(128.*rand_double()),
                (int)round(255.*rand_double()),
                (int)round(20.*rand_double())
        );


        SDL_LockSurface(p_surf);
        Uint32 *pixels = (Uint32 *) p_surf->pixels;
        turtle_set_pixels(turtle_painter1, pixels, WINDOW_WIDTH, WINDOW_HEIGHT, p_surf->format);
        turtle_set_pixels(turtle_painter2, pixels, WINDOW_WIDTH, WINDOW_HEIGHT, p_surf->format);
        turtle_set_pixels(turtle_painter3, pixels, WINDOW_WIDTH, WINDOW_HEIGHT, p_surf->format);

        char c = state1[state_index];
        if (state_index<strlen(state1)){
            if(c=='F'){
                turtle_forward(turtle_painter1,4);
            }
            else if(c=='['){
                turtle_backup(turtle_painter1);
            }
            else if(c==']'){
                turtle_restore(turtle_painter1);
            }
            else if(c=='+'){
                turtle_turn_left(turtle_painter1, 25.7);
            }
            else if(c=='-'){
                turtle_turn_left(turtle_painter1, -25.7);
            }
        }

        if (state_index<strlen(state2)) {
            c = state2[state_index];
            if (c == 'F') {
                turtle_forward(turtle_painter2, 7);
            } else if (c == '[') {
                turtle_backup(turtle_painter2);
            } else if (c == ']') {
                turtle_restore(turtle_painter2);
            } else if (c == '+') {
                turtle_turn_left(turtle_painter2, 20.);
            } else if (c == '-') {
                turtle_turn_left(turtle_painter2, -20.);
            }
        }

        if(state_index< strlen(state3)) {
            c = state3[state_index];
            if (c == 'F') {
                turtle_forward(turtle_painter3, 7);
            } else if (c == '[') {
                turtle_backup(turtle_painter3);
            } else if (c == ']') {
                turtle_restore(turtle_painter3);
            } else if (c == '+') {
                turtle_turn_left(turtle_painter3, 22.5);
            } else if (c == '-') {
                turtle_turn_left(turtle_painter3, -22.5);
            }
        }
        SDL_UnlockSurface(p_surf);
        SDL_UpdateWindowSurface(p_window);

        SDL_Delay(7);
        state_index++;

    }

    SDL_DestroyWindow(p_window);

    SDL_Quit();
    return 0;
}
