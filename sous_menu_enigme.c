#include "sous_menu_enigme.h"
#include <stdio.h>

/* Charger texture */
SDL_Texture* loadTexture(char *path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("Erreur image %s : %s\n", path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur create texture %s : %s\n", path, SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return texture;
}

/* INITIALISATION */
void initEnigme(EnigmeMenu *e, SDL_Renderer *renderer)
{
    
    e->background[0].image = loadTexture("assets/background1.png", renderer);
    e->background[1].image = loadTexture("assets/background2.png", renderer);
    e->background[2].image = loadTexture("assets/background3.png", renderer);
    e->background[0].position = (SDL_Rect){0,0,1024,1024};
    e->background[1].position = (SDL_Rect){0,0,1024,1024};
    e->background[2].position = (SDL_Rect){0,0,1024,1024};


    e->quizquestion.image = loadTexture("assets/button_mtaa3_quiz.png", renderer);
    e->quizquestion.position = (SDL_Rect){212,400,600,100};

    e->quizquestionTxt.text = "Quiz question";
    e->quizquestionTxt.font = TTF_OpenFont("assets/aa.ttf", 24);
    
    e->quizquestionTxt.color = (SDL_Color){0,0,0,0};
    e->quizquestionTxt.position = e->quizquestion.position;

    /* Bouton Quiz */
    e->btnQuiz.normal = loadTexture("assets/quiz.png", renderer);
    e->btnQuiz.hover  = loadTexture("assets/quiz_hover.png", renderer);
    e->btnQuiz.position = (SDL_Rect){412,200,200,60};
    e->btnQuiz.isHovered = 0;

    /* Bouton Puzzle */
    e->btnPuzzle.normal = loadTexture("assets/puzzle.png", renderer);
    e->btnPuzzle.hover  = loadTexture("assets/puzzle_hover.png", renderer);
    e->btnPuzzle.position = (SDL_Rect){412,300,200,60};
    e->btnPuzzle.isHovered = 0;

    /* Boutons réponses */
    e->btnRep1.normal = loadTexture("assets/button_mtaa3_quiz.png", renderer);
    e->btnRep1.hover  = loadTexture("assets/button_mtaa_quiz_hovered.png", renderer);
    e->btnRep1.position = (SDL_Rect){70,600,200,50};
    e->btnRep1Txt.text = "Reponse 1";
    e->btnRep1Txt.font = e->quizquestionTxt.font;
    e->btnRep1Txt.color = (SDL_Color){0,0,0,0};
    e->btnRep1Txt.position = e->btnRep1.position;

    e->btnRep2.normal = loadTexture("assets/button_mtaa3_quiz.png", renderer);
    e->btnRep2.hover  = loadTexture("assets/button_mtaa_quiz_hovered.png", renderer);
    e->btnRep2.position = (SDL_Rect){411,600,200,50};
    e->btnRep2Txt.text = "Reponse 2";
    e->btnRep2Txt.font = e->quizquestionTxt.font;
    e->btnRep2Txt.color = (SDL_Color){0,0,0,0};
    e->btnRep2Txt.position = e->btnRep2.position;

    e->btnRep3.normal = loadTexture("assets/button_mtaa3_quiz.png", renderer);
    e->btnRep3.hover  = loadTexture("assets/button_mtaa_quiz_hovered.png", renderer);
    e->btnRep3.position = (SDL_Rect){751,600,200,50};
    e->btnRep3Txt.text = "Reponse 3";
    e->btnRep3Txt.font = TTF_OpenFont("assets/aa.ttf", 20);
    e->btnRep3Txt.color = (SDL_Color){0,0,0,0};
    e->btnRep3Txt.position = e->btnRep3.position;



    /* Sons */
    e->hoverSound = Mix_LoadWAV("assets/suspense.wav");
    e->quizMusic  = Mix_LoadWAV("assets/hover.wav");  /* keep as chunk */

    e->quizActive = 0;
}

/* INPUT */
void handleInputEnigme(EnigmeMenu *e, SDL_Event event, int *running)
{
    int a[4] = {0,0,0,0};
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            *running = 0;
        if (event.key.keysym.sym == SDLK_BACKSPACE)
            e->quizActive = 0;
            e->puzzleActive = 0;
        if (e->quizActive==1)
        {
            if (event.key.keysym.sym == SDLK_UP)
                a[0] = 1;
            if (event.key.keysym.sym == SDLK_DOWN)
                a[1] = 1;
            if (event.key.keysym.sym == SDLK_RIGHT)
                a[2] = 1;
            if (event.key.keysym.sym == SDLK_LEFT)
                a[3] = 1;

        }

    }
    if(event.type == SDL_KEYUP)
    {
        if (e->quizActive==1)
        {
            if (event.key.keysym.sym == SDLK_UP)
               {
               
                if(e->btnRep1.isHovered && a[0] == 1)
                {
                    e->btnRep1.isHovered = 0;
                    e->btnRep3.isHovered = 1;
                    a[0] = 0;
                }
                else if(e->btnRep2.isHovered && a[0] == 1)
                {
                    e->btnRep2.isHovered = 0;
                    e->btnRep1.isHovered = 1;
                    a[0] = 0;
                }
                else if(e->btnRep3.isHovered && a[0] == 1)
                    {
                    e->btnRep3.isHovered = 0;
                    e->btnRep2.isHovered = 1;
                    a[0] = 0;
                    }
                else 
                {
                    e->btnRep1.isHovered = 1;
                    a[0] = 0;
                }
                } 
            if (event.key.keysym.sym == SDLK_DOWN)
                a[1] = 0;
            if (event.key.keysym.sym == SDLK_RIGHT)
                a[2] = 0;
            if (event.key.keysym.sym == SDLK_LEFT)
                a[3] = 0;

        }

    }

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = event.button.x;
        int y = event.button.y;

        SDL_Rect r = e->btnQuiz.position;
        SDL_Rect r2 = e->btnPuzzle.position;

        if (!e->quizActive &&
            x >= r.x && x <= r.x+r.w &&
            y >= r.y && y <= r.y+r.h)
        {
            e->quizActive = 1;
            Mix_PlayChannel(-1, e->quizMusic, 0);
        }
        if (!e->puzzleActive &&
            x >= r2.x && x <= r2.x+r2.w &&
            y >= r2.y && y <= r2.y+r2.h)
        {
            e->puzzleActive = 1;
            Mix_PlayChannel(-1, e->quizMusic, 0);
        }
        

    }

}

/* UPDATE */
void updateEnigme(EnigmeMenu *e, int mouseX, int mouseY)
{
    Bouton *buttons[] = {
        &e->btnQuiz,
        &e->btnPuzzle,
        &e->btnRep1,
        &e->btnRep2,
        &e->btnRep3
    };
    int s=0;
    if(e->quizActive == 1)
    {
        s=2;
        buttons[0]->isHovered = 0;
        buttons[1]->isHovered = 0;
    }


    for (int i=s;i<5;i++)
    {
        SDL_Rect r = buttons[i]->position;

        int hovered = 0;
        
        if (mouseX >= r.x && mouseX <= r.x+r.w && mouseY >= r.y && mouseY <= r.y+r.h)
        {
            hovered = 1;
        } 

        if (hovered == 1 && !buttons[i]->isHovered)
        {
            Mix_PlayChannel(-1, e->hoverSound, 0);
            buttons[i]->isHovered = 1;
        }
        else if (!hovered && buttons[i]->isHovered)
        {
            buttons[i]->isHovered = 0;
        }
        
    }
}

/* AFFICHAGE */
void renderEnigme(EnigmeMenu *e, SDL_Renderer *renderer)
{
    SDL_Texture *current;
    if(e->quizActive == 0)
    {
            SDL_RenderCopy(renderer, e->background[0].image, NULL, &e->background[0].position);

        
        if (e->btnQuiz.isHovered == 1)
            current = e->btnQuiz.hover;
        else 
            current = e->btnQuiz.normal;

        SDL_RenderCopy(renderer, current, NULL, &e->btnQuiz.position);
        
        if(e->btnPuzzle.isHovered == 1)
        {
            current = e->btnPuzzle.hover;
        }
        else
            current = e->btnPuzzle.normal;
        SDL_RenderCopy(renderer, current, NULL, &e->btnPuzzle.position);
    }
    
    if (e->quizActive == 1)
    {

        SDL_RenderCopy(renderer, e->background[1].image, NULL, &e->background[1].position);
        SDL_RenderCopy(renderer, e->quizquestion.image, NULL, &e->quizquestion.position);

        
        SDL_Surface *textSurface = TTF_RenderText_Solid(e->quizquestionTxt.font,e->quizquestionTxt.text,e->quizquestionTxt.color);    
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);         
        SDL_Rect dest = e->quizquestionTxt.position;
        dest.w = textSurface->w;
        dest.h = textSurface->h;
        dest.x += (e->quizquestion.position.w - dest.w) / 2;
        dest.y += (e->quizquestion.position.h - dest.h) / 2;
        SDL_RenderCopy(renderer, textTexture, NULL, &dest);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);


            
        

        /* first answer button and its label */
        if (e->btnRep1.isHovered == 1)
            current = e->btnRep1.hover;
        else
            current = e->btnRep1.normal;
        SDL_RenderCopy(renderer, current, NULL, &e->btnRep1.position);
        if (e->btnRep1Txt.font) {
            SDL_Surface *textSurface1 = TTF_RenderText_Solid(e->btnRep1Txt.font,
                                                            e->btnRep1Txt.text,
                                                            e->btnRep1Txt.color);
            if (textSurface1) {
                SDL_Texture *textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
                if (textTexture1) {
                    SDL_Rect dest1 = e->btnRep1Txt.position;
                    dest1.w = textSurface1->w;
                    dest1.h = textSurface1->h;
                    dest1.x += (e->btnRep1.position.w - dest1.w) / 2;
                    dest1.y += (e->btnRep1.position.h - dest1.h) / 2;
                    SDL_RenderCopy(renderer, textTexture1, NULL, &dest1);
                    SDL_DestroyTexture(textTexture1);
                }
                SDL_FreeSurface(textSurface1);
            }
        }

        /* second answer button */
        if (e->btnRep2.isHovered == 1)
            current = e->btnRep2.hover;
        else
            current = e->btnRep2.normal;
        SDL_RenderCopy(renderer, current, NULL, &e->btnRep2.position);
        if (e->btnRep2Txt.font) {
            SDL_Surface *textSurface2 = TTF_RenderText_Solid(e->btnRep2Txt.font,
                                                            e->btnRep2Txt.text,
                                                            e->btnRep2Txt.color);
            if (textSurface2) {
                SDL_Texture *textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
                if (textTexture2) {
                    SDL_Rect dest2 = e->btnRep2Txt.position;
                    dest2.w = textSurface2->w;
                    dest2.h = textSurface2->h;
                    dest2.x += (e->btnRep2.position.w - dest2.w) / 2;
                    dest2.y += (e->btnRep2.position.h - dest2.h) / 2;
                    SDL_RenderCopy(renderer, textTexture2, NULL, &dest2);
                    SDL_DestroyTexture(textTexture2);
                }
                SDL_FreeSurface(textSurface2);
            }
        }

        /* third answer button */
        if (e->btnRep3.isHovered == 1)
            current = e->btnRep3.hover;
        else
            current = e->btnRep3.normal;
        SDL_RenderCopy(renderer, current, NULL, &e->btnRep3.position);
        if (e->btnRep3Txt.font) {
            SDL_Surface *textSurface3 = TTF_RenderText_Solid(e->btnRep3Txt.font,
                                                            e->btnRep3Txt.text,
                                                            e->btnRep3Txt.color);
            if (textSurface3) {
                SDL_Texture *textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
                if (textTexture3) {
                    SDL_Rect dest3 = e->btnRep3Txt.position;
                    dest3.w = textSurface3->w;
                    dest3.h = textSurface3->h;
                    dest3.x += (e->btnRep3.position.w - dest3.w) / 2;
                    dest3.y += (e->btnRep3.position.h - dest3.h) / 2;
                    SDL_RenderCopy(renderer, textTexture3, NULL, &dest3);
                    SDL_DestroyTexture(textTexture3);
                }
                SDL_FreeSurface(textSurface3);
            }
        }
    }
    if (e->puzzleActive == 1)
    {
        SDL_RenderCopy(renderer, e->background[2].image, NULL, &e->background[2].position);
    }
}

/* LIBERATION */
void freeEnigme(EnigmeMenu *e)
{
    SDL_DestroyTexture(e->background[0].image);
    SDL_DestroyTexture(e->background[1].image);
    SDL_DestroyTexture(e->background[2].image);
    SDL_DestroyTexture(e->quizquestion.image);
    if (e->quizquestionTxt.font) {
        TTF_CloseFont(e->quizquestionTxt.font);
    }
    

    Bouton *buttons[] = {
        &e->btnQuiz,
        &e->btnPuzzle,
        &e->btnRep1,
        &e->btnRep2,
        &e->btnRep3
    };

    for (int i=0;i<5;i++)
    {
        SDL_DestroyTexture(buttons[i]->normal);
        SDL_DestroyTexture(buttons[i]->hover);
    }

    Mix_FreeChunk(e->hoverSound);
    Mix_FreeChunk(e->quizMusic);}
