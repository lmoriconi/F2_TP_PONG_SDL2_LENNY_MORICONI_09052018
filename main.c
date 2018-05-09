/*******************PONG*******************/

//LENNY MORICONI

//BUT : permet de jouer à Pong -> 2 raquettes se renvoient une balle et doivent atteindre un certain nombre de points en envoyant la balle en dehors des limites du terrain adverse
//ENTREE : player 1 -> up & down ; player 2 -> z & s
//SORTIE : jeu de Pong

#include "window.h"


int main(int argc, char *argv[]){

    game myGame;                                    //a game (window, renderer, texture & surface)
    gameState state;                                //the game is running or not

    unsigned int frameLimit = SDL_GetTicks() + 16;  //handle 60 fps

    enum Bool edgeLeft = False;                     //si bord gauche atteint
    enum Bool edgeRight = False;                    //si bord droit atteint
    enum Bool movingRight = True;                   //la balle va vers la droite de l'écran 
    enum Bool deviation = None;                     //la balle subit une déviation de trajectoire vers le haut de l'écran | First veut dire que c'est la première balle de la partie et qu'elle ne subit pas de déviation de trajectoire

    coordonnees dep;                                //left paddle
    coordonnees dep2;                               //right paddle
    coordonnees dep3;                               //ball

    dep.x = 0, dep.y = 0;
    dep2.x = 0, dep2.y = 0;
    dep3.x = 0, dep3.y = 0;

    //on set les coordonnees de la balle
    setBall(&dep3, &deviation);

    coordonnees pos;                                //position left paddle
    coordonnees pos2;                               //position right paddle
    coordonnees pos3;                               //position ball

    pos.x = 0, pos.y = 0;
    pos2.x = 0, pos2.y = 0;
    pos3.x = 0, pos3.y = 0;

    pos3.x = dep3.x;                                
    pos3.y = dep3.y;                                

    int cptPts = 0, cptPts2 = 0;                    //compteurs de points des joueurs 1 et 2

    state.g_bRunning = 1;                           //my game is running

    //Create texture for drawing in texture or load picture
    myGame.g_ptexture = SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    if(init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &myGame)){
        while(state.g_bRunning){

            handleEvents(&state, &dep, &dep2);

            drawBorder(&myGame);

            drawPaddle(&myGame, &dep, &dep2, &pos, &pos2);

            drawBall(&myGame, &dep3);

            moveBall(&myGame, &dep3, &pos3, &movingRight, &deviation);

            detectCollision(&myGame, &pos, &pos2, &pos3, &cptPts, &cptPts2, &edgeLeft, &edgeRight, &movingRight, &deviation);

            if(edgeLeft == True || edgeRight == True){
                setBall(&dep3, &deviation);
                pos3.x = dep3.x;
                pos3.y = dep3.y;
                edgeLeft = False;
                edgeRight = False;
            }

            if(cptPts == SCORE_MAX || cptPts2 == SCORE_MAX){
                
                state.g_bRunning = 0;                           //my game stops running
                system("cls");
                printf("GAME OVER\n\n");

                if(cptPts == SCORE_MAX)
                    printf("Player 1 won !\n\n");
                else
                    printf("Player 2 won !\n\n");

                printf("Thank you for playing !\n\n");
                printf("CREDITS : Lenny Moriconi\n\n");
                printf("2018\n\n");
                
                //destroy each component of myGame
                destroy(&myGame);

                //clean up all initialized subsystems
                SDL_Quit();

                return 0;                                       //FINPROGRAMME
            }

            displayScore(&myGame, &cptPts, &cptPts2);

            refresh(&myGame);

            //handle 60 fps (1000ms/60 = 16.6 -> 16)
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;
        }
    }
}
