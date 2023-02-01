 /******************************************************************************
 *
 * File Name: snake_game.h file
 *
 * Description: contain prototypes for the tasks
 *
 *
 *******************************************************************************/
#ifndef _SNAKE_H_
#define _SNAKE_H_

/****************************** includes ***************************************/
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
/*******************************************************************************/


/****************************** extern variables ***************************************/
/* variable to define the max score of the level*/
extern int levelMAXScore ;
/* variable to define the level score when to show the enemy*/
extern int score_To_show_enemy ;
/* mutex to solve Solve the concurrency issues */
extern xSemaphoreHandle xMutex;
/* flag for define if the game over or not */
extern char gameOver;
/* width and height of map */
extern const int width , height ;
/* x,y position of snake */
extern int x_pos, y_pos;
/* x,y position of fruit */
extern int fruitX, fruitY;
/* current level score */
extern int score;
/* current level*/
extern int level;
/*total score (sum scores of level scores)*/
extern int totalScore;
/* flag for define if the game finished or not */
extern int finished;
/* x,y position of Enemy */
extern int EnemyX, EnemyY;
/* data storage to store snake*/
extern int SnakeX[100], SnakeY[100];
/* lenth of snake*/
extern int sankeLength;
/* current snake direction */
extern enum eDirecton sankeDirection;
/*********************************************************************************/

/****************************** prototypes ***************************************/
void Logic(void *pvParameters);
void Input(void *pvParameters);
void Draw(void *pvParameters);
void Setup();
/*********************************************************************************/

#endif