#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "sauv_menu.h"
#include "config.h"
#include "headeres.h"
void sauv(SDL_Renderer *renderer,SDL_Window *window)
{
    Mix_Music *bgMusic = Mix_LoadMUS(BG_MUSIC);
	if (!bgMusic) {
		printf("Erreur chargement musique: %s\n", Mix_GetError());
	}

	Mix_PlayMusic(bgMusic, -1);  // -1 = boucle infinie

   
    int x=runSaveMenu(renderer);
    
    Mix_FreeMusic(bgMusic);

    
    if(x==1){
    	jeux(renderer,window);
    }


}
