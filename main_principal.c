#include "menu_principal.h"
#include "headeres.h"

void menuPrincipale(SDL_Renderer *renderer,SDL_Window *window)
{
    
    
    Menu menu;
    initMenu(&menu, renderer);
    int running = 1;
    SDL_Event event;
    int currentMenu=0;
    while(running)
      {
         while(SDL_PollEvent(&event))
         {
             if(event. type == SDL_QUIT)
                running = 0;

             currentMenu=handleMenuEvent (&menu, &event) ;
             
			if(menu.etat==MENU_SCORE) running=0;
			if(menu.etat==MENU_SAUVEGARDE) running=0;
			if(menu.etat==MENU_OPTION) running=0;
             

		}
		
        updateMenu(&menu);
        SDL_RenderClear(renderer);
        renderMenu(&menu, renderer);
        SDL_RenderPresent(renderer);
        
		    
    }

    destroyMenu(&menu);


    if(menu.etat==MENU_SCORE){
    	ghaya(renderer,window);
    }
    if(menu.etat==MENU_SAUVEGARDE){
    	sauv(renderer,window);
    }
    if(menu.etat==MENU_OPTION){
    	option(renderer,window);
    }
}








