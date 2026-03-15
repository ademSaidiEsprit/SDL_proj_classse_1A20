#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "sous_menu_enigme.h"
#include "headeres.h"

void enigme(SDL_Renderer *renderer)
{
    
    EnigmeMenu e;
    initEnigme(&e, renderer);

    int running = 1;
    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = 0;

            handleInputEnigme(&e, event, &running);
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        updateEnigme(&e, mouseX, mouseY);

        SDL_RenderClear(renderer);
        renderEnigme(&e, renderer);
        SDL_RenderPresent(renderer);
    }

    freeEnigme(&e);

    

}
