#include "menu.h"

int pointInRect(int x, int y, SDL_Rect r)
{
    return (x >= r.x && x <= r.x + r.w &&
            y >= r.y && y <= r.y + r.h);
}

void renderButton(SDL_Renderer* renderer, Button* b)
{
    SDL_RenderCopy(renderer,
        b->isHover ? b->hover : b->normal,
        NULL,
        &b->rect);
}

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
