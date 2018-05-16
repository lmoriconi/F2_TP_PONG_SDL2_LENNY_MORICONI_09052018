
#ifndef WINDOW_H_INCLUDED    /** pour éviter la redondance **/

#define WINDOW_H_INCLUDED
#pragma once                /** améliore rapidité compilation **/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780
#define PADDLE_WIDTH 25
#define PADDLE_HEIGHT 150
#define BORDER_SIZE 30
#define MARGIN 50
#define Y_MAX 300
#define BALL_SPEED 5
#define PADDLE_SPEED 20
#define NB_SPAWN 2
#define SCORE_WIDTH 80
#define SCORE_HEIGHT 20
#define SCORE_MAX 10
#define NB_SCORE 2


typedef struct game{

     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_ptexture;
     SDL_Surface *g_psurface;

}game;

typedef struct gameState{

    int g_bRunning;

}gameState;

typedef struct coordonnees{

    int x;
    int y;

}coordonnees;

typedef enum Bool{
    False, True     	//False = 0, True = 1
};

typedef enum State{
    None, Up, Down      //None = 0, Up = 1, Down = 2
};


extern int init(char *title, int xpos, int ypos, int width, int height, int flags, game *myGame);
extern void destroy(game *myGame);
extern void handleEvents(gameState *state, coordonnees *dep, coordonnees *dep2);
extern void delay(unsigned int frameLimit);
extern void refresh(game *myGame);

extern void drawPaddle(game *myGame, coordonnees *dep, coordonnees *dep2, coordonnees *pos, coordonnees *pos2);
extern void drawBorder(game *myGame);
extern void drawBall(game *myGame, coordonnees *dep3);

extern void displayScore(game *myGame, int *cptPts, int *cptPts2);
extern void drawScore(game *myGame, SDL_Rect *bar, SDL_Rect *bar2, SDL_Rect *bar3, SDL_Rect *bar4, SDL_Rect *bar5, SDL_Rect *bar6, SDL_Rect *bar7, int *score);

extern void setBall(coordonnees *dep3, enum State *deviation);
extern void moveBall(game *myGame, coordonnees *dep3, coordonnees *pos3, enum Bool *movingRight, enum State *deviation);
extern void detectCollision(game *myGame, coordonnees *pos, coordonnees *pos2, coordonnees *pos3, int *cptPts, int *cptPts2, enum Bool *edgeLeft, enum Bool *edgeRight, enum Bool *movingRight, enum State *deviation);

#endif // WINDOW_H_INCLUDED
