 /******************************************************************************
 *
 * File Name: uart.c file
 *
 * Description: contain implementation of uart functions
 *
 *
 *******************************************************************************/



/****************************** includes ***************************************/
#include "uart.h"
/*******************************************************************************/



/***************************************************************************************************
 * [Function Name]: Sleep
 *
 * [Description]:  block for some time
 *
 * [Args]:         integer represent the no of cycles to block
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void Sleep (int n) {
    for (int i=0 ; i < n ; i++){
        for (int j=0 ; j < n/2 ; j++) {
        }
    }
}

/***************************************************************************************************
 * [Function Name]: tostring
 *
 * [Description]:  convert from integer to array of char
 *
 * [Args]:         void
 *
 * [Returns]:      int
 *
 ***************************************************************************************************/
static int tostring(char str[], int num)
{
    int i, rem, len = 0, n;
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
	return len;
}

/***************************************************************************************************
 * [Function Name]: print
 *
 * [Description]:  used to print array of char 
 *
 * [Args]:         const char*
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void print(const char*  ch){
    /* loop in all character in the array */
    while(*ch){
        UART0_CharPut( *(ch++) );
        Sleep(10);
    }
}

/***************************************************************************************************
 * [Function Name]: print_idec
 *
 * [Description]:  used to print integer value
 *
 * [Args]:         int 
 *
 * [Returns]:      int number represent the no of dighits in the integer
 *
 ***************************************************************************************************/
int print_idec(int n){
	int count=0;
    /*if it is neg number*/
	if(n<0){
		 UART0_CharPut('-');
		count++;
		n*=-1;
	}/*if it is equal zero*/
    else if(n==0){
		 UART0_CharPut('0');
		return 1;
	}
   char buff[16]; 
   count +=tostring(buff,n);
   print(buff);
   return count;
}

/***************************************************************************************************
 * [Function Name]: UART0_init
 *
 * [Description]:  initialize the uart 0 
 *
 * [Args]:         1- clock
 *                 2- baud rate
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void UART0_init(uint32_t clk, uint32_t baud_rate){

	SYSCTL_RCGCUART_R |= (1<<0);//enable uart 0
	
    SYSCTL_RCGCGPIO_R |= (1<<0);//enable port A

	GPIO_PORTA_AFSEL_R |= (1<<1) | (1<<0);//enable alternative function for PA0,PA1

	GPIO_PORTA_DEN_R |= (1<<0) | (1<<1); //digital enable for PA0,PA1

	UART0_CTL_R &= ~1; //disable uart

    int CLK = clk*1000000;
    UART0_IBRD_R = IBRD( CLK , baud_rate);
    UART0_FBRD_R = FBRD( CLK , baud_rate);

	UART0_LCRH_R = (0x3<<5); //8bit data

	UART0_CC_R = 0x0; //use system clock

	UART0_CTL_R = (1<<0) | (1<<8) | (1<<9); //uart anable + UART Transmit Enable + UART Recieve Enable
}

/***************************************************************************************************
 * [Function Name]: UART0_CharGet
 *
 * [Description]:  recieve one character
 *
 * [Args]:         void
 *
 * [Returns]:      long
 *
 ***************************************************************************************************/
long UART0_CharGet()
{
    /*wait for the flag*/
    while((*((volatile unsigned long *)(UART0_BASE + UART_O_FR))) & UART_FR_RXFE);
    
    return((*((volatile unsigned long *)(UART0_BASE + UART_O_DR))));
}

/***************************************************************************************************
 * [Function Name]: UART0_CharPut
 *
 * [Description]:  print one character
 *
 * [Args]:         char 
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void UART0_CharPut(unsigned char data)
{
    /*wait for the flag*/
    while((*((volatile unsigned long *)(UART0_BASE + UART_O_FR))) & UART_FR_TXFF);

    (*((volatile unsigned long *)(UART0_BASE + UART_O_DR))) = data;
}

