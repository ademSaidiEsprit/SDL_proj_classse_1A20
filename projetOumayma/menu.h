#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct
{
    SDL_Rect rect;
    SDL_Texture* normal;
    SDL_Texture* hover;
    int isHover;
} Button;

int pointInRect(int x, int y, SDL_Rect r);
void renderButton(SDL_Renderer* renderer, Button* b);
void updateHover(Button* b, int x, int y, Mix_Chunk* sound);

#endif
