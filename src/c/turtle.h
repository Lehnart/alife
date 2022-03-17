#ifndef ALIFE_TURTLE_H
#define ALIFE_TURTLE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

typedef struct {
    double x_pos;
    double y_pos;
    double direction;

    RGB pen_color;
    bool is_pen_down;

} Turtle;

typedef struct {
    Uint32 *pixels;
    int width;
    int height;
    SDL_PixelFormat *format;

    Turtle* turtle;
    Turtle* backup_turtle;
} TurtlePainter;


TurtlePainter * turtle_new(Uint32* pixels, int width, int height, SDL_PixelFormat* format);

void turtle_set_pixels(TurtlePainter *turtle_painter, Uint32* pixels, int width, int height, SDL_PixelFormat* format);

void turtle_delete(TurtlePainter *turtle);

void turtle_reset(Turtle *turtle);

void turtle_backup(TurtlePainter *turtle);

void turtle_restore(TurtlePainter *turtle);

void turtle_forward(TurtlePainter *turtle, int pixels);

void turtle_turn_left(TurtlePainter *turtle, double angle);

void turtle_turn_right(TurtlePainter *turtle, double angle);

void turtle_pen_up(TurtlePainter *turtle);

void turtle_pen_down(TurtlePainter *turtle);

void turtle_goto(TurtlePainter *turtle, int x, int y);

void turtle_goto_real(TurtlePainter *turtle, double x, double y);

void turtle_set_direction(TurtlePainter *turtle, double angle);

void turtle_set_pen_color(TurtlePainter *turtle, int red, int green, int blue);


#endif //ALIFE_TURTLE_H
