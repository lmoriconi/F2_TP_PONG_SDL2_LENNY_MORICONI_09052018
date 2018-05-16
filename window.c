#include "window.h"


int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame){
//BUT : Initialize the screen

    myGame->g_pWindow = NULL;
    myGame->g_pRenderer = NULL;
    myGame->g_psurface = NULL;
    myGame->g_ptexture = NULL;

    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0){
        //if succeeded create our window
        myGame->g_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        //if succeeded create window, create our render
        if(myGame->g_pWindow != NULL)
            myGame->g_pRenderer = SDL_CreateRenderer(myGame->g_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    }else
        return 0;

    return 1;
}

void drawPaddle(game *myGame, coordonnees *dep, coordonnees *dep2, coordonnees *pos, coordonnees *pos2){
//BUT : Draw the two paddles

   //Update left paddle
    SDL_Rect leftPaddle;
    leftPaddle.x = MARGIN + dep->x;                                        //debut x
    leftPaddle.y = SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2 + dep->y;             //debut y
    leftPaddle.w = PADDLE_WIDTH;                                           //Largeur
    leftPaddle.h = PADDLE_HEIGHT;                                          //Hauteur

    //Update coord
    pos->x = leftPaddle.x;
    pos->y = leftPaddle.y;

    //Update right paddle
    SDL_Rect rightPaddle;
    rightPaddle.x = SCREEN_WIDTH - MARGIN - PADDLE_WIDTH + dep2->x;        //debut x
    rightPaddle.y = SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2 + dep2->y;           //debut y
    rightPaddle.w = PADDLE_WIDTH;                                          //Largeur
    rightPaddle.h = PADDLE_HEIGHT;                                         //Hauteur

    //Update coord
    pos2->x = rightPaddle.x;
    pos2->y = rightPaddle.y;

    //Draw in texture
    SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(myGame->g_pRenderer, &leftPaddle);
    SDL_RenderFillRect(myGame->g_pRenderer, &rightPaddle);

    //update le rendu

    SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void drawBorder(game *myGame){
//BUT : Draw the borders of the game field

    //Init upper line
    SDL_Rect upperLine;
    upperLine.x = 0;                                //debut x
    upperLine.y = 0;                                //debut y
    upperLine.w = SCREEN_WIDTH;                     //Largeur
    upperLine.h = BORDER_SIZE;                      //Hauteur

    //Init lower line
    SDL_Rect lowerLine;
    lowerLine.x = 0;                                //debut x
    lowerLine.y = SCREEN_HEIGHT - BORDER_SIZE;      //debut y
    lowerLine.w = SCREEN_WIDTH;                     //Largeur
    lowerLine.h = BORDER_SIZE;                      //Hauteur

    //Init middle line
    SDL_Rect middleLine;
    middleLine.x = SCREEN_WIDTH/2;                  //debut x
    middleLine.y = BORDER_SIZE;                     //debut y
    middleLine.w = BORDER_SIZE;                     //Largeur
    middleLine.h = SCREEN_HEIGHT;                   //Hauteur


    //Draw in texture
    SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(myGame->g_pRenderer, &upperLine);
    SDL_RenderFillRect(myGame->g_pRenderer, &lowerLine);
    SDL_RenderFillRect(myGame->g_pRenderer, &middleLine);

    //update renderer

    SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void drawBall(game *myGame, coordonnees *dep3){
//BUT : Draw the ball

    SDL_Rect ball;

    ball.x = dep3->x;                                        //debut x
    ball.y = dep3->y;                                        //debut y
    ball.w = BORDER_SIZE;                                    //Largeur
    ball.h = BORDER_SIZE;                                    //Hauteur

    //Draw in texture
    SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(myGame->g_pRenderer, &ball);

    //update renderer

    SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

}

void displayScore(game *myGame, int *cptPts, int *cptPts2){
//BUT : Init rectangles' values and call drawing method to display the score

    int i = 0;

    //variables pour placer le score à l'écran
    int div = 0;
    int dif = 0;
    int dif2 = 0;
    int multi = 0;

    for(i=0; i<NB_SCORE; i++){

        switch(i){
            case 0 :    div = 4;
                        multi = 1;
                        dif = 0;
                        dif2 = 0;
            break;                                                                                      //afin que le score soit à gauche de l'écran
            case 1 :    div = 2;
                        multi = 2;
                        dif = SCORE_WIDTH * 3;
                        dif2 = SCORE_HEIGHT + SCORE_HEIGHT/2;
            break;                                                                                      //afin que le score soit à droite de l'écran
        }

        SDL_Rect bar = {
                            (SCREEN_WIDTH/div - SCORE_WIDTH/2) * multi - dif,                           //x
                            BORDER_SIZE*2,                                                              //y
                            SCORE_WIDTH,                                                                //w
                            SCORE_HEIGHT                                                                //h
                        };

        SDL_Rect bar2 = {
                            (SCREEN_WIDTH/div + SCORE_WIDTH/2 - SCORE_HEIGHT - dif2) * multi - dif,     //x
                            SCORE_WIDTH/2 + SCORE_HEIGHT,                                               //y
                            SCORE_WIDTH/4,                                                              //w
                            SCORE_HEIGHT*2                                                              //h
                        };

        SDL_Rect bar3 = {
                            (SCREEN_WIDTH/div + SCORE_WIDTH/2 - SCORE_HEIGHT - dif2) * multi - dif,     //x
                            SCORE_WIDTH + SCORE_HEIGHT,                                                 //y
                            SCORE_WIDTH/4,                                                              //w
                            SCORE_HEIGHT*2                                                              //h
                        };

        SDL_Rect bar4 = {
                            (SCREEN_WIDTH/div - SCORE_WIDTH/2) * multi - dif,                           //x
                            BORDER_SIZE*2 + SCORE_HEIGHT*4,                                             //y
                            SCORE_WIDTH,                                                                //w
                            SCORE_HEIGHT                                                                //h
                        };

        SDL_Rect bar5 = {
                            (SCREEN_WIDTH/div - SCORE_WIDTH/2) * multi - dif,                           //x
                            SCORE_WIDTH + SCORE_HEIGHT,                                                 //y
                            SCORE_WIDTH/4,                                                              //w
                            SCORE_HEIGHT*2                                                              //h
                        };

        SDL_Rect bar6 = {
                            (SCREEN_WIDTH/div - SCORE_WIDTH/2) * multi - dif,                           //x
                            SCORE_WIDTH/2 + SCORE_HEIGHT,                                               //y
                            SCORE_WIDTH/4,                                                              //w
                            SCORE_HEIGHT*2                                                              //h
                        };

        SDL_Rect bar7 = {
                            (SCREEN_WIDTH/div - SCORE_WIDTH/2) * multi - dif,                            //x
                            BORDER_SIZE*2 + SCORE_HEIGHT*2,                                              //y
                            SCORE_WIDTH,                                                                 //w
                            SCORE_HEIGHT                                                                 //h
                        };
        switch(i){
            case 0 : drawScore(myGame, &bar, &bar2, &bar3, &bar4, &bar5, &bar6, &bar7, cptPts); break;
            case 1 : drawScore(myGame, &bar, &bar2, &bar3, &bar4, &bar5, &bar6, &bar7, cptPts2); break;
        }
    }

}

void drawScore(game *myGame, SDL_Rect *bar, SDL_Rect *bar2, SDL_Rect *bar3, SDL_Rect *bar4, SDL_Rect *bar5, SDL_Rect *bar6, SDL_Rect *bar7, int *score){
//BUT : Display the score

    //Draw in texture
    SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    switch(*score){

        case 1 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar2);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
        break;

        case 2 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar2);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar4);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar5);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar7);
        break;

        case 3 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar2);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar4);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar7);
        break;

        case 4 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar2);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar6);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar7);
        break;

        case 5 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar4);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar6);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar7);
        break;

        case 6 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar4);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar5);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar6);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar7);
        break;

        case 7 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar2);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
        break;

        case 8 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar2);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar4);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar5);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar6);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar7);
        break;

        case 9 :
                    SDL_RenderFillRect(myGame->g_pRenderer, bar);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar2);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar4);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar6);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar7);
        break;

        default :                                                           //cas du zéro
                    SDL_RenderFillRect(myGame->g_pRenderer, bar);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar2);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar3);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar4);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar5);
                    SDL_RenderFillRect(myGame->g_pRenderer, bar6);
        break;
    }

    //update renderer

    SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

}

void setBall(coordonnees *dep3, enum State *deviation){
//BUT : Set all ball's values

    //array of integer for the two ballSpawns Y values
    int ballSpawn[NB_SPAWN] = {SCREEN_HEIGHT/4, SCREEN_HEIGHT-SCREEN_HEIGHT/4};

    srand(time(NULL));

    //Init ball
    dep3->x = SCREEN_WIDTH/2;                                 //debut x
    dep3->y = ballSpawn[rand() % NB_SPAWN];                   //debut y

    *deviation = None;                                        //on réinitialise la deviation sur None

}

void moveBall(game *myGame, coordonnees *dep3, coordonnees *pos3, enum Bool *movingRight, enum State *deviation){
//BUT : Make the ball move

    if(*movingRight == True){
        if(dep3->x < SCREEN_WIDTH-BORDER_SIZE){
            dep3->x += BALL_SPEED;
            pos3->x = dep3->x;
            if(*deviation == Up){
                dep3->y -= BALL_SPEED;
                pos3->y = dep3->y;
            }
            else if(*deviation == Down){
                dep3->y += BALL_SPEED;
                pos3->y = dep3->y;
            }
        }
    }
    else{
        if(dep3->x > BORDER_SIZE){
            dep3->x -= BALL_SPEED;
            pos3->x = dep3->x;
            if(*deviation == Up){
                dep3->y -= BALL_SPEED;
                pos3->y = dep3->y;
            }
            else if(*deviation == Down){
                dep3->y += BALL_SPEED;
                pos3->y = dep3->y;
            }
        }
    }

}

void detectCollision(game *myGame, coordonnees *pos, coordonnees *pos2, coordonnees *pos3, int *cptPts, int *cptPts2, enum Bool *edgeLeft, enum Bool *edgeRight, enum Bool *movingRight, enum State *deviation){
//BUT : Detect collisions between ball and paddles or edge

    //si la balle a touché la raquette de gauche
    if(pos3->x <= pos->x + PADDLE_WIDTH && pos3->x > pos->x && pos3->y + BORDER_SIZE >= pos->y && pos3->y < pos->y + PADDLE_HEIGHT){
        printf("Collison left paddle\n");

        *movingRight = True;

        if(pos3->y + BORDER_SIZE <= pos->y + PADDLE_HEIGHT/2)
            *deviation = Up;
        else
            *deviation = Down;

        printf("deviation = %d\n", *deviation);

    }
    //si la balle a touché la raquette de droite
    else if(pos3->x + BORDER_SIZE >= pos2->x && pos3->x + BORDER_SIZE < pos2->x + PADDLE_WIDTH && pos3->y + BORDER_SIZE >= pos2->y && pos3->y < pos2->y + PADDLE_HEIGHT){
        printf("Collison right paddle\n");

        *movingRight = False;

        if(pos3->y + BORDER_SIZE <= pos2->y + PADDLE_HEIGHT/2)
            *deviation = Up;
        else
            *deviation = Down;

        printf("deviation = %d\n", *deviation);

    }
    //si la balle atteint le bord gauche de l'écran
    else if(pos3->x <= BORDER_SIZE){
        *edgeLeft = True;
        *cptPts2 += 1;
        *movingRight = False;
    }
    //si la balle atteint le bord droit de l'écran
    else if(pos3->x >= SCREEN_WIDTH-BORDER_SIZE){
        *edgeRight = True;
        *cptPts += 1;
        *movingRight = True;
    }
    //si la balle atteint le bord inférieur de l'écran
    else if(pos3->y + BORDER_SIZE >= SCREEN_HEIGHT - BORDER_SIZE){
        if(*deviation == Up)
            *deviation = Down;
        else if(*deviation == Down)
            *deviation = Up;
    }
    //si la balle atteint le bord supérieur de l'écran
    else if(pos3->y <= BORDER_SIZE){
        if(*deviation == Up)
            *deviation = Down;
        else if(*deviation == Down)
            *deviation = Up;
    }
}

void destroy(game *myGame){
//BUT : Destroy my game

    //Destroy render
    if(myGame->g_pRenderer != NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);

    //Destroy texture
    if(myGame->g_ptexture != NULL)
        SDL_DestroyTexture(myGame->g_ptexture);

    //Destroy surface
    if(myGame->g_psurface != NULL)
        SDL_FreeSurface(myGame->g_psurface);

    //Destroy window
    if(myGame->g_pWindow != NULL)
        SDL_DestroyWindow(myGame->g_pWindow);
}

void handleEvents(gameState *state, coordonnees *dep, coordonnees *dep2){
//BUT : gerer les inputs utilisateurs

    SDL_Event event;

    //s'il y a un événement en attente
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT :
                  state -> g_bRunning = 0; break;                                //on quitte le jeu
            case SDL_KEYDOWN :
                            switch(event.key.keysym.sym){                        //on modifie les coordonnees en testant les limites du terrain
                                    //PLAYER 1
                                    case SDLK_UP :
                                                    if(dep->y > - Y_MAX + PADDLE_SPEED)
                                                        dep->y -= PADDLE_SPEED;
                                    break;
                                    case SDLK_DOWN :
                                                    if(dep->y < Y_MAX - PADDLE_SPEED)
                                                        dep->y += PADDLE_SPEED;
                                    break;
                                    //PLAYER 2
                                    case SDLK_z :
                                                    if(dep2->y > - Y_MAX + PADDLE_SPEED)
                                                        dep2->y -= PADDLE_SPEED;
                                    break;
                                    case SDLK_s :
                                                    if(dep2->y < Y_MAX - PADDLE_SPEED)
                                                        dep2->y += PADDLE_SPEED;
                                    break;
                            }break;

            case SDL_KEYUP : default : break;
        }
    }
}

void delay(unsigned int frameLimit){
//BUT : Gestion des 60 fps (images/seconde)

    unsigned int ticks = SDL_GetTicks();

    if(frameLimit < ticks)
        return;

    if (frameLimit > ticks + 16)
        SDL_Delay(16);
    else
        SDL_Delay(frameLimit - ticks);
}

void refresh(game *myGame){

    SDL_RenderPresent(myGame->g_pRenderer);
    SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(myGame->g_pRenderer);
    SDL_DestroyTexture(myGame->g_ptexture);
}
