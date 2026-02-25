#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "menu.h"
#include "config.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *bgMusic = Mix_LoadMUS(BG_MUSIC);
	if (!bgMusic) {
		printf("Erreur chargement musique: %s\n", Mix_GetError());
	}

	Mix_PlayMusic(bgMusic, -1);  // -1 = boucle infinie

    SDL_Window *window = SDL_CreateWindow("Save Menu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    runSaveMenu(renderer);
    
    
    Mix_FreeMusic(bgMusic);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
