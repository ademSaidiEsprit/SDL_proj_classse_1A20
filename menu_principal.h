#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 800
#define HEIGHT 600

typedef enum {
    MENU_PRINCIPAL,
    MENU_SAUVEGARDE,
    MENU_OPTION,
    MENU_SCORE
} Etat;

typedef struct
{
    SDL_Texture *background;
    SDL_Texture *boutonTexture[5];
    SDL_Texture *boutonHover[5];
    SDL_Texture *title;
    SDL_Texture *shadow;

    SDL_Rect buttons[5];
    SDL_Rect titlePos;
    SDL_Rect shadowPos;

    Mix_Music *music;
    Mix_Chunk *hoverSound;

    TTF_Font *font;

    int selected;
    Etat etat;

} Menu;

void initMenu(Menu *menu, SDL_Renderer *renderer);
int handleMenuEvent(Menu *menu, SDL_Event *event);
void updateMenu(Menu *menu);
void renderMenu(Menu *menu, SDL_Renderer *renderer);
void destroyMenu(Menu *menu);

#endif
