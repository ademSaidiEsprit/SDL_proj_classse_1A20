#include "sauv_menu.h"
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





