#ifndef MENU_OPTION_H
#define MENU_OPTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define NIVEAUX_VOLUME 9  // Niveaux de volume de 0 à 8

// États du menu
typedef enum {
    MENU_PRINCIPAL,      // Menu principal
    MENU_OPTIONS         // Sous-menu options
} EtatMenu;

// Structure pour un bouton
typedef struct {
    SDL_Texture *normal;      // Texture normale
    SDL_Texture *selectionne; // Texture sélectionnée (survol)
    SDL_Rect position;        // Position et dimensions
    int estSurvole;           // État de survol
} Bouton;

// Structure principale du menu
typedef struct {
    SDL_Window *fenetre;
    SDL_Renderer *rendu;
    
    // Arrière-plans
    SDL_Texture *arrierePlan1;     // Arrière-plan menu principal
    SDL_Texture *arrierePlan2;     // Arrière-plan menu options
    
    // Boutons
    Bouton btnOptions;             // Bouton "Options" (menu principal)
    Bouton btnRetour;              // Bouton "Retour" (menu options)
    Bouton btnAugmenterVolume;     // Bouton "Augmenter volume"
    Bouton btnDiminuerVolume;      // Bouton "Diminuer volume"
    Bouton btnPleinEcran;          // Bouton "Plein écran"
    Bouton btnModeNormal;          // Bouton "Mode normal"
    
    // Audio
    Mix_Music *musiqueMenu;        // Musique menu principal
    Mix_Music *musiqueOptions;     // Musique menu options
    Mix_Chunk *sonSurvol;          // Son de survol des boutons
    
    // Police pour le texte
    TTF_Font *police;              // Police pour les labels des boutons
    
    // État du menu
    EtatMenu menuActuel;           // Menu actuel
    int volumeSonore;              // Volume sonore (0-8)
    int estPleinEcran;             // Mode plein écran (0 ou 1)
    int enCours;                   // Boucle principale active
    int dernierBoutonSurvole;      // Dernier bouton survolé
    
    // Dimensions de la fenêtre
    int largeurEcran;
    int hauteurEcran;
} MenuOption;

// ============================================================================
// PHASE 1 : INITIALISATION
// ============================================================================
int initialiserMenu(MenuOption *menu,SDL_Window *window,SDL_Renderer *renderer);
int chargerRessources(MenuOption *menu);
SDL_Texture* chargerTexture(const char *chemin, SDL_Renderer *rendu);
void creerBoutonTailleFixe(Bouton *bouton, SDL_Texture *texture, int x, int y, int w, int h);

// ============================================================================
// PHASE 2 : INPUT (Gestion des événements)
// ============================================================================
int gererEvenements(MenuOption *menu);
void gererMouvementSouris(MenuOption *menu, int x, int y);
int gererClicSouris(MenuOption *menu, int x, int y);
void gererToucheClavier(MenuOption *menu, SDL_Keycode touche);

// ============================================================================
// PHASE 3 : MISE À JOUR (Update)
// ============================================================================
void mettreAJour(MenuOption *menu);
void mettreAJourVolume(MenuOption *menu);
void basculerPleinEcran(MenuOption *menu);

// ============================================================================
// PHASE 4 : AFFICHAGE (Render)
// ============================================================================
void afficher(MenuOption *menu);
void afficherMenuPrincipal(MenuOption *menu);
void afficherMenuOptions(MenuOption *menu);
void afficherTexte(MenuOption *menu, const char *texte, int x, int y, SDL_Color couleur);

// ============================================================================
// PHASE 5 : LIBÉRATION MÉMOIRE
// ============================================================================
void libererRessources(MenuOption *menu);

// ============================================================================
// UTILITAIRES AUDIO
// ============================================================================
void jouerSonSurvol(MenuOption *menu, int idBouton);

// ============================================================================
// BOUCLE PRINCIPALE DU JEU
// ============================================================================
//int executerBoucleJeu(MenuOption *menu);

#endif
