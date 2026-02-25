#include "button.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>



void initButton(Button *btn, SDL_Renderer *renderer,
                char img[], char over[],char click[],
                int x, int y)
{
    btn->normal = IMG_LoadTexture(renderer, img);
    btn->hover = IMG_LoadTexture(renderer, over);
    btn->clicked = IMG_LoadTexture(renderer, click);
	int w,h;
    SDL_QueryTexture(btn->normal, NULL, NULL, &w, &h);
	
	btn->rect.w=w/20;
	btn->rect.h=h/20;
    btn->rect.x = x;
    btn->rect.y = y;
    btn->state = 0;
    btn->wasHover = 0;
}

void renderButton(Button *btn, SDL_Renderer *renderer)
{
    if (btn->state == 0)
        SDL_RenderCopy(renderer, btn->normal, NULL, &btn->rect);
    else if (btn->state == 1)
        SDL_RenderCopy(renderer, btn->hover, NULL, &btn->rect);
    else
        SDL_RenderCopy(renderer, btn->clicked, NULL, &btn->rect);
}

int handleButtonEvent(Button *btn, SDL_Event *e, Mix_Chunk *hoverSound)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int inside = mouseX > btn->rect.x &&
                 mouseX < btn->rect.x + btn->rect.w &&
                 mouseY > btn->rect.y &&
                 mouseY < btn->rect.y + btn->rect.h;

    if (inside) {
        btn->state = 1;

        if (!btn->wasHover) {
            Mix_PlayChannel(-1, hoverSound, 0);
            btn->wasHover = 1;
        }

        if (e->type == SDL_MOUSEBUTTONDOWN) {
            btn->state = 2;
        }

        if (e->type == SDL_MOUSEBUTTONUP) {
            return 1; // bouton cliqué
        }
    } else {
        btn->state = 0;
        btn->wasHover = 0;
    }

    return 0;
}

void destroyButton(Button *btn)
{
    SDL_DestroyTexture(btn->normal);
    SDL_DestroyTexture(btn->hover);
    SDL_DestroyTexture(btn->clicked);
}
