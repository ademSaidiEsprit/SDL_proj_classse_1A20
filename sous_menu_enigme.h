#ifndef ENIGME_H
#define ENIGME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

typedef struct {
    SDL_Texture *image;
    SDL_Rect position;
} Image;
typedef struct {
    SDL_Texture *texture;
    SDL_Rect position;
    TTF_Font *font;
    SDL_Color color;
    char *text;
} text;

typedef struct {
    SDL_Texture *normal;
    SDL_Texture *hover;
    SDL_Rect position;
    int isHovered;
} Bouton;

typedef struct {

    Image background[3];

    Bouton btnQuiz;
    Bouton btnPuzzle;
    Image quizquestion;      
    text  quizquestionTxt;   

    int quizActive;
    int puzzleActive;
    Bouton btnRep1;
        text  btnRep1Txt;
    Bouton btnRep2;
        text  btnRep2Txt;
    Bouton btnRep3;
        text  btnRep3Txt;

    Mix_Chunk *hoverSound;
    Mix_Chunk *quizMusic;   

} EnigmeMenu;

/* Fonctions */
void initEnigme(EnigmeMenu *e, SDL_Renderer *renderer);
void handleInputEnigme(EnigmeMenu *e, SDL_Event event, int *running);
void updateEnigme(EnigmeMenu *e, int mouseX, int mouseY);
void renderEnigme(EnigmeMenu *e, SDL_Renderer *renderer);
void freeEnigme(EnigmeMenu *e);

#endif

