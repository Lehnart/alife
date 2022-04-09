#include "turtle.h"
#include "../../tools/tools.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

char state1[1000000] = "F";
char next_state1[1000000];

char rule1[] = "F[+F]F[-F]";
char rule2[] = "F[+F]F[+F]";
char rule3[] = "F[-F]F[-F]";


void next(char* state, char* next_state, char* rule1, char* rule2, char* rule3 ){
    strcpy(next_state,"");
    for(int i=0; i < strlen(state); i++){

        char* rule;
        double r = rand_double();
        if( r < 0.333) rule = rule1;
        else if(r < 0.666) rule = rule2;
        else rule = rule3;

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
    rand_seed(456,45,54681);
    SDL_Window *p_window = create_window("test", WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    TurtlePainter * turtle_painter1 = turtle_new(NULL, WINDOW_WIDTH,WINDOW_HEIGHT,p_surf->format);

    turtle_goto(turtle_painter1, 400,WINDOW_HEIGHT-1);
    turtle_turn_left(turtle_painter1,-90);
    turtle_pen_down(turtle_painter1);


    for(int i =0; i<6;i++) next(state1, next_state1, rule1, rule2, rule3);

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
                (int)round(120.*rand_double()),
                (int)round(255.*rand_double()),
                (int)round(60.*rand_double())
        );

        SDL_LockSurface(p_surf);
        Uint32 *pixels = (Uint32 *) p_surf->pixels;
        turtle_set_pixels(turtle_painter1, pixels, WINDOW_WIDTH, WINDOW_HEIGHT, p_surf->format);

        char c = state1[state_index];
        if (state_index<strlen(state1)){
            if(c=='F'){
                turtle_forward(turtle_painter1,6);
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

        SDL_UnlockSurface(p_surf);
        SDL_UpdateWindowSurface(p_window);

        SDL_Delay(1);
        state_index++;

    }

    SDL_DestroyWindow(p_window);

    SDL_Quit();
    return 0;
}
