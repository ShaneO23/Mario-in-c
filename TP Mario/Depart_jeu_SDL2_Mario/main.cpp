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
#define NBL 35         // Nombre de lignes
#define NBC 20          // Nombre de colonnes

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

// 'C' = Coins, 'W' = Wall, 'F' = Flagpole, 'B' = Bomb, 'P' = Plant , 'Z'=Bridge, 'E'=Water

char ecran [NBC][NBL] =

    // 1   2   3   4    5   6   7  8   9   0   1   2   3   4   5   6   7   8   9   0
   /* {{'.','C','C','C','C','C','C','C','C','F','C','.','.','.','.','.','.','.','.','.'}, //1
    {'C','F','S','S','S','S','S','S','M','S','S','S','S','S','S','S','S','S','S','C'},  //2
    {'C','M','M','M','M','S','M','S','M','S','M','M','M','M','M','M','M','M','S','C'},  //3
    {'C','S','S','S','S','S','M','S','M','S','S','S','S','S','S','S','S','S','S','C'},  //4
    {'C','M','M','S','M','M','M','S','M','S','M','M','M','M','S','M','S','M','M','C'},  //5
    {'C','S','S','S','S','M','M','S','M','S','M','S','S','S','S','S','S','S','S','C'},  //6
    {'C','M','M','M','S','M','M','S','M','S','M','M','M','S','M','S','M','M','S','C'},  //7
    {'C','M','S','S','S','M','M','S','S','S','M','M','M','S','S','S','M','M','S','C'},  //8
    {'C','M','S','M','S','M','M','S','M','M','M','M','M','S','M','S','M','M','S','C'},  //9
    {'C','M','S','S','S','S','S','S','M','S','S','S','M','S','M','S','M','M','S','C'},  //0
    {'C','M','S','M','M','M','M','S','S','S','M','M','M','S','M','S','M','M','S','C'},  //1
    {'C','M','S','S','S','S','S','S','M','S','M','S','M','S','M','S','S','S','S','C'},  //2
    {'C','M','M','M','M','S','M','S','M','S','S','S','M','S','S','S','M','M','M','C'},  //3
    {'C','M','S','S','S','S','M','S','M','M','M','M','S','S','M','S','M','M','M','C'},  //4
    {'C','M','S','M','M','S','S','S','S','S','S','S','S','M','M','S','S','S','S','C'},  //5
    {'C','S','S','S','M','S','M','M','M','S','M','M','M','S','M','M','M','M','M','C'},  //6
    {'C','S','M','S','S','S','M','S','S','S','M','S','S','S','M','S','S','S','M','C'},  //7
    {'C','S','M','M','M','S','M','S','M','M','S','S','M','S','M','S','M','S','M','C'},  //8
    {'C','S','M','S','S','S','S','S','S','M','S','M','M','S','S','S','M','S','M','C'},  //9
    {'C','S','S','S','M','M','M','S','S','M','S','S','M','S','M','M','M','S','S','C'},  //0
    {'C','M','M','S','M','S','S','S','M','M','M','S','M','S','M','M','M','M','S','C'},  //1
    {'C','S','S','S','M','S','M','M','S','S','S','S','S','S','S','S','S','S','S','C'},  //2
    {'C','S','M','S','S','S','S','S','M','S','M','M','M','M','S','M','S','M','S','C'},  //3
    {'C','S','M','S','M','S','M','S','M','S','S','S','M','M','S','M','S','M','S','C'},  //4
    {'C','S','M','S','M','S','M','S','M','S','M','M','M','S','S','S','S','S','S','C'},  //5
    {'C','S','M','M','M','S','S','S','M','S','S','S','S','S','M','S','M','M','M','C'},  //6
    {'C','S','S','S','M','S','S','M','M','S','M','S','M','S','M','S','M','M','M','C'},  //7
    {'C','S','M','S','M','S','S','M','M','S','M','S','S','S','M','S','S','S','S','C'},  //8
    {'C','S','M','S','M','S','M','M','M','S','M','M','M','S','M','S','S','M','S','C'},  //9
    {'C','S','M','S','S','S','M','S','S','S','S','S','M','S','M','S','S','M','S','C'},  //0
    {'C','S','M','M','M','S','M','M','M','S','M','M','S','S','M','M','S','M','S','C'},  //1
    {'C','S','S','S','S','S','S','S','S','S','S','S','M','S','S','S','S','S','S','C'},  //2
    {'C','M','M','M','S','M','M','S','M','M','M','M','M','S','M','M','M','M','M','C'},  //3
    {'C','S','S','S','S','M','M','S','S','S','S','S','M','S','S','S','S','S','D','C'},  //4
    {'C','C','C','C','C','C','C','C','C','F','C','C','C','C','C','C','C','C','C','C'}}; //5*/
{{'.','.','.','.','W','.','.','.','.','W','W','.','.','.','.','.','.','.','.','W','W','E','E','E','E','E','E','E','E','E','E','E','E','E','W'},
 {'.','.','.','.','W','.','P','P','.','W','W','.','.','.','W','.','.','.','.','W','W','E','E','E','E','E','E','E','E','E','E','E','E','E','W'},
 {'.','.','.','.','W','.','.','P','.','W','W','.','T','.','W','.','.','O','.','W','W','E','E','E','E','E','E','E','E','E','E','E','E','E','W'},
 {'.','.','.','.','W','.','P','.','.','W','W','.','.','.','W','.','.','.','.','W','W','E','E','E','E','E','E','E','E','E','E','W','E','E','W'},
 {'.','.','.','.','W','.','P','.','P','W','W','P','.','P','W','.','.','O','.','W','W','E','E','E','E','E','E','E','E','E','E','E','E','E','W'},
 {'.','.','.','.','W','.','P','.','.','W','W','.','.','.','W','.','.','.','.','W','W','E','E','E','E','E','E','E','E','E','E','E','E','E','W'},
 {'.','.','.','.','W','.','.','P','.','W','W','.','T','.','W','.','.','O','.','W','W','E','E','E','E','E','E','E','E','E','E','E','E','E','W'},
 {'.','.','.','.','W','.','P','.','.','W','W','.','.','.','W','.','.','.','.','W','W','E','E','E','E','E','E','E','E','E','E','E','E','E','W'},
 {'.','.','.','.','W','.','P','.','P','W','W','P','.','P','W','.','.','O','.','W','W','E','E','E','E','E','E','E','E','E','E','E','E','E','W'},
 {'.','.','.','.','W','C','P','.','.','.','T','.','.','.','W','.','.','.','.','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','M'},
 {'E','B','B','E','E','E','.','.','.','.','.','.','.','.','W','.','.','.','.','.','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.'},
 {'.','.','.','.','.','W','.','.','.','W','W','W','W','W','.','M','W','.','.','.','.','.','.','.','W','.','.','.','.','.','.','.','.','.','.'},
 {'.','.','.','.','.','W','.','.','.','W','M','C','.','.','T','.','.','T','.','.','W','P','P','C','W','.','X','X','.','W','W','W','W','.','.'},
 {'.','.','W','.','.','W','.','.','.','W','E','E','E','E','E','E','E','E','E','E','W','.','.','.','W','.','.','P','.','W','.','.','.','P','.'},
 {'P','.','W','C','.','W','.','.','.','W','E','E','E','E','E','E','E','E','E','E','W','C','X','X','W','X','.','.','X','W','W','W','.','.','M'},
 {'.','.','W','W','W','W','.','.','.','W','E','E','E','E','E','E','E','E','E','E','W','.','.','.','W','.','.','T','.','W','.','.','.','T','.'},
 {'.','.','.','.','.','.','.','.','.','W','E','E','E','E','E','E','E','E','E','E','W','X','X','C','W','.','X','X','.','W','W','W','.','.','M'},
 {'.','P','.','.','.','.','.','.','.','W','E','E','E','E','E','E','E','E','E','E','W','.','.','.','W','.','.','T','.','W','.','.','.','T','.'},
 {'.','.','.','.','T','.','.','.','.','W','E','E','E','E','E','E','E','E','E','E','W','C','X','X','W','X','.','.','X','W','W','.','.','.','.'},
 {'.','.','.','.','.','.','.','.','C','W','E','E','E','E','E','E','E','E','E','E','W','.','.','.','.','T','.','.','.','W','W','.','.','.','F'}};


// Bitmaps pour l'affichage
SDL_Texture *pTextureBackground ;
SDL_Texture *pTextureCoin ;
SDL_Texture *pTextureWall ;
SDL_Texture *pTextureWater ;
SDL_Texture *pTextureFlagpole ;
SDL_Texture *pTextureBomb ;
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
    printf("\nThe Game will start by itself, ENJOY!!!!!!");

    SDL_Delay(2000) ;
}

// -----------------------------------------------------
// Initialisations jeu
// -----------------------------------------------------
// Chargement des bitmaps pour affichage
void initTextures(SDL_Renderer *sdlRenderer)
{
    pTextureBackground=IUTSDL_LoadTexture(sdlRenderer, "background.bmp" ,0xFF,0xFF,0xFF);
    pTextureCoin=IUTSDL_LoadTexture(sdlRenderer, "coin.bmp" ,0xFF,0xFF,0xFF);
    pTextureWall=IUTSDL_LoadTexture(sdlRenderer, "wall.bmp" ,0xFF,0xFF,0xFF);
    pTextureWater=IUTSDL_LoadTexture(sdlRenderer, "water.bmp" ,0xFF,0xFF,0xFF);
    pTextureBrigde=IUTSDL_LoadTexture(sdlRenderer, "bridge.bmp" ,0xFF,0xFF,0xFF);
    pTextureBomb=IUTSDL_LoadTexture(sdlRenderer, "bomb.bmp" ,0xFF,0xFF,0xFF);
    pTexturePlant=IUTSDL_LoadTexture(sdlRenderer, "plant.bmp" ,0xFF,0xFF,0xFF);
    pTextureFlagpole=IUTSDL_LoadTexture(sdlRenderer, "flagpole.bmp" ,0xFF,0xFF,0xFF);
    pTextureInverse=IUTSDL_LoadTexture(sdlRenderer, "inverse.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_LEFT]=IUTSDL_LoadTexture(sdlRenderer, "mario-gauche.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_RIGHT]=IUTSDL_LoadTexture(sdlRenderer, "mario-droite.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_UP]=IUTSDL_LoadTexture(sdlRenderer, "mario-haut.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_DOWN]=IUTSDL_LoadTexture(sdlRenderer, "mario-bas.bmp" ,0xFF,0xFF,0xFF);



    pTextureTrophy=IUTSDL_LoadTexture(sdlRenderer, "trophy.bmp" ,0xFF,0xFF,0xFF);
    pTextureBowser=IUTSDL_LoadTexture(sdlRenderer, "bowser.bmp" ,0xFF,0xFF,0xFF);

}

// Initialisation coordonnées des cases de la grille
void initRectGrille()
{
    for (int i=0 ; i<NBC ; i++ )
    {
        for (int j=0 ; j<NBL ; j++)
        {
            rectGrille[i][j].x = i * CASE_W ;
            rectGrille[i][j].y = j * CASE_H ;
            rectGrille[i][j].w = CASE_W ;
            rectGrille[i][j].h = CASE_H ;
        }
    }
}


// Affichage contenu fixe de la grille
void affichageBackground(SDL_Renderer *sdlRenderer, int i, int j)
{
    SDL_Rect rect ;
    rect.x = i*CASE_W ;
    rect.y = j*CASE_H ;
    rect.w = CASE_W ;
    rect.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureBackground, NULL, &rect);
}

// Affichage Mario
void affichageMario(SDL_Renderer *sdlRenderer, int x, int y, int sens)
{
    SDL_Rect rectMario ;
    rectMario.x = x*CASE_W ;
    rectMario.y = y*CASE_H ;
    rectMario.w = CASE_W ;
    rectMario.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureMario[4], NULL, &rectMario); //on note pTextureMario[a] afin de pouvoir utiliser le sprite
}


//Print Walls
void affichageMur(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect ;
    rect.x = CASE_W ;
    rect.y = CASE_H ;
    rect.w = CASE_W ;
    rect.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureWall, NULL, &rect);
}

//Print Inverse
void affichageInverse(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect ;
    rect.x = CASE_W ;
    rect.y = CASE_H ;
    rect.w = CASE_W ;
    rect.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureInverse, NULL, &rect);
}

//Print Coins
void affichageCoin(SDL_Renderer *sdlRenderer)
{

    SDL_Rect rect ;
    rect.x = CASE_W ;
    rect.y = CASE_H ;
    rect.w = CASE_W ;
    rect.h = CASE_H ;

    SDL_RenderCopy(sdlRenderer, pTextureCoin, NULL, &rect);

}

//Print Flag
void affichageFlagpole(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect ;
    rect.x = CASE_W ;
    rect.y = CASE_H ;
    rect.w = CASE_W ;
    rect.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureFlagpole, NULL, &rect);
}

//Print Trophy
void affichageTrophy(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect;
    rect.x = 12*CASE_W ;
    rect.y = 5*CASE_H ;
    rect.w = 13*CASE_W ;
    rect.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureTrophy, NULL, &rect);
}

//Print Bowser
void affichageBowser(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect;
    rect.x = 5*CASE_W ;
    rect.y = 5*CASE_H ;
    rect.w = 8*CASE_W ;
    rect.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureBowser, NULL, &rect);
}

//Print Water
void affichageWater(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect;
    rect.x = 5*CASE_W ;
    rect.y = 5*CASE_H ;
    rect.w = 8*CASE_W ;
    rect.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureWater, NULL, &rect);
}

//Print Plant
void affichagePlant(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect;
    rect.x = 5*CASE_W ;
    rect.y = 5*CASE_H ;
    rect.w = 8*CASE_W ;
    rect.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTexturePlant, NULL, &rect);
}

//Print Turtle
void affichageTurtle(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect;
    rect.x = 5*CASE_W ;
    rect.y = 5*CASE_H ;
    rect.w = 8*CASE_W ;
    rect.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureTurtle, NULL, &rect);
}




//effacer les traces de mario
void effacerMario(SDL_Renderer *sdlRenderer, int x, int y)
{
    SDL_Rect rect = rectGrille[x][y] ;
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

    //Print Background
    for(int i=0 ; i<NBC; i++)
    {
        for (int j=0 ; j<NBL; j++)
        {
            {

                affichageBackground(sdlRenderer,i ,j);

                    if (ecran[i][j] == 'M' )
                        {
                        affichageMur(sdlRenderer) ;
                        }

                    if (ecran[i][j] == 'C' )
                        {
                        affichageCoin(sdlRenderer);
                        }

                    if (ecran[i][j] == 'F' )
                        {
                        affichageFlagpole(sdlRenderer);
                        }

                    if (ecran[i][j] == 'W' )
                        {
                        affichageWater(sdlRenderer);
                        }

                    if (ecran[i][j] == 'P' )
                        {
                        affichagePlant(sdlRenderer);
                        }

                    if (ecran[i][j] == 'C' )
                        {
                        affichageTurtle(sdlRenderer);
                        }
                     if (ecran[i][j] == 'I' )
                        {
                        affichageInverse(sdlRenderer);
                        }
            }

        }
    }


    // Mise à jour de l'affichage
    IUTSDL_RefreshScreen(sdlRenderer);
}



// -----------------------------------------------------
// Fonction main
// -----------------------------------------------------
int main( int argc, char* args[] )
{
    SDL_Window   *pScreen=NULL;         // Fenetre
    SDL_Renderer *sdlRenderer=NULL;     // Declaration du Buffer Video


    int x, y,i,j,sens ;
    // Mario Position
    int xMario, yMario ;
    //Mario Direction
    int dirMario ;

    rules();

    // Initialisations graphique SDL
    // LAISSER TEL QUEL
    //
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
    IUTSDL_SetWindowIcon (pScreen, "mario-icone-64.bmp");

    // Début affichege
    //sdlRenderer = SDL_CreateRenderer(pScreen, -1, 0 /*SDL_RENDERER_ACCELERATED*/);      // Association du Buffer Video à la Fenetre
    sdlRenderer = SDL_CreateRenderer(pScreen, -1, SDL_RENDERER_SOFTWARE);      // Association du Buffer Video à la Fenetre


    IUTSDL_ClearScreen(sdlRenderer);

    // Fin d'initialisation graphique SDL
    //
    // Timer
    //
    // Création d'un timer pour affichage du titre. La fonction callback sera appellée périodiquement toutes les 100ms
    SDL_TimerID timerID = SDL_AddTimer(1000, callback, NULL );


    // Jeu
    // Initialisations
    init(sdlRenderer) ;

    xMario = 0 ;
    yMario = 0 ;
    dirMario = MOVE_DOWN ;
    int dollar=0;
    int escape;

    while(!escape)
    {
        // Affichage titre de fenetre
        SDL_SetWindowTitle(pScreen, gTitle);

        SDL_Delay(50) ;

        // Keyboard to action in game
        SDL_Event( event );
        while( SDL_PollEvent( &event ) != 0 )
        {
            sens = -1 ;
            switch ( event.type)
            {
                case SDL_QUIT :
                escape = 1 ;
                break;

            case SDL_KEYDOWN :
                switch( event.key.keysym.sym )
                {

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

            switch (sens)
            {
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

// If Mario hits something
                    if(ecran[xMario][yMario] == 'B' )
                        {
                            affichageBowser(sdlRenderer);
                        }
                    if(ecran[xMario][yMario] == 'P')
                        {
                            affichageBowser(sdlRenderer);
                        }
                     if(ecran[xMario][yMario] == 'T')
                        {
                            affichageBowser(sdlRenderer);
                        }
                    if(ecran[xMario][yMario] == 'E')
                        {
                            affichageBowser(sdlRenderer);
                        }
                    if(ecran[xMario][yMario] == 'I')
                        {
                            MOVE_UP    =MOVE_DOWN;
                            MOVE_DOWN  =MOVE_UP;
                            MOVE_RIGHT =MOVE_LEFT;
                            MOVE_LEFT  =MOVE_RIGHT;
                        }

// Coins
            if (ecran[xMario][yMario] == 'C')
            {
                dollar++;
            }


// when Mario on 'F' with all the coins collected the game ends
        if (dollar==5, ecran[xMario][yMario] == 'F')
         {
                escape = 1;
         }


        affichageMario(sdlRenderer, xMario, yMario, dirMario) ;
        IUTSDL_RefreshScreen(sdlRenderer);
    }

    IUTSDL_ClearScreen(sdlRenderer);
    IUTSDL_RefreshScreen(sdlRenderer);


    }

    return 0 ;

}
