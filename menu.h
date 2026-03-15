#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Structure pour les boutons
typedef struct
{
    SDL_Rect rect;       // Position et taille
    SDL_Texture* normal; // Texture normale
    SDL_Texture* hover;  // Texture survolée
    int isHover;         // 0 = normal, 1 = hover
} Button;

// Fonctions utiles
int pointInRect(int x, int y, SDL_Rect r);
void renderButton(SDL_Renderer* renderer, Button* b);
void updateHover(Button* b, int x, int y, Mix_Chunk* sound);

#endif
