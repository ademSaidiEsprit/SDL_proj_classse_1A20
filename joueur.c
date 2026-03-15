#include "headeres.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include <stdio.h>

#define WIDTH 1000
#define HEIGHT 700

// Affiche le texte centré sur un bouton
void drawButtonText(SDL_Renderer* renderer, Button* b, const char* text, TTF_Font* font)
{
    SDL_Color color = b->isHover ? (SDL_Color){0,255,255,255} : (SDL_Color){57,255,20,255};
    SDL_Surface* surf = TTF_RenderText_Blended(font, text, color);
    if(!surf) { printf("Erreur surface texte: %s\n", TTF_GetError()); return; }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    if(!texture) { printf("Erreur texture texte\n"); SDL_FreeSurface(surf); return; }

    SDL_Rect dst = {b->rect.x + (b->rect.w - surf->w)/2, b->rect.y + (b->rect.h - surf->h)/2, surf->w, surf->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}




void jeux(SDL_Renderer *renderer,SDL_Window *window)
{
	int current_menu = 1;
    
    // Textures de fond
    SDL_Texture* bg_main   = IMG_LoadTexture(renderer, "assets/background.jpg");
    SDL_Texture* bg_select = IMG_LoadTexture(renderer, "assets/background.jpg");
    SDL_Texture* bg_scores = IMG_LoadTexture(renderer, "assets/background.jpg");
    SDL_Texture* bg_empty  = IMG_LoadTexture(renderer, "assets/background.jpg");

    // Sons
    Mix_Music* music      = Mix_LoadMUS("assets/song.mp3");
    Mix_Chunk* hoverSound = Mix_LoadWAV("assets/mouseclick.wav");
    Mix_PlayMusic(music, -1);

    TTF_Font* font = TTF_OpenFont("assets/aa.TTF", 32);

    // Menu principal
    Button mono  = {{150,250,400,140}, IMG_LoadTexture(renderer,"assets/bouton.png"), IMG_LoadTexture(renderer,"assets/hover.png"),0};
    Button multi = {{600,250,400,140}, IMG_LoadTexture(renderer,"assets/bouton.png"), IMG_LoadTexture(renderer,"assets/hover.png"),0};
    Button retourPrincipal = {{WIDTH - 350, 580, 300, 100}, IMG_LoadTexture(renderer,"assets/bouton.png"), IMG_LoadTexture(renderer,"assets/hover.png"),0};

    // Menu sélection
    Button retour  = {{WIDTH - 450, 580, 400, 140}, IMG_LoadTexture(renderer,"assets/bouton.png"), IMG_LoadTexture(renderer,"assets/hover.png"),0};
    Button valider = {{375,500,400,140}, IMG_LoadTexture(renderer,"assets/bouton.png"), IMG_LoadTexture(renderer,"assets/hover.png"),0};
    Button avatar1 = {{180,120,400,140}, IMG_LoadTexture(renderer,"assets/avatar1.png"), IMG_LoadTexture(renderer,"assets/avatar1_hover.png"),0};
    Button avatar2 = {{550,120,400,140}, IMG_LoadTexture(renderer,"assets/avatar2.png"), IMG_LoadTexture(renderer,"assets/avatar2_hover.png"),0};
    Button input1  = {{180,280,400,140}, IMG_LoadTexture(renderer,"assets/bouton.png"), IMG_LoadTexture(renderer,"assets/hover.png"),0};
    Button input2  = {{550,280,400,140}, IMG_LoadTexture(renderer,"assets/bouton.png"), IMG_LoadTexture(renderer,"assets/hover.png"),0};

    int running = 1, selectedMode = 0, avatarSelected = 0, inputSelected = 0;
    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) running = 0;
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE) running = 0;
                if(event.key.keysym.sym == SDLK_RETURN && current_menu == 2 && avatarSelected && inputSelected)
                    current_menu = 3;
            }

            if(event.type == SDL_MOUSEMOTION)
            {
                int x = event.motion.x, y = event.motion.y;
                if(current_menu == 1){
                    updateHover(&mono,x,y,hoverSound);
                    updateHover(&multi,x,y,hoverSound);
                    updateHover(&retourPrincipal,x,y,hoverSound);
                } else if(current_menu == 2){
                    updateHover(&retour,x,y,hoverSound);
                    updateHover(&valider,x,y,hoverSound);
                    updateHover(&avatar1,x,y,hoverSound);
                    updateHover(&avatar2,x,y,hoverSound);
                    updateHover(&input1,x,y,hoverSound);
                    updateHover(&input2,x,y,hoverSound);
                }
            }

            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x, y = event.button.y;
                if(current_menu == 1){
                    if(pointInRect(x,y,mono.rect)){ current_menu=2; selectedMode=1; avatarSelected=0; inputSelected=0; }
                    if(pointInRect(x,y,multi.rect)){ current_menu=2; selectedMode=2; avatarSelected=0; inputSelected=0; }
                    if(pointInRect(x,y,retourPrincipal.rect)) current_menu = 0;
                } else if(current_menu == 2){
                    if(pointInRect(x,y,retour.rect)){ current_menu=1; avatarSelected=0; inputSelected=0; }
                    if(pointInRect(x,y,avatar1.rect)) avatarSelected=1;
                    if(pointInRect(x,y,avatar2.rect)) avatarSelected=1;
                    if(pointInRect(x,y,input1.rect)) inputSelected=1;
                    if(pointInRect(x,y,input2.rect)) inputSelected=1;
                    if(pointInRect(x,y,valider.rect)){
                        if(avatarSelected && inputSelected) current_menu=3;
                        else Mix_PlayChannel(-1, hoverSound, 0);
                    }
                }
            }
        }

        SDL_RenderClear(renderer);

        if(current_menu==1){
            SDL_RenderCopy(renderer,bg_main,NULL,NULL);
            renderButton(renderer,&mono); drawButtonText(renderer,&mono,"Mono Joueur",font);
            renderButton(renderer,&multi); drawButtonText(renderer,&multi,"Multi Joueur",font);
            renderButton(renderer,&retourPrincipal); drawButtonText(renderer,&retourPrincipal,"Retour",font);
        }
        else if(current_menu==2){
            SDL_RenderCopy(renderer,bg_select,NULL,NULL);
            renderButton(renderer,&retour); drawButtonText(renderer,&retour,"Retour",font);
            renderButton(renderer,&valider); drawButtonText(renderer,&valider,"Valider",font);
            renderButton(renderer,&avatar1);
            renderButton(renderer,&avatar2);
            renderButton(renderer,&input1); drawButtonText(renderer,&input1,"Input 1",font);
            renderButton(renderer,&input2); drawButtonText(renderer,&input2,"Input 2",font);
        }
        else if(current_menu==3){
            //SDL_RenderCopy(renderer,bg_scores,NULL,NULL);
            //thezek meilleur score
            running=0;
        }
        else if(current_menu==0){
            //SDL_RenderCopy(renderer,bg_empty,NULL,NULL);
            //menu principale
            running=0;
        }

        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    SDL_DestroyTexture(bg_main); SDL_DestroyTexture(bg_select); SDL_DestroyTexture(bg_scores); SDL_DestroyTexture(bg_empty);
    SDL_DestroyTexture(mono.normal); SDL_DestroyTexture(mono.hover);
    SDL_DestroyTexture(multi.normal); SDL_DestroyTexture(multi.hover);
    SDL_DestroyTexture(retour.normal); SDL_DestroyTexture(retour.hover);
    SDL_DestroyTexture(valider.normal); SDL_DestroyTexture(valider.hover);
    SDL_DestroyTexture(input1.normal); SDL_DestroyTexture(input1.hover);
    SDL_DestroyTexture(input2.normal); SDL_DestroyTexture(input2.hover);
    SDL_DestroyTexture(avatar1.normal); SDL_DestroyTexture(avatar1.hover);
    SDL_DestroyTexture(avatar2.normal); SDL_DestroyTexture(avatar2.hover);
    SDL_DestroyTexture(retourPrincipal.normal); SDL_DestroyTexture(retourPrincipal.hover);

    Mix_FreeChunk(hoverSound); Mix_FreeMusic(music); 
    TTF_CloseFont(font); 
    
	if(current_menu==3) ghaya(renderer,window);//system("./game");
	if(current_menu==0) menuPrincipale(renderer,window);//system("./app");
	

}
