#include "header.h"

// ================= TEXT WITH SHADOW =================
void drawShadowText(SDL_Renderer* ren, TTF_Font* font,
                    const char* txt, int x, int y, SDL_Color color)
{
    SDL_Color black = {0,0,0,255};

    SDL_Surface* s1 = TTF_RenderText_Blended(font, txt, black);
    SDL_Texture* shadow = SDL_CreateTextureFromSurface(ren, s1);
    SDL_FreeSurface(s1);

    SDL_Surface* s2 = TTF_RenderText_Blended(font, txt, color);
    SDL_Texture* text = SDL_CreateTextureFromSurface(ren, s2);
    SDL_FreeSurface(s2);

    int w,h;
    SDL_QueryTexture(text,NULL,NULL,&w,&h);

    SDL_Rect sh = {x+2, y+2, w, h};
    SDL_Rect pos = {x, y, w, h};

    SDL_RenderCopy(ren, shadow, NULL, &sh);
    SDL_RenderCopy(ren, text, NULL, &pos);

    SDL_DestroyTexture(shadow);
    SDL_DestroyTexture(text);
}

// ================= INIT / CLEANUP =================
int initSDL(App* app,SDL_Renderer *renderer,SDL_Window *window) {
    
    app->window = window;
    if(!app->window) return 1;
    app->renderer = renderer;
    if(!app->renderer) return 1;
    app->fontPetit = TTF_OpenFont("aa.TTF", 20);
    app->fontNormal = TTF_OpenFont("aa.TTF", 30);
    app->fontTitre = TTF_OpenFont("aa.TTF", 50);
    return 0;
}

void cleanup(App* app, Textures* tex, Sounds* snd) {
    if(tex->background) SDL_DestroyTexture(tex->background);
    if(tex->valider) SDL_DestroyTexture(tex->valider);
    if(tex->valider_hover) SDL_DestroyTexture(tex->valider_hover);
    if(tex->retour) SDL_DestroyTexture(tex->retour);
    if(tex->retour_hover) SDL_DestroyTexture(tex->retour_hover);
    if(tex->quitter) SDL_DestroyTexture(tex->quitter);
    if(tex->quitter_hover) SDL_DestroyTexture(tex->quitter_hover);
    if(snd->hoverSound) Mix_FreeChunk(snd->hoverSound);
    if(snd->victoryMusic) Mix_FreeMusic(snd->victoryMusic);
    if(app->fontPetit) TTF_CloseFont(app->fontPetit);
    if(app->fontNormal) TTF_CloseFont(app->fontNormal);
    if(app->fontTitre) TTF_CloseFont(app->fontTitre);
}

// ================= PAGE 1 =================
void renderPage1(App *app, Textures *tex, GameState *gs, Buttons *bt, int mx, int my)
{
    SDL_RenderCopy(app->renderer, tex->background, NULL, NULL);

    SDL_Color white = {255,255,255,255};
    drawShadowText(app->renderer, app->fontPetit, "SAISIR NOM/PSEUDO :", 250, 210, white);

    SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(app->renderer,0,0,0,140);
    SDL_RenderFillRect(app->renderer, &bt->inputBox);
    SDL_SetRenderDrawColor(app->renderer,255,255,255,255);
    SDL_RenderDrawRect(app->renderer, &bt->inputBox);

    if(strlen(gs->nom) > 0)
        drawShadowText(app->renderer, app->fontNormal, gs->nom, bt->inputBox.x+20, bt->inputBox.y+8, white);

    SDL_Rect btn = bt->rValider;
    SDL_Texture *tValider = tex->valider;
    if(mx >= bt->rValider.x && mx <= bt->rValider.x + bt->rValider.w &&
       my >= bt->rValider.y && my <= bt->rValider.y + bt->rValider.h)
    {
        tValider = tex->valider_hover;
        btn.x -= 5; btn.y -= 5; btn.w += 10; btn.h += 10;
    }

    SDL_RenderCopy(app->renderer, tValider, NULL, &btn);
}

// ================= PAGE 2 =================
void renderPage2(App *app, Textures *tex, GameState *gs, Buttons *bt, int mx, int my)
{
    SDL_RenderCopy(app->renderer, tex->background, NULL, NULL);

    SDL_Color white = {255,255,255,255};
    drawShadowText(app->renderer, app->fontTitre, "MEILLEURS SCORES", 100, 60, white);

    SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(app->renderer,0,0,0,150);
    SDL_Rect box={150,130,500,220};
    SDL_RenderFillRect(app->renderer,&box);

    char ligne[100];
    for(int i=0;i<3;i++)
    {
        sprintf(ligne,"%d. %s - %d pts",i+1,gs->joueurs[i],gs->scores[i]);
        drawShadowText(app->renderer, app->fontNormal, ligne, 250, 160+i*60, white);
    }

    // Buttons
    SDL_Rect bRetour = bt->rRetour;
    SDL_Rect bQuit = bt->rQuitter;
    SDL_Texture *tRetour = tex->retour;
    SDL_Texture *tQuit = tex->quitter;

    if(mx >= bt->rRetour.x && mx <= bt->rRetour.x + bt->rRetour.w &&
       my >= bt->rRetour.y && my <= bt->rRetour.y + bt->rRetour.h)
    {
        tRetour = tex->retour_hover; bRetour.x -= 5; bRetour.y -= 5; bRetour.w += 10; bRetour.h += 10;
    }
    if(mx >= bt->rQuitter.x && mx <= bt->rQuitter.x + bt->rQuitter.w &&
       my >= bt->rQuitter.y && my <= bt->rQuitter.y + bt->rQuitter.h)
    {
        tQuit = tex->quitter_hover; bQuit.x -= 5; bQuit.y -= 5; bQuit.w += 10; bQuit.h += 10;
    }

    SDL_RenderCopy(app->renderer, tRetour, NULL, &bRetour);
    SDL_RenderCopy(app->renderer, tQuit, NULL, &bQuit);
}

// ================= PAGE 3 =================
void renderPage3(App *app, GameState *gs)
{
    SDL_SetRenderDrawColor(app->renderer,30,30,60,255);
    SDL_RenderClear(app->renderer);

    SDL_Color white = {255,255,255,255};
    drawShadowText(app->renderer, app->fontTitre, "MENU PRINCIPAL", 220, 200, white);
    drawShadowText(app->renderer, app->fontNormal, "Appuie sur ESC pour quitter", 200, 300, white);
}

// ================= PAGE 4 =================
void renderPage4(App *app, GameState *gs)
{
    SDL_SetRenderDrawColor(app->renderer,10,40,40,255);
    SDL_RenderClear(app->renderer);

   // SDL_Color white = {255,255,255,255};
   // drawShadowText(app->renderer, app->fontTitre, "PAGE E ACTIVE", 250, 200, white);
   // drawShadowText(app->renderer, app->fontNormal, "Appuie sur R pour revenir", 220, 300, white);
}

