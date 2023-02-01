 /******************************************************************************
 *
 * File Name: uart.h file
 *
 * Description: contain prototypes for the uart functions
 *
 *
 *******************************************************************************/
#ifndef __UART_H__
#define __UART_H__

/****************************** includes ***************************************/
#include "MCU_DEVICE_HEADER.h"
#include<stdint.h>
/*******************************************************************************/


/******************************** Baud Rate *******************************/
#define BRD(_CLK_,_Baud_Rate_)          (int)( ( (_CLK_<<2) + (_Baud_Rate_>>1) ) /_Baud_Rate_)
#define IBRD(_CLK_,_Baud_Rate_)         (int)( (BRD(_CLK_,_Baud_Rate_)) >> 6)
#define FBRD(_CLK_,_Baud_Rate_)         (int)( (BRD(_CLK_,_Baud_Rate_)) & 0x3F)
/**************************************************************************/


/****************************** prototypes ***************************************/
extern void Sleep (int n) ;
extern void UART0_init(uint32_t clk, uint32_t baud_rate);
extern long UART0_CharGet();
extern void UART0_CharPut(unsigned char ucData);
extern int print_idec(int n);
extern void print(const char*  ch);
extern void Sleep (int n) ;
/*******************************************************************************/

#endif //  __UART_H__
