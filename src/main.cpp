//**************************
//Mario Game SDL 2.0
//
// AUTEUR : Shane O'MULLAN
//          IUT GEII BRIVE
//**************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "IUTSDL.h"

// -----------------------------------------------------
// Constantes

const int tatoal_time = 60;    //60seconds to read the rules

// -----------------------------------------------------
// Nom du jeu
#define TITRE "Mario Shane"

// Dimensions de la grille
#define NBL 20       // Nombre de lignes
#define NBC 35          // Nombre de colonnes

// Dimensions des cases : correspond au images bitmap
#define CASE_W 34       // Largeur
#define CASE_H 34       // Hauteur

// Dimensions de l'écran
#define SCREEN_W NBC*CASE_W
#define SCREEN_H NBL*CASE_H

// Types de mouvements Mario. Indices des sprites correspondants dans le tableau des textures.
#define MOVE_LEFT    0
#define MOVE_RIGHT   1
#define MOVE_UP      2
#define MOVE_DOWN    3

// Position à atteindre pour fin du jeu : en haut à droite
#define XFIN    NBC-1
#define YFIN    0


// -----------------------------------------------------
// Globales
// -----------------------------------------------------
// Pour affichage (traitement timer)
char gTitle[100] = "";              // Titre a afficher sur la fenetre
int sortie = 0 ;

// Déclaration de la carte

// 'C' = Coins, 'M' = Wall, 'F' = Flagpole, 'O' = Bomb, 'P' = Plant , 'B'=Bridge, 'W'=Water
char ecran [NBL][NBC] =
{{'.','.','.','.','M','.','.','.','.','M','M','.','.','.','.','.','.','.','.','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'.','.','.','.','M','.','P','P','.','M','M','.','.','.','M','.','.','.','.','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'.','.','.','.','M','.','.','P','.','M','M','.','T','.','M','.','.','O','.','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'.','.','.','.','M','.','P','.','.','M','M','.','.','.','M','.','.','.','.','M','M','W','W','W','W','W','W','W','W','W','W','M','W','W','M'},
 {'.','.','.','.','M','.','P','.','P','M','M','P','.','P','M','.','.','O','.','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'.','.','.','.','M','.','P','.','.','M','M','.','.','.','M','.','.','.','.','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'.','.','.','.','M','.','.','P','.','M','M','.','T','.','M','.','.','O','.','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'.','.','.','.','M','.','P','.','.','M','M','.','.','.','M','.','.','.','.','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'.','.','.','.','M','.','P','.','P','M','M','P','.','P','M','.','.','O','.','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'.','.','.','.','M','C','P','.','.','.','T','.','.','.','M','.','.','.','.','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M'},
 {'W','B','B','W','W','W','.','.','.','.','.','.','.','.','M','.','.','.','.','.','.','.','.','.','M','.','.','.','.','.','.','.','.','.','.'},
 {'.','.','.','.','.','M','.','.','.','M','M','M','M','M','.','M','M','.','.','.','.','.','.','.','M','.','.','.','.','.','.','.','.','.','.'},
 {'.','.','.','.','.','M','.','.','.','M','M','C','.','.','T','.','.','T','.','.','M','P','P','C','M','.','P','P','.','M','M','M','M','.','.'},
 {'.','.','M','.','.','M','.','.','.','M','W','W','W','W','W','W','W','W','W','W','M','.','.','.','M','.','.','P','.','M','.','.','.','P','.'},
 {'P','.','M','C','.','M','.','.','.','M','W','W','W','W','W','W','W','W','W','W','M','C','P','P','M','P','.','.','P','M','M','M','.','.','M'},
 {'.','.','M','M','M','M','.','.','.','M','W','W','W','W','W','W','W','W','W','W','M','.','.','.','M','.','.','T','.','M','.','.','.','T','.'},
 {'.','.','.','.','.','.','.','.','.','M','W','W','W','W','W','W','W','W','W','W','M','P','P','C','M','.','P','P','.','M','M','M','.','.','M'},
 {'.','P','.','.','.','.','.','.','.','M','W','W','W','W','W','W','W','W','W','W','M','.','.','.','M','.','.','T','.','M','.','.','.','T','.'},
 {'.','.','.','.','T','.','.','.','.','M','W','W','W','W','W','W','W','W','W','W','M','C','P','P','M','P','.','.','P','M','M','.','.','.','.'},
 {'.','.','.','.','.','.','.','.','C','M','W','W','W','W','W','W','W','W','W','W','M','.','.','.','.','T','.','.','.','M','M','.','.','.','F'}};


// Bitmaps pour l'affichage
SDL_Texture *pTextureBackground ;
SDL_Texture *pTextureCoin ;
SDL_Texture *pTextureWall ;
SDL_Texture *pTextureWater ;
SDL_Texture *pTextureFlagpole ;
SDL_Texture *pTextureBomb ;
SDL_Texture *pTextureExplosion ;
SDL_Texture *pTexturePlant ;
SDL_Texture *pTextureTurtle ;
SDL_Texture *pTextureInverse ;

SDL_Texture *pTextureBrigde ;
SDL_Texture *pTextureTrophy ;
SDL_Texture *pTextureBowser ;
SDL_Texture *pTextureGagne ;  // déclaration image gagné de fin
SDL_Texture *pTexturePerdu ;  // déclaration image perdu de fin
SDL_Texture *pTextureMario[4]  ;

// Coordonnées écran de chacune des cases pour l'affichage du fond et des sprites
SDL_Rect rectGrille[NBC][NBL] ;


Uint32 callback( Uint32 interval, void* param )
{
    static int compteur = 0 ;
    int game_time ; // Init du temps de jeu
    game_time = compteur / 1000 ;  // Conversion en secondes

    compteur+=interval ;

    //Print the time in the top bar
    sprintf(gTitle," - Temps de jeu : %d sec ",game_time) ;


    return interval;
}
   //This Rules will show before the game starts
void rules()
{
    printf("\nWELCOME to Shane's Mario Game !!!\n");
    printf("To Move Mario around use the arrows on your Keyboard\n");
    printf("The rules of the game are simple if you hit a Fireball, Plant or Turtle Mario \n dies !\n");
    printf("\nAnd if you fall in the water you die also......\n");
    printf("\nTo win :\n 1) Collect all the coins\n 2) Get to the Flagpole the fastest you can to get a better Score !!\n");
    printf("\nRemember this game is for Fun !\n");
    printf("\nThe Game will start by itself, ENJOY!!!!!!\n And PRESS ECHAP to quit the game");

    //SDL_Delay(2000) ;
}

// Load texture
SDL_Texture *loadTexture(SDL_Renderer *sdlRenderer, const char *name) {
    // Calcul du chemin
    char filename[1024];
    snprintf(filename, 1023, "images/%s.bmp", name);

    return IUTSDL_LoadTexture(sdlRenderer, filename, 0xFF,0xFF,0xFF);
}

// -----------------------------------------------------
// Initialisations jeu
// -----------------------------------------------------
// Chargement des bitmaps pour affichage
void initTextures(SDL_Renderer *sdlRenderer)
{
    pTextureBackground=loadTexture(sdlRenderer, "background");
    pTextureCoin=loadTexture(sdlRenderer, "coin");
    pTextureWall=loadTexture(sdlRenderer, "wall");
    pTextureWater=loadTexture(sdlRenderer, "water");
    pTextureBrigde=loadTexture(sdlRenderer, "bridge");
    pTextureBomb=loadTexture(sdlRenderer, "bomb");
    pTextureExplosion=loadTexture(sdlRenderer, "explosion");

    pTexturePlant=loadTexture(sdlRenderer, "plant");
    pTextureFlagpole=loadTexture(sdlRenderer, "flagpole");
    pTextureInverse=loadTexture(sdlRenderer, "inverse");
    pTextureMario[MOVE_LEFT]=loadTexture(sdlRenderer, "mario-gauche");
    pTextureMario[MOVE_RIGHT]=loadTexture(sdlRenderer, "mario-droite");
    pTextureMario[MOVE_UP]=loadTexture(sdlRenderer, "mario-haut");
    pTextureMario[MOVE_DOWN]=loadTexture(sdlRenderer, "mario-bas");



    pTextureTrophy=loadTexture(sdlRenderer, "trophy");
    pTextureBowser=loadTexture(sdlRenderer, "bowser");

}

// Initialisation coordonnées des cases de la grille
void initRectGrille()
{
    for (int y = 0; y < NBL ; y++) {
        for (int x=0 ; x < NBC ; x++) {
            rectGrille[y][x].x = x * CASE_W;
            rectGrille[y][x].y = y * CASE_H;
            rectGrille[y][x].w = CASE_W;
            rectGrille[y][x].h = CASE_H;
        }
    }
}

void renderTile(SDL_Renderer *sdlRenderer, int x, int y, SDL_Texture *texture) {
    SDL_Rect rect ;
    rect.x = x * CASE_W ;
    rect.y = y * CASE_H ;
    rect.w = CASE_W ;
    rect.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, texture, NULL, &rect);
}

SDL_Texture *tileTexture(char tile) {
    if (tile == 'M') {
        return pTextureWall;
    } else if (tile == 'C') {
        return pTextureCoin;
    } else if (tile == 'F') {
        return pTextureFlagpole;
    } else if (tile == 'W') {
        return pTextureWater;
    } else if (tile == 'P') {
        return pTexturePlant;
    } else if (tile == 'T') {
        return pTextureTurtle;
    } else if (tile == 'S') {
        return pTextureInverse;
    } else if (tile == 'O') {
        return pTextureBomb;
    } else if (tile == 'B') {
        return pTextureBrigde;
    }
    return NULL;
}

// Affichage Mario
void affichageMario(SDL_Renderer *sdlRenderer, int x, int y, int sens)
{
    SDL_Rect rectMario ;
    rectMario.x = x * CASE_W;
    rectMario.y = y * CASE_H;
    rectMario.w = CASE_W ;
    rectMario.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureMario[sens], NULL, &rectMario); //on note pTextureMario[a] afin de pouvoir utiliser le sprite
}

//Print Trophy
void affichageTrophy(SDL_Renderer *sdlRenderer)
{
    int w = 13 * CASE_W;
    int h = 8 * CASE_H;
    int x = SCREEN_W/2 - w/2;
    int y = SCREEN_H/2 - h/2;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(sdlRenderer, pTextureTrophy, NULL, &rect);
}

//Print Bowser
void affichageBowser(SDL_Renderer *sdlRenderer)
{
    // Compute position
    int w = 8*CASE_W;
    int h = 8*CASE_H;
    int x = SCREEN_W/2 - w/2;
    int y = SCREEN_H/2 - h/2;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(sdlRenderer, pTextureBowser, NULL, &rect);
}

//effacer les traces de mario
void effacerMario(SDL_Renderer *sdlRenderer, int x, int y)
{
    SDL_Rect rect = rectGrille[y][x] ;
    SDL_RenderCopy(sdlRenderer, pTextureBackground, NULL, &rect);

}

// Fonction d'initialisation du jeu
void init(SDL_Renderer *sdlRenderer)
{
    // Init random
    //srand(time(NULL));

    // Textures pour afficher éléments du jeu
    initTextures(sdlRenderer) ;


    // Grille pour affichage décors. Attention Table colonne/ligne pour respecter le sens x=colonne et y=ligne
    initRectGrille() ;
}


void renderMap(SDL_Renderer *sdlRenderer) {
    // Print Background
    for(int y = 0; y < NBL; y++) {
        for (int x = 0; x < NBC; x++) {
            char tile = ecran[y][x];
            renderTile(sdlRenderer, x, y, pTextureBackground);
            renderTile(sdlRenderer, x, y, tileTexture(tile));
        }
    }
}

// -----------------------------------------------------
// Fonction main
// -----------------------------------------------------
int main( int argc, char* args[] )
{
    SDL_Window   *pScreen=NULL;         // Fenetre
    SDL_Renderer *sdlRenderer=NULL;     // Declaration du Buffer Video


    int x, y,i,j,sens ;
    //Mario Direction
    int dirMario ;

    rules();

    // Initialisation utilisation de la SDL
    if( IUTSDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) != NO_ERROR )
    {
        printf("Erreur IUTSDL\n") ;
        exit(1) ;
    }

    // Création de la fenêtre
    pScreen = IUTSDL_CreateWindow(TITRE, SCREEN_W, SCREEN_H);


    if (pScreen == NULL)
    {
        printf("Erreur IUTSDL\n") ;
        exit(1) ;
    }

    // Icône
    IUTSDL_SetWindowIcon (pScreen, "images/mario-icone-64.bmp");

    // Début affichege
    sdlRenderer = SDL_CreateRenderer(pScreen, -1, 0 /*SDL_RENDERER_ACCELERATED*/);      // Association du Buffer Video à la Fenetre
    //sdlRenderer = SDL_CreateRenderer(pScreen, -1, SDL_RENDERER_SOFTWARE);      // Association du Buffer Video à la Fenetre
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(sdlRenderer, SCREEN_W, SCREEN_H);

    // Fin d'initialisation graphique SDL
    //
    // Timer
    //
    // Création d'un timer pour affichage du titre. La fonction callback sera appellée périodiquement toutes les 100ms
    SDL_TimerID timerID = SDL_AddTimer(1000, callback, NULL );


    // Jeu
    // Initialisations
    init(sdlRenderer) ;

    int xMario = 0;
    int yMario = 0;
    dirMario = MOVE_DOWN ;
    int dollar = 0;

    // Quit game
    int escape = 0;
    // Died
    int dead = 0;
    // Sucess
    int success = 0;

    while(!escape)
    {
        // Affichage du titre en haut de la fenetre
        SDL_SetWindowTitle(pScreen, gTitle);

        SDL_Delay(50) ;

        // Keyboard to action in game
        SDL_Event( event );
        while(SDL_PollEvent( &event ) != 0) {
            sens = -1 ;
            switch(event.type) {
                // Window exit
                case SDL_QUIT :
                    escape = 1 ;
                    break;

                // Handle keyboard
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym) {
                    case SDLK_LEFT:
                        sens = MOVE_LEFT ;
                        break;
                    case SDLK_RIGHT:
                        sens = MOVE_RIGHT ;
                        break;
                    case SDLK_UP:
                        sens = MOVE_UP;
                        break;
                    case SDLK_DOWN:
                        sens = MOVE_DOWN ;
                        break;
                    case SDLK_ESCAPE:
                        escape = 1;
                    }
            }

            switch (sens) {
                case MOVE_UP:
                    yMario--;
                    break;

                case MOVE_DOWN:
                    yMario++;
                    break;

                case MOVE_LEFT:
                    xMario--;
                    break;

                case MOVE_RIGHT:
                    xMario++;
                    break;
            }
        }

        // If Mario hits something
        char tile = ecran[yMario][xMario];
        if(tile == 'O') {
            dead = 1;
        } else if(tile == 'P') {
            dead = 1;
        } else if(tile == 'T') {
            dead = 1;
        } else if(tile == 'E') {
            dead = 1;
        }
      /*  if(ecran[xMario][yMario] == 'S')
            {
                MOVE_UP    =MOVE_DOWN;
                MOVE_DOWN  =MOVE_UP;
                MOVE_RIGHT =MOVE_LEFT;
                MOVE_LEFT  =MOVE_RIGHT;
            }*/

        // Coins
        if (tile == 'C') {
            // Remove coin
            ecran[yMario][xMario] = '.';
            dollar++;
        }


        // when Mario on 'F' with all the coins collected the game ends
        if (dollar == 5 && tile == 'F') {
            success = 1;
        }

        // Render
        SDL_RenderClear(sdlRenderer);
        if(success) {
            affichageTrophy(sdlRenderer);
        } else if(!dead) {
            renderMap(sdlRenderer);
            affichageMario(sdlRenderer, xMario, yMario, dirMario);
        } else {
            affichageBowser(sdlRenderer);
        }
        IUTSDL_RefreshScreen(sdlRenderer);
    }

    return 0 ;

}
