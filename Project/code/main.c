 /******************************************************************************
 *
 * File Name: main.c file
 *
 * Description: this the main file where start of program
 *
 *
 *******************************************************************************/


/****************************** includes ***************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "MCU_DEVICE_HEADER.h"
#include "uart.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "snake_game.h"
#include <stdint.h>
/*******************************************************************************/


/****************************** prototypes ***************************************/
static void prvSetupHardware( void );
static void startWindow(void);
/*******************************************************************************/


/***************************************************************************************************
 * [Function Name]: main
 *
 * [Description]:  Main Function of the program
 *
 * [Args]:         void
 *
 * [Returns]:      int
 *
 ***************************************************************************************************/
int main( void )
{
    /*initialization*/
    prvSetupHardware();
    Setup();
    startWindow();

    xMutex = xSemaphoreCreateMutex();
    if( xMutex != NULL )
	{
        /* creating app tasks*/
        xTaskCreate( Draw, "Draw", configMINIMAL_STACK_SIZE, NULL, 1 , NULL );
        xTaskCreate( Input, "Input", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
        xTaskCreate( Logic, "Logic", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

        /* Start the scheduler. */
        vTaskStartScheduler();
    }
    for(;;);
}

/***************************************************************************************************
 * [Function Name]: prvSetupHardware
 *
 * [Description]:  setup hardware for our app
 *
 * [Args]:         void
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
static void prvSetupHardware( void )
{
    UART0_init(16,9600);
}

/***************************************************************************************************
 * [Function Name]: startWindow
 *
 * [Description]:  show the welcome window to the player
 *
 * [Args]:         void
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void startWindow(void){
    print("\e[1;1H\e[2J"); 
    print("                                  *************************\n");
    print("                                  WELCOME TO OUR SNAKE GAME\n");
    print("                                  *************************\n");
    print("\n\n");
    print("KEYS CONTROLS: \n");
    print("              a: move LEFT\n");
    print("              d: move RIGHT\n");
    print("              w: move UP\n");
    print("              s: move DOWN\n");
    print("              x: game over\n");
    print("RULES: \n");
    print("      - eat the Fruit # to grow\n");
    print("      - avoid the Enemy E to not lose \n");
    print("      - you can only move in the reverse direction if the lenth of the snake <= 2 \n");
    print("      - enemy E show when your score is 30 at each level \n");
    print("      - you have only 3 Levels \n");
    print("      - max score at every level is 50  \n");
    print("      - speed increase after each level  \n");
    print("\n\n");
    Sleep(80000);
}



