#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"

void updateLayout(SDL_Renderer *renderer, Button *btnOui, Button *btnNon,Button *btnLoad,Button *btnNew, SDL_Rect *recTxt);
int runSaveMenu(SDL_Renderer *renderer);

#endif
