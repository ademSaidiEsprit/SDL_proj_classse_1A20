#include "menu.h"

// Vérifie si un point (x,y) est dans un rectangle r
int pointInRect(int x, int y, SDL_Rect r)
{
    return (x >= r.x && x < r.x + r.w &&
            y >= r.y && y < r.y + r.h);
}

// Affiche le bouton selon son état (hover ou normal)
void renderButton(SDL_Renderer* renderer, Button* b)
{
    SDL_RenderCopy(renderer,
        b->isHover ? b->hover : b->normal,
        NULL,
        &b->rect);
}

// Met à jour l'état hover et joue le son si nécessaire
void updateHover(Button* b, int x, int y, Mix_Chunk* sound)
{
    if(pointInRect(x,y,b->rect))
    {
        if(!b->isHover)
        {
            Mix_PlayChannel(-1, sound, 0);
            b->isHover = 1;
        }
    }
    else
        b->isHover = 0;
}
