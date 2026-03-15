#include "menu_principal.h"
#include <stdio.h>

void initMenu(Menu *menu, SDL_Renderer *renderer)
{
    menu->background = IMG_LoadTexture(renderer, "assets/arriere plan.jpg");

    menu->music = Mix_LoadMUS("assets/background.mp3");
    Mix_PlayMusic(menu->music, -1);

    menu->hoverSound = Mix_LoadWAV("assets/clic.wav");

    SDL_Color gold = {255,215,0,255};
    SDL_Color black = {0,0,0,255};

    menu->font = TTF_OpenFont("assets/aa.ttf", 60);

    SDL_Surface *surface =
        TTF_RenderText_Blended(menu->font, "MENU", gold);
    menu->title =
        SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Surface *shadowSurface =
        TTF_RenderText_Blended(menu->font, "MENU", black);
    menu->shadow =
        SDL_CreateTextureFromSurface(renderer, shadowSurface);
    SDL_FreeSurface(shadowSurface);

    SDL_QueryTexture(menu->title, NULL, NULL,
                     &menu->titlePos.w, &menu->titlePos.h);

    menu->titlePos.x = (WIDTH - menu->titlePos.w) / 2;
    menu->titlePos.y = 40;

    menu->shadowPos = menu->titlePos;
    menu->shadowPos.x += 4;
    menu->shadowPos.y += 4;

    menu->boutonTexture[0] = IMG_LoadTexture(renderer, "assets/JOUER.png");
    menu->boutonTexture[1] = IMG_LoadTexture(renderer, "assets/OPTION.png");
    menu->boutonTexture[2] = IMG_LoadTexture(renderer, "assets/SCORE.png");
    menu->boutonTexture[3] = IMG_LoadTexture(renderer, "assets/HISTOIRE.png");
    menu->boutonTexture[4] = IMG_LoadTexture(renderer, "assets/QUITTER.png");

    menu->boutonHover[0] = IMG_LoadTexture(renderer, "assets/JOUER HOVER.png");
    menu->boutonHover[1] = IMG_LoadTexture(renderer, "assets/OPTION HOVER.png");
    menu->boutonHover[2] = IMG_LoadTexture(renderer, "assets/SCORE HOVER.png");
    menu->boutonHover[3] = IMG_LoadTexture(renderer, "assets/HISTOIRE HOVER.png");
    menu->boutonHover[4] = IMG_LoadTexture(renderer, "assets/QUITTER HOVER.png");

    SDL_Rect temp[5] = {
        {200,130,400,140},
        {200,210,400,140},
        {200,300,400,140},
        {200,390,400,140},
        {200,480,400,140}
    };

    for(int i=0;i<5;i++)
        menu->buttons[i] = temp[i];

    menu->selected = -1;
    menu->etat = MENU_PRINCIPAL;
}

int handleMenuEvent(Menu *menu, SDL_Event *event)
{

int i;
    // ----------- CLAVIER -----------
    if(event->type == SDL_KEYDOWN)
    {
        if(event->key.keysym.sym == SDLK_ESCAPE)
        {
            if(menu->etat == MENU_PRINCIPAL)
                exit(0);
            else
                menu->etat = MENU_PRINCIPAL;
        }

        if(event->key.keysym.sym == SDLK_j)
            menu->etat = MENU_SAUVEGARDE;
           
            

        if(event->key.keysym.sym == SDLK_o)
            menu->etat = MENU_OPTION;

        if(event->key.keysym.sym == SDLK_m)
            menu->etat = MENU_SCORE;
    }

    // ----------- SOURIS (AJOUT IMPORTANT) -----------
    if(event->type == SDL_MOUSEBUTTONDOWN)
    {
        int x = event->button.x;
        int y = event->button.y;


        for(i = 0; i < 5; i++)
        {
            if(x >= menu->buttons[i].x &&
               x <= menu->buttons[i].x + menu->buttons[i].w &&
               y >= menu->buttons[i].y &&
               y <= menu->buttons[i].y + menu->buttons[i].h)
            {
                printf("Bouton %d clique !\n", i);

                if(i == 0) menu->etat = MENU_SAUVEGARDE;
                if(i == 1) menu->etat = MENU_OPTION;
                if(i == 2) menu->etat = MENU_SCORE;
                if(i == 4) exit(0); // bouton quitter
            }
        }
    }
    return i;
}






void updateMenu(Menu *menu)
{
    int mx,my;
    SDL_GetMouseState(&mx,&my);
    SDL_Point mouse = {mx,my};

    int newSelected = -1;

    for(int i=0;i<5;i++)
        if(SDL_PointInRect(&mouse,&menu->buttons[i]))
            newSelected = i;

    if(newSelected != menu->selected && newSelected != -1)
        Mix_PlayChannel(-1, menu->hoverSound, 0);

    menu->selected = newSelected;
}

void renderMenu(Menu *menu, SDL_Renderer *renderer)
{
    if(menu->etat == MENU_PRINCIPAL)
    {
        SDL_RenderCopy(renderer, menu->background, NULL, NULL);

        SDL_RenderCopy(renderer, menu->shadow, NULL, &menu->shadowPos);
        SDL_RenderCopy(renderer, menu->title, NULL, &menu->titlePos);

        for(int i=0;i<5;i++)
        {
            if(i == menu->selected)
                SDL_RenderCopy(renderer, menu->boutonHover[i], NULL, &menu->buttons[i]);
            else
                SDL_RenderCopy(renderer, menu->boutonTexture[i], NULL, &menu->buttons[i]);
        }
    }
    else if(menu->etat == MENU_SAUVEGARDE)
    {
        SDL_SetRenderDrawColor(renderer, 0,100,0,255);
        SDL_RenderClear(renderer);
    }
    else if(menu->etat == MENU_OPTION)
    {
        SDL_SetRenderDrawColor(renderer, 100,0,100,255);
        SDL_RenderClear(renderer);
    }
    else if(menu->etat == MENU_SCORE)
    {
        SDL_SetRenderDrawColor(renderer, 0,0,120,255);
        SDL_RenderClear(renderer);
    }
}


void destroyMenu(Menu *menu)
{
    for(int i=0;i<5;i++)
    {
        SDL_DestroyTexture(menu->boutonTexture[i]);
        SDL_DestroyTexture(menu->boutonHover[i]);
    }

    SDL_DestroyTexture(menu->background);
    SDL_DestroyTexture(menu->title);
    SDL_DestroyTexture(menu->shadow);

    Mix_FreeChunk(menu->hoverSound);
    Mix_FreeMusic(menu->music);

    TTF_CloseFont(menu->font);
}

