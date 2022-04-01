#include <SDL2/SDL.h>
#include "texture.h"

SDL_Texture * texture_o(SDL_Renderer* renderer) {
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 3, 3);
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    void *temp;
    int pitch;
    Uint32 *pixels;
    SDL_LockTexture(texture, NULL, &temp, &pitch);
    pixels = temp;
    pixels[0 + (0 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[1 + (0 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[2 + (0 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[0 + (1 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[1 + (1 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[2 + (1 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[0 + (2 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[1 + (2 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[2 + (2 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    SDL_FreeFormat(format);
    SDL_UnlockTexture(texture);
    return texture;
}


SDL_Texture * texture_right(SDL_Renderer* renderer) {
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 3, 3);
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    void *temp;
    int pitch;
    Uint32 *pixels;
    SDL_LockTexture(texture, NULL, &temp, &pitch);
    pixels = temp;
    pixels[0 + (0 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[1 + (0 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[2 + (0 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[0 + (1 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[1 + (1 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[2 + (1 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[0 + (2 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[1 + (2 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[2 + (2 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    SDL_FreeFormat(format);
    SDL_UnlockTexture(texture);
    return texture;
}


SDL_Texture * texture_left_turn(SDL_Renderer* renderer) {
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 3, 3);
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    void *temp;
    int pitch;
    Uint32 *pixels;
    SDL_LockTexture(texture, NULL, &temp, &pitch);
    pixels = temp;
    pixels[0 + (0 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[1 + (0 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[2 + (0 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[0 + (1 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[1 + (1 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[2 + (1 * 3)] = SDL_MapRGBA(format, 0, 0, 0, (Uint8) 255);
    pixels[0 + (2 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[1 + (2 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    pixels[2 + (2 * 3)] = SDL_MapRGBA(format, 255, 255, 255, (Uint8) 255);
    SDL_FreeFormat(format);
    SDL_UnlockTexture(texture);
    return texture;
}