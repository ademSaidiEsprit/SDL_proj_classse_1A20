#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
    SDL_Texture *normal;
    SDL_Texture *hover;
    SDL_Texture *clicked;
    SDL_Rect rect;
    int state; // 0 normal, 1 hover, 2 clicked
    int wasHover;
} Button;



void initButton(Button *btn, SDL_Renderer *renderer,char img[],  char over[], char click[],
                int x, int y);

void renderButton(Button *btn, SDL_Renderer *renderer);

int handleButtonEvent(Button *btn, SDL_Event *e, Mix_Chunk *hoverSound);

void destroyButton(Button *btn);

#endif
