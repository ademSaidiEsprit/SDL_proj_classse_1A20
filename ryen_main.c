#include "headeres.h"
#include "menu_option.h"
#include <stdio.h>

void option(SDL_Renderer *renderer,SDL_Window *window){
    MenuOption menu;
    
    // Initialiser le menu
    if (initialiserMenu(&menu,window,renderer) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation du menu\n");
    }
    
    // Charger les ressources
    if (chargerRessources(&menu) != 0) {
        fprintf(stderr, "Erreur lors du chargement des ressources\n");
        libererRessources(&menu);
    }
    
    
    if (menu.musiqueOptions) {
        Mix_PlayMusic(menu.musiqueOptions, -1);  
    }
    mettreAJourVolume(&menu);
    
    int ouvMenu;
    while (menu.enCours) {
        ouvMenu=gererEvenements(&menu);   
        mettreAJour(&menu);       
        afficher(&menu);          
        SDL_Delay(16); 
        if(ouvMenu==1) menu.enCours=0;          
    }


    int x=ouvMenu;
    
    // Libérer les ressources
    libererRessources(&menu);
    if(x==1) enigme(renderer);//system("./app");

}
