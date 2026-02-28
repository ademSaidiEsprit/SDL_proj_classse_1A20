#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "menu.h"

#define WIDTH 1000
#define HEIGHT 700


void drawButtonText(SDL_Renderer* renderer, Button* b, const char* text, TTF_Font* font)
{
    SDL_Color textColor = b->isHover ? (SDL_Color){0, 255, 255, 255} : (SDL_Color){57, 255, 20, 255};
    SDL_Surface* surf = TTF_RenderText_Blended(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_Rect dst = { 
        b->rect.x + (b->rect.w - surf->w)/2, 
        b->rect.y + (b->rect.h - surf->h)/2, 
        surf->w, surf->h 
    };
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Sous Menu Joueur",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    
    SDL_Texture* background_main = IMG_LoadTexture(renderer, "menu_principal.png");
    SDL_Texture* background2 = IMG_LoadTexture(renderer, "background.jpg");
    SDL_Texture* background_scores = IMG_LoadTexture(renderer, "meilleurs_scores.png");

   
    Mix_Music* music = Mix_LoadMUS("song.mp3");
    Mix_Chunk* hoverSound = Mix_LoadWAV("mouseclick.wav");
    Mix_PlayMusic(music, -1);

    
    TTF_Font* font = TTF_OpenFont("aa.TTF", 32); 

    
    Button mono    = {{150,250,400,140}, IMG_LoadTexture(renderer,"bouton.png"), IMG_LoadTexture(renderer,"hover.png"),0};
    Button multi   = {{600,250,400,140}, IMG_LoadTexture(renderer,"bouton.png"), IMG_LoadTexture(renderer,"hover.png"),0};
    Button retour  = {{50,580,400,140}, IMG_LoadTexture(renderer,"bouton.png"), IMG_LoadTexture(renderer,"hover.png"),0};
    Button valider = {{375,500,400,140}, IMG_LoadTexture(renderer,"bouton.png"), IMG_LoadTexture(renderer,"hover.png"),0};
    Button input1  = {{200,350,400,140}, IMG_LoadTexture(renderer,"bouton.png"), IMG_LoadTexture(renderer,"hover.png"),0};
    Button input2  = {{550,350,400,140}, IMG_LoadTexture(renderer,"bouton.png"), IMG_LoadTexture(renderer,"hover.png"),0};
    Button avatar1 = {{180,120,400,140}, IMG_LoadTexture(renderer,"avatar1.png"), IMG_LoadTexture(renderer,"avatar1_hover.png"),0};
    Button avatar2 = {{550,120,400,140}, IMG_LoadTexture(renderer,"avatar2.png"), IMG_LoadTexture(renderer,"avatar2_hover.png"),0};

    int running = 1;
    int current_menu = 1;   
    int showChoices = 0;
    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) running = 0;

            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE) running = 0;
                if(event.key.keysym.sym == SDLK_RETURN && showChoices && current_menu == 1)
                    current_menu = 2;
            }

            if(current_menu == 1)
            {
                if(event.type == SDL_MOUSEMOTION)
                {
                    int x = event.motion.x;
                    int y = event.motion.y;

                    updateHover(&mono,x,y,hoverSound);
                    updateHover(&multi,x,y,hoverSound);
                    updateHover(&retour,x,y,hoverSound);

                    if(showChoices)
                    {
                        updateHover(&avatar1,x,y,hoverSound);
                        updateHover(&avatar2,x,y,hoverSound);
                        updateHover(&input1,x,y,hoverSound);
                        updateHover(&input2,x,y,hoverSound);
                        updateHover(&valider,x,y,hoverSound);
                    }
                }

                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    if(pointInRect(x,y,mono.rect) || pointInRect(x,y,multi.rect))
                        showChoices = 1;

                    if(pointInRect(x,y,retour.rect))
                    {
                        current_menu = 0;
                        showChoices = 0;
                    }

                    if(showChoices && pointInRect(x,y,valider.rect))
                        current_menu = 2;
                }
            }
        }

        SDL_RenderClear(renderer);

        if(current_menu == 0)
            SDL_RenderCopy(renderer, background_main, NULL, NULL);
        else if(current_menu == 1)
        {
            SDL_RenderCopy(renderer, background2, NULL, NULL);

            
            renderButton(renderer, &mono);
            drawButtonText(renderer, &mono, "Mono Joueur", font);

            renderButton(renderer, &multi);
            drawButtonText(renderer, &multi, "Multi Joueur", font);

            renderButton(renderer, &retour);
            drawButtonText(renderer, &retour, "Quitter", font);

            if(showChoices) {
                renderButton(renderer, &avatar1);
                

                renderButton(renderer, &avatar2);
                

                renderButton(renderer, &input1);
                drawButtonText(renderer, &input1, "Input 1", font);

                renderButton(renderer, &input2);
                drawButtonText(renderer, &input2, "Input 2", font);

                renderButton(renderer, &valider);
                drawButtonText(renderer, &valider, "Valider", font);
            }
        }
        else if(current_menu == 2)
            SDL_RenderCopy(renderer, background_scores, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    
    SDL_DestroyTexture(background_main);
    SDL_DestroyTexture(background2);
    SDL_DestroyTexture(background_scores);

    SDL_DestroyTexture(mono.normal); SDL_DestroyTexture(mono.hover);
    SDL_DestroyTexture(multi.normal); SDL_DestroyTexture(multi.hover);
    SDL_DestroyTexture(retour.normal); SDL_DestroyTexture(retour.hover);
    SDL_DestroyTexture(valider.normal); SDL_DestroyTexture(valider.hover);
    SDL_DestroyTexture(input1.normal); SDL_DestroyTexture(input1.hover);
    SDL_DestroyTexture(input2.normal); SDL_DestroyTexture(input2.hover);
    SDL_DestroyTexture(avatar1.normal); SDL_DestroyTexture(avatar1.hover);
    SDL_DestroyTexture(avatar2.normal); SDL_DestroyTexture(avatar2.hover);

    Mix_FreeChunk(hoverSound);
    Mix_FreeMusic(music);
    Mix_CloseAudio();

    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
