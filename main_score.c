#include "header.h"
#include <stdio.h>
#include <string.h>

int main()
{
    App app;
    Textures tex = {0};
    Sounds snd = {0};
    Buttons bt;
    GameState gs = {0};

    gs.running = 1;
    gs.page = 1;
    strcpy(gs.joueurs[0],"Ghaya");
    strcpy(gs.joueurs[1],"Ali");
    strcpy(gs.joueurs[2],"Sara");
    gs.scores[0] = 300; gs.scores[1] = 200; gs.scores[2] = 100;

    // Initialize SDL
    if(initSDL(&app)) { printf("SDL init failed\n"); return 1; }

    // Load textures
    tex.background = IMG_LoadTexture(app.renderer, "assets/background3.jpg");
    tex.valider = IMG_LoadTexture(app.renderer, "assets/valider.png");
    tex.valider_hover = IMG_LoadTexture(app.renderer, "assets/valider_actif.png");
    tex.retour = IMG_LoadTexture(app.renderer, "assets/retour.png");
    tex.retour_hover = IMG_LoadTexture(app.renderer, "assets/retour_actif.png");
    tex.quitter = IMG_LoadTexture(app.renderer, "assets/quitter.png");
    tex.quitter_hover = IMG_LoadTexture(app.renderer, "assets/quitter_actif.png");

    // Load sounds
    snd.hoverSound = Mix_LoadWAV("assets/hover.wav");
    snd.victoryMusic = Mix_LoadMUS("assets/victory.wav");

    // Setup button rects
    bt.inputBox = (SDL_Rect){250,260,300,45};
    bt.rValider = (SDL_Rect){250,400,300,150};
    bt.rRetour = (SDL_Rect){50,420,250,120};
    bt.rQuitter = (SDL_Rect){500,420,250,120};

    SDL_Event e;
    int mx=0, my=0;

    SDL_StartTextInput();

    while(gs.running)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) gs.running = 0;

            // Text input
            if(e.type == SDL_TEXTINPUT && gs.page==1)
                strcat(gs.nom, e.text.text);

            // Keyboard input
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_BACKSPACE && strlen(gs.nom)>0)
                    gs.nom[strlen(gs.nom)-1] = 0;

                if(e.key.keysym.sym == SDLK_RETURN && gs.page==1)
                {
                    gs.page = 2;
                    Mix_PlayMusic(snd.victoryMusic, -1);
                }

                if(e.key.keysym.sym == SDLK_e && gs.page==2)
                {
                    gs.page = 4;
                    Mix_HaltMusic();  // stop music when leaving scores page
                }

                if(e.key.keysym.sym == SDLK_r && gs.page==4)
                {
                    gs.page = 2;
                    Mix_PlayMusic(snd.victoryMusic, -1); // restart music
                }

                if(e.key.keysym.sym == SDLK_ESCAPE)
                    gs.running = 0;
            }

            // Mouse clicks
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x=e.button.x, y=e.button.y;
                // valider
                if(gs.page==1 &&
                   x>bt.rValider.x && x<bt.rValider.x+bt.rValider.w &&
                   y>bt.rValider.y && y<bt.rValider.y+bt.rValider.h)
                {
                    gs.page = 2;
                    Mix_PlayMusic(snd.victoryMusic,-1);
                }
                // retour
                if(gs.page==2 &&
                   x>bt.rRetour.x && x<bt.rRetour.x+bt.rRetour.w &&
                   y>bt.rRetour.y && y<bt.rRetour.y+bt.rRetour.h)
                {
                    gs.page = 3;
                    Mix_HaltMusic();
                }
                // quitter
                if(x>bt.rQuitter.x && x<bt.rQuitter.x+bt.rQuitter.w &&
                   y>bt.rQuitter.y && y<bt.rQuitter.y+bt.rQuitter.h)
                    gs.running=0;
            }

            // Mouse motion / hover
            if(e.type == SDL_MOUSEMOTION)
            {
                mx=e.motion.x; my=e.motion.y;

                int hoverVal = mx>=bt.rValider.x && mx<=bt.rValider.x+bt.rValider.w &&
                               my>=bt.rValider.y && my<=bt.rValider.y+bt.rValider.h;
                int hoverRet = mx>=bt.rRetour.x && mx<=bt.rRetour.x+bt.rRetour.w &&
                               my>=bt.rRetour.y && my<=bt.rRetour.y+bt.rRetour.h;
                int hoverQuit = mx>=bt.rQuitter.x && mx<=bt.rQuitter.x+bt.rQuitter.w &&
                                my>=bt.rQuitter.y && my<=bt.rQuitter.y+bt.rQuitter.h;

                if((hoverVal || hoverRet || hoverQuit) && !gs.hoverPlayed && snd.hoverSound)
                    Mix_PlayChannel(-1, snd.hoverSound,0);

                gs.hoverPlayed = hoverVal || hoverRet || hoverQuit;
            }
        }

        // Render
        SDL_RenderClear(app.renderer);
        if(gs.page==1) renderPage1(&app, &tex, &gs, &bt, mx, my);
        else if(gs.page==2) renderPage2(&app, &tex, &gs, &bt, mx, my);
        else if(gs.page==3) renderPage3(&app, &gs);
        else if(gs.page==4) renderPage4(&app, &gs);
        SDL_RenderPresent(app.renderer);
    }

    SDL_StopTextInput();
    cleanup(&app, &tex, &snd);
    return 0;
}

