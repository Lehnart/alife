#include "turtle.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include <SDL2/SDL_pixels.h>

#define ABS(X) ((X)>0 ? (X) : (-(X)))
#define PI 3.141592653589793

void turtle_draw_pixel(TurtlePainter *turtle_painter, int x, int y) {
    Turtle * turtle = turtle_painter->turtle;
    turtle_painter->pixels[x + (y * turtle_painter->width)] = SDL_MapRGBA(
            turtle_painter->format,
            turtle->pen_color.red,
            turtle->pen_color.green,
            turtle->pen_color.blue,
            255
            );
}


void turtle_draw_line(TurtlePainter *turtle_painter, int x0, int y0, int x1, int y1) {
    int absX = ABS(x1 - x0);          // absolute value of coordinate distances
    int absY = ABS(y1 - y0);
    int offX = x0 < x1 ? 1 : -1;      // line-drawing direction offsets
    int offY = y0 < y1 ? 1 : -1;
    int x = x0;                     // incremental location
    int y = y0;
    int err;

    turtle_draw_pixel(turtle_painter, x, y);
    if (absX > absY) {

        // line is more horizontal; increment along x-axis
        err = absX / 2;
        while (x != x1) {
            err = err - absY;
            if (err < 0) {
                y += offY;
                err += absX;
            }
            x += offX;
            turtle_draw_pixel(turtle_painter, x, y);
        }
    } else {

        // line is more vertical; increment along y-axis
        err = absY / 2;
        while (y != y1) {
            err = err - absX;
            if (err < 0) {
                x += offX;
                err += absY;
            }
            y += offY;
            turtle_draw_pixel(turtle_painter, x, y);
        }
    }
}

void turtle_set_pixels(TurtlePainter *turtle_painter, Uint32* pixels, int width, int height, SDL_PixelFormat* format){
    turtle_painter->pixels = pixels;
    turtle_painter->width = width;
    turtle_painter->height = height;
    turtle_painter->format = format;
}

TurtlePainter * turtle_new(Uint32* pixels, int width, int height, SDL_PixelFormat* format) {
    Turtle *turtle = malloc(sizeof(Turtle));
    Turtle *backup_turtle = malloc(sizeof(Turtle));
    TurtlePainter *turtle_painter = malloc(sizeof(TurtlePainter));

    turtle_painter->turtle = turtle;
    turtle_painter->backup_turtle = backup_turtle;

    turtle_set_pixels(turtle_painter, pixels, width, height, format);

    turtle_reset(turtle);
    turtle_reset(backup_turtle);

    return turtle_painter;
}

void turtle_delete(TurtlePainter *turtle_painter) {
    free(turtle_painter->turtle);
    free(turtle_painter->backup_turtle);
    free(turtle_painter);
}


void turtle_reset(Turtle *turtle) {
    turtle->x_pos = 0.0;
    turtle->y_pos = 0.0;
    turtle->direction = 0.0;
    turtle->pen_color.red = 0;
    turtle->pen_color.green = 0;
    turtle->pen_color.blue = 0;
    turtle->is_pen_down = false;
}

void turtle_backup(TurtlePainter *turtle_painter) {
    *(turtle_painter->backup_turtle) = *(turtle_painter->turtle);
}

void turtle_restore(TurtlePainter *turtle_painter) {
    *(turtle_painter->turtle) = *(turtle_painter->backup_turtle);
}

void turtle_forward(TurtlePainter *turtle_painter, int pixels) {
    Turtle* turtle = turtle_painter->turtle;
    double radians = turtle->direction * PI / 180.0;
    double dx = cos(radians) * pixels;
    double dy = sin(radians) * pixels;
    turtle_goto_real(turtle_painter, turtle->x_pos + dx, turtle->y_pos + dy);
}

void turtle_turn_left(TurtlePainter *turtle_painter, double angle) {
    Turtle * turtle= turtle_painter->turtle;
    turtle->direction += angle;
    if (turtle->direction < 0.0) {
        turtle->direction += 360.0;
    } else if (turtle->direction >= 360.0) {
        turtle->direction -= 360.0;
    }
}

void turtle_turn_right(TurtlePainter *turtle_painter, double angle) {
    turtle_turn_left(turtle_painter, -angle);
}

void turtle_pen_up(TurtlePainter *turtle_painter) {
    turtle_painter->turtle->is_pen_down = false;
}

void turtle_pen_down(TurtlePainter *turtle_painter) {
    turtle_painter->turtle->is_pen_down = true;
}

void turtle_goto(TurtlePainter *turtle_painter, int x, int y) {
    turtle_goto_real(turtle_painter, (double) x, (double) y);
}

void turtle_goto_real(TurtlePainter *turtle_painter, double x, double y) {
    Turtle * turtle = turtle_painter->turtle;

    // draw line if pen is down
    if (turtle->is_pen_down) {
        turtle_draw_line(
                turtle_painter,
                (int) round(turtle->x_pos),
                (int) round(turtle->y_pos),
                (int) round(x),
                (int) round(y));
    }

    // change current turtle position
    turtle->x_pos = (double) x;
    turtle->y_pos = (double) y;
}

void turtle_set_direction(TurtlePainter *turtle_painter, double angle) {
    turtle_painter->turtle->direction = angle;
}

void turtle_set_pen_color(TurtlePainter *turtle_painter, int red, int green, int blue) {
    Turtle * turtle = turtle_painter->turtle;
    turtle->pen_color.red = red;
    turtle->pen_color.green = green;
    turtle->pen_color.blue = blue;
}

