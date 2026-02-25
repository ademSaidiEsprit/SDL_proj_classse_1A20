#include "menu.h"
#include "button.h"
#include "config.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define spacing 200
void updateLayout(SDL_Renderer *renderer, Button *btnOui, Button *btnNon,Button *btnLoad,Button *btnNew , SDL_Rect *recTxt)
{
    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    int totalWidth = btnOui->rect.w + btnNon->rect.w + spacing;
    int startX = (winW - totalWidth) / 2;

    btnOui->rect.x = startX;
    btnNon->rect.x = startX + btnOui->rect.w + spacing;

    btnOui->rect.y = winH / 2;
    btnNon->rect.y = winH / 2;
    
	btnLoad->rect.x = winW / 2- btnLoad->rect.w /2;
	btnLoad->rect.y = winH / 2-300;
	
	btnNew->rect.x = winW / 2- btnNew->rect.w /2;
	btnNew->rect.y = winH / 2;
	
	recTxt->x=winW / 2 -recTxt->w/2;
	recTxt->y= winH / 2 - 150;


   
    
    
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
	
	SDL_Color white={255,255,255,255};
    TTF_Font *font = TTF_OpenFont("assets/Blue Winter.ttf", 40);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font,"Save your game?",white);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
	SDL_FreeSurface(textSurface);
    
    SDL_Rect recTxt;
	SDL_QueryTexture(textTexture, NULL, NULL, &recTxt.w, &recTxt.h);


	
	
	
	
	
    initButton(&btnOui, renderer, BTN_OUI_IMG, BTN_OUI_OVER, BTN_OUI_CLICK, 400, 400);
    
	
	
    initButton(&btnNon, renderer, BTN_NON_IMG, BTN_NON_OVER, BTN_NON_CLICK, 400, 400);
    
    
    

    initButton(&btnLoad, renderer, BTN_LOAD_IMG, BTN_LOAD_OVER, BTN_LOAD_CLICK, 500, 300);
    
    
    initButton(&btnNew, renderer, BTN_NEW_IMG, BTN_NEW_OVER, BTN_NEW_CLICK, 500, 450);
    
//

    updateLayout(renderer,&btnOui,&btnNon,&btnLoad,&btnNew,&recTxt);


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
            	updateLayout(renderer,&btnOui,&btnNon,&btnLoad,&btnNew,&recTxt);
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        

        if (!showSecondMenu) {
        	SDL_RenderCopy(renderer, textTexture, NULL, &recTxt);
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
