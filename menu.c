#include "menu.h"
#include "button.h"
#include "config.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#define spacing 200
void updateLayout(SDL_Renderer *renderer, Button *btnOui, Button *btnNon)
{
    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    int totalWidth = btnOui->rect.w + btnNon->rect.w + spacing;
    int startX = (winW - totalWidth) / 2;

    btnOui->rect.x = startX;
    btnNon->rect.x = startX + btnOui->rect.w + spacing;

    btnOui->rect.y = winH / 2;
    btnNon->rect.y = winH / 2;
}


void runSaveMenu(SDL_Renderer *renderer)
{
    SDL_Texture *background = IMG_LoadTexture(renderer, BG_SAVE_PATH);
    int flags = MIX_INIT_MP3;
    if ((Mix_Init(flags) & flags) != flags) {
        printf("MP3 support not available: %s\n", Mix_GetError());
    }
    Mix_Chunk *hoverSound = Mix_LoadWAV(HOVER_SOUND);

    Button btnOui, btnNon, btnLoad, btnNew;
    int winW,winH;
    
	SDL_GetRendererOutputSize(renderer, &winW, &winH);

    

    initButton(&btnOui, renderer, BTN_OUI_IMG, BTN_OUI_OVER, BTN_OUI_CLICK, 400, 400);
    
	
	
    initButton(&btnNon, renderer, BTN_NON_IMG, BTN_NON_OVER, BTN_NON_CLICK, 400, 400);
    
    //
    updateLayout(renderer,&btnOui,&btnNon);
    

    initButton(&btnLoad, renderer, BTN_LOAD_IMG, BTN_LOAD_OVER, BTN_LOAD_CLICK, 500, 300);
    
    
    initButton(&btnNew, renderer, BTN_NEW_IMG, BTN_NEW_OVER, BTN_NEW_CLICK, 500, 450);
    
    int showteardMenu = 0;
    int showSecondMenu = 0;
    int running = 1;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT)
                running = 0;

            if (!showSecondMenu) {
                if (handleButtonEvent(&btnOui, &e, hoverSound))
                    showSecondMenu = 1;

                if (handleButtonEvent(&btnNon, &e, hoverSound))
                    running = 0;
            } else {
            
            	if (handleButtonEvent(&btnNew, &e, hoverSound)||
            	(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n)){
                    showteardMenu = 1;
                    printf("Sous menu joueur\n");
            	}

                if (handleButtonEvent(&btnLoad, &e, hoverSound))
                    printf("Charger jeu\n");


            }
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED){
            	updateLayout(renderer,&btnOui,&btnNon);
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        if (!showSecondMenu) {
            renderButton(&btnOui, renderer);
            renderButton(&btnNon, renderer);
        } else {
        	if(!showteardMenu){
		        renderButton(&btnLoad, renderer);
		        renderButton(&btnNew, renderer);
		    }
        }

        SDL_RenderPresent(renderer);
    }

    destroyButton(&btnOui);
    destroyButton(&btnNon);
    destroyButton(&btnLoad);
    destroyButton(&btnNew);

    SDL_DestroyTexture(background);
    Mix_FreeChunk(hoverSound);
}
