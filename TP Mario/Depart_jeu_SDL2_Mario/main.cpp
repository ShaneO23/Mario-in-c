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
#define TITRE "Mario Shane»

// Dimensions de la grille
#define NBL 35         // Nombre de lignes
#define NBC 11          // Nombre de colonnes

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
{{'.','.','.','.','W','.','.','.','.','M','M','.','.','.','.','.','.','.','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','.','P','P','.','M','M','.','.','.','M','.','.','.','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','.','.','P','.','M','M','.','T','.','M','.','.','O','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','.','P','.','.','M','M','.','.','.','M','.','.','.','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','.','P','.','P','M','M','P','.','P','M','.','.','O','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','.','P','.','.','M','M','.','.','.','M','.','.','.','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','.','.','P','.','M','M','.','G','.','M','.','.','O','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','.','P','.','.','M','M','.','.','.','M','.','.','.','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','.','P','.','P','M','M','P','.','P','M','.','.','O','.','M','M','M','W','W','W','W','W','W','W','W','W','W','W','W','W'},
 {'.','.','.','.','W','C','P','.','.','.','T','.','.','.','M','.','.','.','.','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M'},
 {'W','B','B','W','W','W','.','.','.','.','.','.','.','.','M','.','.','.','.','.','.','.','.','.','M','.','.','.','.','.','.','.','.','.','.'}};
/* {.....M...MMMMM.MM.......M..........},
 {.....M...MMC..G..G..MXXCM.XX.MMMM..},
 {..M..M...MWWWWWWWWWWM...M..G.M...G.},
 {X.MC.M...MWWWWWWWWWWMCXXMX..XMMM..M},
 {..MMMM...MWWWWWWWWWWM...M..G.M...G.},
 {.........MWWWWWWWWWWMXXCM.XX.MMM..M},
 {.X.......MWWWWWWWWWWM...M..G.M...G.},
 {....G....MWWWWWWWWWWMCXXMX..XMM....},
 {........CMWWWWWWWWWWM....G...MM..F.}}*/


// Bitmaps pour l'affichage
SDL_Texture *pTextureBackground ; // déclaration texture de fond
SDL_Texture *pTextureCoin ; // déclaration bloc de contour
SDL_Texture *pTextureWall ;  // déclaration texture du mur
SDL_Texture *pTextureWater ;
SDL_Texture *pTextureFlagpole ;
SDL_Texture *pTextureBomb ;  // déclaration texture des points jaunes
SDL_Texture *pTexturePlant ;  // déclaration texture drapeau d'arrivée
SDL_Texture *pTextureTurtle ;
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
    int tempsjeu ; // Init du temps de jeu
    tempsjeu = compteur / 1000 ;  // Conversion en secondes

    compteur+=interval ;


    sprintf(gTitle," - Temps de jeu : %d sec ") ;// metre le temps de jeu


    return interval;
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

    pTextureMario[MOVE_LEFT]=IUTSDL_LoadTexture(sdlRenderer, "mario-gauche.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_RIGHT]=IUTSDL_LoadTexture(sdlRenderer, "mario-droite.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_UP]=IUTSDL_LoadTexture(sdlRenderer, "mario-haut.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_DOWN]=IUTSDL_LoadTexture(sdlRenderer, "mario-bas.bmp" ,0xFF,0xFF,0xFF);



    pTextureTrophy=IUTSDL_LoadTexture(sdlRenderer, "trophy.bmp" ,0xFF,0xFF,0xFF);
    pTextureBowser=IUTSDL_LoadTexture(sdlRenderer, "perdu.bmp" ,0xFF,0xFF,0xFF);

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


// Affichage contenu fixe de la grille : fond
void affichageBackground(SDL_Renderer *sdlRenderer, int i, int j)
{
    SDL_Rect rectFond ;
    rectFond.x = i*CASE_W ;
    rectFond.y = j*CASE_H ;
    rectFond.w = CASE_W ;
    rectFond.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureBackground, NULL, &rectFond);
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
    SDL_Rect rectWall ;
    rectWall.x = i*CASE_W ;
    rectWall.y = j*CASE_H ;
    rectWall.w = CASE_W ;
    rectWall.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureWall, NULL, &rectWall);
}

//Print Coins
void affichageBonus(SDL_Renderer *sdlRenderer)
{

    SDL_Rect rectCoins ;
    rectCoins.x = i*CASE_W ;
    rectCoins.y = j*CASE_H ;
    rectCoins.w = CASE_W ;
    rectCoins.h = CASE_H ;

    SDL_RenderCopy(sdlRenderer, pTextureCoin, NULL, &rectCoins);

}

//Print Flag
void affichageFlagpole(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectFlagpole ;
    rectFlagpole.x = i*CASE_W ;
    rectFlagpole.y = j*CASE_H ;
    rectFlagpole.w = CASE_W ;
    rectFlagpole.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureFlagpole, NULL, &rectFlagpole);
}

//Print Trophy
void affichageTrophy(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectTrophy;
    rectTrophy.x = 12*CASE_W ;
    rectTrophy.y = 5*CASE_H ;
    rectTrophy.w = 13*CASE_W ;
    rectTrophy.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureTrophy, NULL, &rectTrophy);
}

//Print Bowser
void affichageBowser(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectBowser;
    rectBowser.x = 5*CASE_W ;
    rectBowser.y = 5*CASE_H ;
    rectBowser.w = 8*CASE_W ;
    rectBowser.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureBowser, NULL, &rectBowser);
}

//Print Coin
void affichageCoin(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectCoin;
    rectCoin.x = 5*CASE_W ;
    rectCoin.y = 5*CASE_H ;
    rectCoin.w = 8*CASE_W ;
    rectCoin.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureCoin, NULL, &rectCoin);
}

//Print Water
void affichageWater(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectWater;
    rectWater.x = 5*CASE_W ;
    rectWater.y = 5*CASE_H ;
    rectWater.w = 8*CASE_W ;
    rectWater.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureWater, NULL, &rectWater);
}

//Print Plant
void affichagePlant(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectPlant;
    rectPlant.x = 5*CASE_W ;
    rectPlant.y = 5*CASE_H ;
    rectPlant.w = 8*CASE_W ;
    rectPlant.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTexturePlant, NULL, &rectPlant);
}

//Print Turtle
void affichageTurtle(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectTurtle;
    rectTurtle.x = 5*CASE_W ;
    rectTurtle.y = 5*CASE_H ;
    rectTurtle.w = 8*CASE_W ;
    rectTurtle.h = 8*CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureTurtle, NULL, &rectTurtle);
}





void effacerMario(SDL_Renderer *sdlRenderer, int x, int y) //effacer les traces de mario
{
    SDL_Rect rect = rectGrille[x][y] ;
    SDL_RenderCopy(sdlRenderer, pTextureBackground, NULL, &rect);

}

// Fonction d'initialisation du jeu
void init(SDL_Renderer *sdlRenderer)
{
    // Init random
    srand(time(NULL));

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

                    if (ecran[i][j] == 'F' )     // if(ecran[xMario][yMario] == 'B' ) { affichagePerdu(sldRenderer)}
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

    // Nouvelles positions pour calcul
    int x, y ;
    int sens ;
    int i, j ;
    char attente_validation;  //Pour attendre que l'utilisateur appuie sur entrée avant de lancer le jeu
    // Position Mario
    int xMario, yMario ;        // Position de Mario
    // Direction Mario
    int dirMario ;

    // Listage des regles et commandes
    printf("Bienvenue dans cette toute nouvelle experience \n\n") ;


    // 8 secondes de pause pour laisser le temps de lire
    //
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
    int points=0;


    while(!sortie)
    {
        // Affichage titre de fenetre
        SDL_SetWindowTitle(pScreen, gTitle);

        // Attendre un poil
        SDL_Delay(50) ;







        // Recup des evenements externe (clavier, souris)
        SDL_Event( event );
        while( SDL_PollEvent( &event ) != 0 )
        {
            sens = -1 ;
            switch ( event.type)
            {
            case SDL_QUIT :
                sortie = 1 ;
                break;

            case SDL_KEYDOWN :
                switch( event.key.keysym.sym )
                {


                case SDLK_ESCAPE:
                    sortie = 1;
                    break;


                    break;

                case SDLK_LEFT:
                    sens = MOVE_LEFT ;
                    break;
                case SDLK_RIGHT:
                    sens = MOVE_RIGHT ;
                    break;
                case SDLK_UP:
                    sens = MOVE_UP ;
                    break;
                case SDLK_DOWN:
                    sens = MOVE_DOWN ;
                    break;


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




            if (ecran[xMario][yMario] == 'C')   // Coins
            {
                points++;
            }



        if (ecran[xMario][yMario] == 'F') // when on 'F' end the game
        {
           sortie = 1;
        }


        affichageMario(sdlRenderer, xMario, yMario, dirMario) ;
        IUTSDL_RefreshScreen(sdlRenderer);
    }

    // Quand le temps est écoulé ou que le joueur a perdu :

    IUTSDL_ClearScreen(sdlRenderer);
    IUTSDL_RefreshScreen(sdlRenderer);


    SDL_Delay(1000);     // Pause pour laisser le temps a l'utilisateur de lire le message de fermeture

    SDL_RemoveTimer( timerID );


    printf("\n MERCI d'avoir participe a l'experience Pacman !\n Vous avez mis fin a la partie !\n ") ;


    return 0 ;

}
