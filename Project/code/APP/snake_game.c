 /******************************************************************************
 *
 * File Name: snake_game.c file
 *
 * Description: contatin the implementation of tasks
 *
 *
 *******************************************************************************/


/****************************** includes ***************************************/
#include "snake_game.h"
#include "uart.h"
#include <stdlib.h>
#include "MCU_DEVICE_HEADER.h"
/*******************************************************************************/


/****************************** global variables ***************************************/
/* variable to define the max score of the level*/
int levelMAXScore = 50;
/* variable to define the level score when to show the enemy*/
int score_To_show_enemy =30;
/* mutex to solve Solve the concurrency issues */
xSemaphoreHandle xMutex;
/* flag for define if the game over or not */
char gameOver;
/* width and height of map */
const int width = 50; const int height = 20;
/* x,y position of snake */
int x_pos, y_pos;
/* x,y position of fruit */
int fruitX, fruitY;
/* current level score */
int score;
/* current level*/
int level;
/*total score (sum scores of level scores)*/
int totalScore;
/* flag for define if the game finished or not */
int finished;
/* x,y position of Enemy */
int EnemyX, EnemyY;
/* data storage to store snake*/
int SnakeX[100], SnakeY[100];
/* lenth of snake*/
int sankeLength;
/* enum to define the avialable directions */
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
/* current snake direction */
enum eDirecton sankeDirection;
/*******************************************************************************/


/****************************** static variables *******************************/
static unsigned int seed = 1;
/*******************************************************************************/


/***************************************************************************************************
 * [Function Name]: randd
 *
 * [Description]:  generate random integer
 *
 * [Args]:         void
 *
 * [Returns]:      int
 *
 ***************************************************************************************************/
int randd (void) {
    seed = (seed * 1103515245U + 12345U) & 0x7fffffffU;
    return (int)seed;
}

/***************************************************************************************************
 * [Function Name]: Setup
 *
 * [Description]:  setup and init the variables used by tasks
 *
 * [Args]:         void
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void Setup()
{
    gameOver = 0;
    sankeDirection = STOP;
    x_pos = width / 2;
    y_pos = height / 2;
    /*generate random positions for fruit and enemy*/
    fruitX = randd() % width;
    fruitY = randd() % height;
    EnemyX = randd() % width;
    EnemyY = randd() % height;
    score = 0;
    level=0;
    totalScore=0;
    finished=0;
    sankeLength=0;
}

/***************************************************************************************************
 * [Function Name]: Continue
 *
 * [Description]:  ask the player if he want to continu to play another game or not
 *
 * [Args]:         void
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
static void Continue(){
    print("\nto Continue,press y/Y  \n");
    /*receive answer from user*/
    char input = UART0_CharGet();
    if(input =='y' || input =='Y' ){
        /*to start again*/
        Setup();
    }
    else{
        /*don't do any thing*/
    }
}

/***************************************************************************************************
 * [Function Name]: Draw
 *
 * [Description]:  responsible for drawing
 *
 * [Args]:         void *
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void Draw(void *pvParameters)
{
    
    for(;;){
        /*Solve the concurrency issues*/
        xSemaphoreTake( xMutex, portMAX_DELAY );
        if(gameOver ==1 ){
            /*for make screen fixed*/
            print("\e[1;1H\e[2J");  
            print("\n Game Over\n"); 
            /* increase priority to not allow other tasks to execute while asking player*/ 
            vTaskPrioritySet(NULL,2);
            Continue();
            vTaskPrioritySet(NULL,1);
            /* return to default priority to return to the same flow before gamover*/ 
            
        }else if(finished ==0){
            /*for make screen fixed*/
            print("\e[1;1H\e[2J");  
            /*print upper boundary*/
            for (int i = 0; i < width+2; i++){
                print("-");
            }
            print("\n");

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (j == 0){
                        /*draw left boundary*/
                        print("|");
                    }
                    if (i == y_pos && j == x_pos){
                        /*draw head snake */
                        print("*");
                    }
                    else if(score==score_To_show_enemy && i == EnemyY && j == EnemyX ){
                        /*draw enemy*/
                            print("E");   
                    }
                    else if (i == fruitY && j == fruitX){
                        /*draw fruit*/
                        print("#");                       
                    }
                    else
                    {
                        char p = 0;
                        for (int k = 0; k < sankeLength; k++)
                        {
                            if (SnakeX[k] == j && SnakeY[k] == i)
                            {
                                /*draw snake body */
                                print("*");
                                p = 1;
                            }
                        }
                        if (!p){
                            print(" ");
                        }
                    }
                    if (j == width - 1){
                        /*draw left boundary*/
                        print("|");
                    }
                }
                print("\n");
            }
            /*print down boundary*/
            for (int i = 0; i < width+2; i++){
                print("-");
            }
            /*draw states of game*/
            print("\n");
            print("Score: ");
            print_idec(score);
            print("\n");
            print("Level: ");
            print_idec(level);
            print("\n");
            print("Total Score: ");
            print_idec(totalScore);
            print("\r\n");

            /*checking if the game finished or can increase player level*/
            if(score==levelMAXScore ){
                if(level==2){
                    finished=1;
                }else{
                    level++;
                    score=0;
                }
            }
        }else if(finished ==1){
                    /*for make screen fixed*/
                    print("\e[1;1H\e[2J");  
                    /*Congratulations*/
                    print("\n Congratulations, you are a hero\n"); 
                    /* increase priority to not allow other tasks to execute while asking player*/ 
                    vTaskPrioritySet(NULL,2);
                    Continue();
                    vTaskPrioritySet(NULL,1);
                    /* return to default priority to return to the same flow before Congratulations*/ 
                   
        }
        xSemaphoreGive( xMutex );
        vTaskDelay(200-level*75);
    }
}

/***************************************************************************************************
 * [Function Name]: Input
 *
 * [Description]:  responsible for taking input from user
 *
 * [Args]:         void *
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void Input(void *pvParameters)
{
    for(;;){
        /*take user interactions*/
        char c = UART0_CharGet();
        /*change direction */
        switch (c)
        {
        case 'a':
            sankeDirection = LEFT;
            break;
        case 'd':
            sankeDirection = RIGHT;
            break;
        case 'w':
            sankeDirection = UP;
            break;
        case 's':
            sankeDirection = DOWN;
            break;
        case 'x':
            gameOver = 1;
            break;
        }

        vTaskDelay(200-level*75);
    }   
}

/***************************************************************************************************
 * [Function Name]: Logic
 *
 * [Description]:  responsible for logic and control of the game (mind)
 *
 * [Args]:         void *
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void Logic(void *pvParameters)
{
    for(;;){
         /*Solve the concurrency issues*/
        xSemaphoreTake( xMutex, portMAX_DELAY );
        int prevX = SnakeX[0];
        int prevY = SnakeY[0];
        int prev2X, prev2Y;
        SnakeX[0] = x_pos;
        SnakeY[0] = y_pos;
        for (int i = 1; i < sankeLength; i++)
        {
            prev2X = SnakeX[i];
            prev2Y = SnakeY[i];
            SnakeX[i] = prevX;
            SnakeY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        switch (sankeDirection)
        {
        case LEFT:
            x_pos--;
            break;
        case RIGHT:
            x_pos++;
            break;
        case UP:
            y_pos--;
            break;
        case DOWN:
            y_pos++;
            break;
        default:
            break;
        }
        if (x_pos > width-1 || x_pos < 0 || y_pos > height-1 || y_pos < 0){
            /*gameover if it hit the boundary*/
            gameOver = 1;
        }
    
        for (int i = 0; i < sankeLength; i++){
            if (SnakeX[i] == x_pos && SnakeY[i] == y_pos){
                /*gameover if it eat yoursel*/
                gameOver = 1;
            }
        }
    
        if (x_pos == fruitX && y_pos == fruitY)
        {
            /*increase score if eat fruit*/
            score += 10;
            totalScore+=10;
            /*generate random positions for fruit and enemy*/
            fruitX = randd() % width;
            fruitY = randd() % height;
            EnemyX = randd() % width;
            EnemyY = randd() % height;
            /*increase snake lenth*/
            sankeLength++;
        }else if(score ==score_To_show_enemy && x_pos == EnemyX && y_pos == EnemyY){
            /*if eat enemy--> gamover*/
            gameOver = 1;
        }
        xSemaphoreGive( xMutex );
        vTaskDelay(200-level*75);
    }
}


