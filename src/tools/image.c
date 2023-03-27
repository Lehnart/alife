#include <SDL2/SDL.h>

void draw_image(SDL_Surface *image, int x, int y, SDL_Renderer *p_renderer) {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(p_renderer, image);
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(p_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}