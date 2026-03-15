#include "menu_option.h"
#include <stdio.h>
SDL_Texture* chargerTexture(const char *chemin, SDL_Renderer *rendu) {
    SDL_Surface *surface = IMG_Load(chemin);
    if (!surface) {
        fprintf(stderr, "Erreur chargement image %s: %s\n", chemin, IMG_GetError());
        return NULL;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) {
        fprintf(stderr, "Erreur création texture %s: %s\n", chemin, SDL_GetError());
        return NULL;
    }
    
    return texture;
}
void creerBoutonTailleFixe(Bouton *bouton, SDL_Texture *texture, int x, int y, int w, int h) {
    bouton->normal = texture;
    bouton->selectionne = texture;
    bouton->position.x = x;
    bouton->position.y = y;
    bouton->position.w = w;
    bouton->position.h = h;
    bouton->estSurvole = 0;
}
int initialiserMenu(MenuOption *menu,SDL_Window *window,SDL_Renderer *renderer) {
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    /*
    SDL_GetWindowSize(menu->fenetre, &menu->largeurEcran, &menu->hauteurEcran);

	menu->btnRetour.position.x = (menu->largeurEcran / 2) - 175;
	menu->btnRetour.position.y = menu->hauteurEcran - 200;
	menu->btnRetour.position.w = 350;
	menu->btnRetour.position.h = 100;
    */
    menu->fenetre = window;
    
    if (!menu->fenetre) {
        fprintf(stderr, "Erreur création fenêtre: %s\n", SDL_GetError());
        return -1;
    }
    
    //menu->rendu = SDL_CreateRenderer(menu->fenetre, -1, 
    //                                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    menu->rendu= renderer;
    if (!menu->rendu) {
        fprintf(stderr, "Erreur création renderer: %s\n", SDL_GetError());
        return -1;
    }
    
    menu->menuActuel = MENU_OPTIONS;
    menu->volumeSonore = 4;
    menu->estPleinEcran = 0;
    menu->enCours = 1;
    menu->dernierBoutonSurvole = -1;
    
    return 0;
}
int chargerRessources(MenuOption *menu) {
    menu->arrierePlan1 = chargerTexture("assets/background_option.jpg", menu->rendu);
    menu->arrierePlan2 = chargerTexture("assets/background_option.jpg", menu->rendu);
    
    if (!menu->arrierePlan1 || !menu->arrierePlan2) {
        fprintf(stderr, "Erreur chargement arrière-plans\n");
        return -1;
    }
    
    menu->btnOptions.normal = chargerTexture("assets/button.png", menu->rendu);
    menu->btnOptions.selectionne = chargerTexture("assets/button_select.png", menu->rendu);
    menu->btnRetour.normal = chargerTexture("assets/button.png", menu->rendu);
    menu->btnRetour.selectionne = chargerTexture("assets/button_select.png", menu->rendu);
    menu->btnAugmenterVolume.normal = chargerTexture("assets/button.png", menu->rendu);
    menu->btnAugmenterVolume.selectionne = chargerTexture("assets/button_select.png", menu->rendu);
    menu->btnDiminuerVolume.normal = chargerTexture("assets/button.png", menu->rendu);
    menu->btnDiminuerVolume.selectionne = chargerTexture("assets/button_select.png", menu->rendu);
    menu->btnPleinEcran.normal = chargerTexture("assets/button.png", menu->rendu);
    menu->btnPleinEcran.selectionne = chargerTexture("assets/button_select.png", menu->rendu);
    menu->btnModeNormal.normal = chargerTexture("assets/button.png", menu->rendu);
    menu->btnModeNormal.selectionne = chargerTexture("assets/button_select.png", menu->rendu);
    
    if (!menu->btnOptions.normal || !menu->btnRetour.normal || 
        !menu->btnAugmenterVolume.normal || !menu->btnDiminuerVolume.normal ||
        !menu->btnPleinEcran.normal || !menu->btnModeNormal.normal) {
        fprintf(stderr, "Erreur chargement boutons\n");
        return -1;
    }
    
    menu->police = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 28);
    if (!menu->police) {
        menu->police = TTF_OpenFont("/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf", 28);
    }
    if (!menu->police) {
        fprintf(stderr, "Avertissement: Police non trouvée, texte non affiché\n");
    }
    
    menu->musiqueMenu = Mix_LoadMUS("assets/music_option.mp3");
    menu->musiqueOptions = Mix_LoadMUS("assets/music_option.mp3");
    menu->sonSurvol = Mix_LoadWAV("assets/song button.mp3");
    
    if (!menu->musiqueMenu) {
        fprintf(stderr, "Avertissement: music_option.mp3 non trouvé\n");
    }
    if (!menu->musiqueOptions) {
        fprintf(stderr, "Avertissement: music_option.mp3 non trouvé\n");
    }
    if (!menu->sonSurvol) {
        fprintf(stderr, "Avertissement: song button.mp3 non trouvé\n");
    }
    
    return 0;
}
void gererMouvementSouris(MenuOption *menu, int x, int y) {
    int boutonSurvole = -1;
    
    
    menu->btnRetour.estSurvole = 0;
    menu->btnAugmenterVolume.estSurvole = 0;
    menu->btnDiminuerVolume.estSurvole = 0;
    menu->btnPleinEcran.estSurvole = 0;
    menu->btnModeNormal.estSurvole = 0;
    
    
    if (x >= menu->btnRetour.position.x && 
        x <= menu->btnRetour.position.x + menu->btnRetour.position.w &&
        y >= menu->btnRetour.position.y && 
        y <= menu->btnRetour.position.y + menu->btnRetour.position.h) {
        menu->btnRetour.estSurvole = 1;
        boutonSurvole = 2;
    }
    
    else if (x >= menu->btnAugmenterVolume.position.x && 
             x <= menu->btnAugmenterVolume.position.x + menu->btnAugmenterVolume.position.w &&
             y >= menu->btnAugmenterVolume.position.y && 
             y <= menu->btnAugmenterVolume.position.y + menu->btnAugmenterVolume.position.h) {
        menu->btnAugmenterVolume.estSurvole = 1;
        boutonSurvole = 3;
    }
    
    else if (x >= menu->btnDiminuerVolume.position.x && 
             x <= menu->btnDiminuerVolume.position.x + menu->btnDiminuerVolume.position.w &&
             y >= menu->btnDiminuerVolume.position.y && 
             y <= menu->btnDiminuerVolume.position.y + menu->btnDiminuerVolume.position.h) {
        menu->btnDiminuerVolume.estSurvole = 1;
        boutonSurvole = 4;
    }
    
    else if (x >= menu->btnPleinEcran.position.x && 
             x <= menu->btnPleinEcran.position.x + menu->btnPleinEcran.position.w &&
             y >= menu->btnPleinEcran.position.y && 
             y <= menu->btnPleinEcran.position.y + menu->btnPleinEcran.position.h) {
        menu->btnPleinEcran.estSurvole = 1;
        boutonSurvole = 5;
    }
    
    else if (x >= menu->btnModeNormal.position.x && 
             x <= menu->btnModeNormal.position.x + menu->btnModeNormal.position.w &&
             y >= menu->btnModeNormal.position.y && 
             y <= menu->btnModeNormal.position.y + menu->btnModeNormal.position.h) {
        menu->btnModeNormal.estSurvole = 1;
        boutonSurvole = 6;
    }
    
    
    jouerSonSurvol(menu, boutonSurvole);
}
int gererClicSouris(MenuOption *menu, int x, int y) {
	int ouvMenu=0;
    if (menu->btnRetour.estSurvole) {
        menu->enCours = 0;
          
        ouvMenu=1;
    }
    
    else if (menu->btnAugmenterVolume.estSurvole) {
        if (menu->volumeSonore < 8) {
            menu->volumeSonore++;
            mettreAJourVolume(menu);
        }
    }
    
    else if (menu->btnDiminuerVolume.estSurvole) {
        if (menu->volumeSonore > 0) {
            menu->volumeSonore--;
            mettreAJourVolume(menu);
        }
    }
    
    else if (menu->btnPleinEcran.estSurvole) {
        menu->estPleinEcran = 1;
        basculerPleinEcran(menu);
    }
    
    else if (menu->btnModeNormal.estSurvole) {
        menu->estPleinEcran = 0;
        basculerPleinEcran(menu);
    }
    return ouvMenu;
}
void gererToucheClavier(MenuOption *menu, SDL_Keycode touche) {
    switch (touche) {
        case SDLK_ESCAPE:
            
            menu->enCours = 0;
            break;
            
        case SDLK_PLUS:
        case SDLK_KP_PLUS:
        case SDLK_EQUALS:
            
            if (menu->volumeSonore < 8) {
                menu->volumeSonore++;
                mettreAJourVolume(menu);
            }
            break;
            
        case SDLK_MINUS:
        case SDLK_KP_MINUS:
            
            if (menu->volumeSonore > 0) {
                menu->volumeSonore--;
                mettreAJourVolume(menu);
            }
            break;
            
        default:
            break;
    }
}
int gererEvenements(MenuOption *menu) {
	int ouv;
    SDL_Event evenement;
    while (SDL_PollEvent(&evenement)) {
        switch (evenement.type) {
            case SDL_QUIT:
                
                menu->enCours = 0;
                break;
                
            case SDL_MOUSEMOTION:
                
                gererMouvementSouris(menu, evenement.motion.x, evenement.motion.y);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                
                ouv=gererClicSouris(menu, evenement.button.x, evenement.button.y);
                break;
                
            case SDL_KEYDOWN:
                
                gererToucheClavier(menu, evenement.key.keysym.sym);
                break;
        }
    }
    return ouv;
}
void mettreAJourVolume(MenuOption *menu) {
    
    int volume = (MIX_MAX_VOLUME / 8) * menu->volumeSonore;
    
    
    Mix_Volume(-1, volume);
    Mix_VolumeMusic(volume);
}
void basculerPleinEcran(MenuOption *menu) {
    if (menu->estPleinEcran) {
        
        SDL_SetWindowFullscreen(menu->fenetre, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        
        SDL_SetWindowFullscreen(menu->fenetre, 0);
        SDL_SetWindowSize(menu->fenetre, 1024, 768);
        SDL_SetWindowPosition(menu->fenetre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }
}
void mettreAJour(MenuOption *menu) {
    
    mettreAJourVolume(menu);
}
void afficherTexte(MenuOption *menu, const char *texte, int x, int y, SDL_Color couleur) {
    if (!menu->police) return;
    
    SDL_Surface *surface = TTF_RenderText_Blended(menu->police, texte, couleur);
    if (!surface) return;
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(menu->rendu, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect rectDest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(menu->rendu, texture, NULL, &rectDest);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
void afficherMenuOptions(MenuOption *menu) {
    SDL_RenderCopy(menu->rendu, menu->arrierePlan2, NULL, NULL);
    
    SDL_Color blanc = {255, 255, 255, 255};
    
    int largeurBouton = 350;
    int hauteurBouton = 300;
    
    afficherTexte(menu, "Volume", 50, 50, blanc);
    
    menu->btnDiminuerVolume.position.x = 90;
    menu->btnDiminuerVolume.position.y = 50;
    menu->btnDiminuerVolume.position.w = largeurBouton;
    menu->btnDiminuerVolume.position.h = hauteurBouton;
    
    SDL_Texture *btnDiminuer = menu->btnDiminuerVolume.estSurvole ? 
                               menu->btnDiminuerVolume.selectionne : menu->btnDiminuerVolume.normal;
    SDL_RenderCopy(menu->rendu, btnDiminuer, NULL, &menu->btnDiminuerVolume.position);
    afficherTexte(menu, "Diminuer", 150, 180, blanc);
    
    menu->btnAugmenterVolume.position.x = 550;
    menu->btnAugmenterVolume.position.y = 50;
    menu->btnAugmenterVolume.position.w = largeurBouton;
    menu->btnAugmenterVolume.position.h = hauteurBouton;
    
    SDL_Texture *btnAugmenter = menu->btnAugmenterVolume.estSurvole ? 
                                menu->btnAugmenterVolume.selectionne : menu->btnAugmenterVolume.normal;
    SDL_RenderCopy(menu->rendu, btnAugmenter, NULL, &menu->btnAugmenterVolume.position);
    afficherTexte(menu, "Augmenter", 620, 180, blanc);
    
    SDL_Rect barreVolume = {70, 330, menu->volumeSonore * 35, 25};
    SDL_SetRenderDrawColor(menu->rendu, 0, 255, 0, 255);
    SDL_RenderFillRect(menu->rendu, &barreVolume);
    
    char texteVolume[20];
    snprintf(texteVolume, sizeof(texteVolume), "Niveau: %d/8", menu->volumeSonore);
    afficherTexte(menu, texteVolume, 100, 300, blanc);
    
    afficherTexte(menu, "Mode d'affichage", 50, 370, blanc);
    
    menu->btnModeNormal.position.x = 90;
    menu->btnModeNormal.position.y = 340;
    menu->btnModeNormal.position.w = largeurBouton;
    menu->btnModeNormal.position.h = hauteurBouton;
    
    SDL_Texture *btnNormal = menu->btnModeNormal.estSurvole ? 
                             menu->btnModeNormal.selectionne : menu->btnModeNormal.normal;
    SDL_RenderCopy(menu->rendu, btnNormal, NULL, &menu->btnModeNormal.position);
    afficherTexte(menu, "Normal", 150, 470, blanc);
    
    menu->btnPleinEcran.position.x = 550;
    menu->btnPleinEcran.position.y = 340;
    menu->btnPleinEcran.position.w = largeurBouton;
    menu->btnPleinEcran.position.h = hauteurBouton;
    
    SDL_Texture *btnPlein = menu->btnPleinEcran.estSurvole ? 
                            menu->btnPleinEcran.selectionne : menu->btnPleinEcran.normal;
    SDL_RenderCopy(menu->rendu, btnPlein, NULL, &menu->btnPleinEcran.position);
    afficherTexte(menu, "Plein ecran", 620, 470, blanc);
    
    const char *texteMode = menu->estPleinEcran ? "Mode: Plein ecran" : "Mode: Normal";
    afficherTexte(menu, texteMode, 50, 950, blanc);
    
    menu->btnRetour.position.x = (menu->largeurEcran / 2) - (largeurBouton / 2);
    menu->btnRetour.position.y = menu->hauteurEcran - 230;
    menu->btnRetour.position.w = largeurBouton;
    menu->btnRetour.position.h = hauteurBouton;
    
    SDL_Texture *btnRetour = menu->btnRetour.estSurvole ? 
                             menu->btnRetour.selectionne : menu->btnRetour.normal;
    SDL_RenderCopy(menu->rendu, btnRetour, NULL, &menu->btnRetour.position);
    afficherTexte(menu, "Retour", (menu->largeurEcran / 2) - 60, menu->hauteurEcran - 100, blanc);
}
void afficher(MenuOption *menu) {
    
    SDL_SetRenderDrawColor(menu->rendu, 0, 0, 0, 255);
    SDL_RenderClear(menu->rendu);
    
    
    afficherMenuOptions(menu);
    
    
    SDL_RenderPresent(menu->rendu);
}
void libererRessources(MenuOption *menu) {
    
    if (menu->btnOptions.normal) SDL_DestroyTexture(menu->btnOptions.normal);
    if (menu->btnOptions.selectionne) SDL_DestroyTexture(menu->btnOptions.selectionne);
    if (menu->btnRetour.normal) SDL_DestroyTexture(menu->btnRetour.normal);
    if (menu->btnRetour.selectionne) SDL_DestroyTexture(menu->btnRetour.selectionne);
    if (menu->btnAugmenterVolume.normal) SDL_DestroyTexture(menu->btnAugmenterVolume.normal);
    if (menu->btnAugmenterVolume.selectionne) SDL_DestroyTexture(menu->btnAugmenterVolume.selectionne);
    if (menu->btnDiminuerVolume.normal) SDL_DestroyTexture(menu->btnDiminuerVolume.normal);
    if (menu->btnDiminuerVolume.selectionne) SDL_DestroyTexture(menu->btnDiminuerVolume.selectionne);
    if (menu->btnPleinEcran.normal) SDL_DestroyTexture(menu->btnPleinEcran.normal);
    if (menu->btnPleinEcran.selectionne) SDL_DestroyTexture(menu->btnPleinEcran.selectionne);
    if (menu->btnModeNormal.normal) SDL_DestroyTexture(menu->btnModeNormal.normal);
    if (menu->btnModeNormal.selectionne) SDL_DestroyTexture(menu->btnModeNormal.selectionne);
    
    
    if (menu->arrierePlan1) SDL_DestroyTexture(menu->arrierePlan1);
    if (menu->arrierePlan2) SDL_DestroyTexture(menu->arrierePlan2);
    
    
    if (menu->musiqueMenu) Mix_FreeMusic(menu->musiqueMenu);
    if (menu->musiqueOptions) Mix_FreeMusic(menu->musiqueOptions);
    if (menu->sonSurvol) Mix_FreeChunk(menu->sonSurvol);
    
    
    if (menu->police) TTF_CloseFont(menu->police);
    
    
    
    
    
    
}
void jouerSonSurvol(MenuOption *menu, int idBouton) {
    if (menu->dernierBoutonSurvole != idBouton && idBouton != -1) {
        if (menu->sonSurvol) {
            printf("Son de survol joué pour bouton %d\n", idBouton);
            Mix_PlayChannel(-1, menu->sonSurvol, 0);
        } else {
            printf("Son de survol non disponible\n");
        }
        menu->dernierBoutonSurvole = idBouton;
    }
}

