#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

// ================= STRUCTURES =================
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* fontPetit;
    TTF_Font* fontNormal;
    TTF_Font* fontTitre;
} App;

typedef struct {
    SDL_Texture* background;
    SDL_Texture* valider;
    SDL_Texture* valider_hover;
    SDL_Texture* retour;
    SDL_Texture* retour_hover;
    SDL_Texture* quitter;
    SDL_Texture* quitter_hover;
} Textures;

typedef struct {
    Mix_Chunk* hoverSound;
    Mix_Music* victoryMusic;
} Sounds;

typedef struct {
    SDL_Rect inputBox;
    SDL_Rect rValider;
    SDL_Rect rRetour;
    SDL_Rect rQuitter;
} Buttons;

typedef struct {
    int running;
    int page;
    char nom[50];
    char joueurs[3][50];
    int scores[3];
    int hoverPlayed;
} GameState;

// ================= SDL INIT / CLEANUP =================
int initSDL(App* app,SDL_Renderer *renderer,SDL_Window *window);
void cleanup(App* app, Textures* tex, Sounds* snd);

// ================= RENDER FUNCTIONS =================
void drawShadowText(SDL_Renderer* ren, TTF_Font* font,
                    const char* txt, int x, int y, SDL_Color color);

void renderPage1(App* app, Textures* tex, GameState* gs, Buttons* bt, int mx, int my);
void renderPage2(App* app, Textures* tex, GameState* gs, Buttons* bt, int mx, int my);
void renderPage3(App* app, GameState* gs);
void renderPage4(App* app, GameState* gs);

#endif

