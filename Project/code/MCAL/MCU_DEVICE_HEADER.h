 /******************************************************************************
 *
 * File Name: MCU_DEVICE_HEADER.h file
 *
 * Description: contain addresses and registers 
 *
 *
 *******************************************************************************/
#ifndef __MCU_DEVICE_HEADER_H_
#define __MCU_DEVICE_HEADER_H_


#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_RCGCUART_R       (*((volatile uint32_t *)0x400FE618))
#define GPIO_PORTA_AFSEL_R      (*((volatile uint32_t *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile uint32_t *)0x4000451C))
#define UART0_LCRH_R            (*((volatile uint32_t *)0x4000C02C))
#define UART0_CC_R              (*((volatile uint32_t *)0x4000CFC8))
#define UART0_CTL_R             (*((volatile uint32_t *)0x4000C030))
#define UART0_IBRD_R            (*((volatile uint32_t *)0x4000C024))
#define UART0_FBRD_R            (*((volatile uint32_t *)0x4000C028))

#define UART_O_DR               0x00000000  // Data Register
#define UART_O_FR               0x00000018  // Flag Register (read only)
#define UART_FR_TXFE            0x00000080  // TX FIFO Empty
#define UART_FR_RXFF            0x00000040  // RX FIFO Full
#define UART_FR_TXFF            0x00000020  // TX FIFO Full
#define UART_FR_RXFE            0x00000010  // RX FIFO Empty
#define UART_FR_BUSY            0x00000008  // UART Busy

#define GPIO_PORTA_BASE         0x40004000  // GPIO Port A
#define GPIO_PORTB_BASE         0x40005000  // GPIO Port B
#define GPIO_PORTC_BASE         0x40006000  // GPIO Port C
#define GPIO_PORTD_BASE         0x40007000  // GPIO Port D
#define SSI_BASE                0x40008000  // SSI
#define UART0_BASE              0x4000C000  // UART0
#define UART1_BASE              0x4000D000  // UART1
#define I2C_MASTER_BASE         0x40020000  // I2C Master
#define I2C_SLAVE_BASE          0x40020800  // I2C Slave
#define GPIO_PORTE_BASE         0x40024000  // GPIO Port E
#define PWM_BASE                0x40028000  // PWM
#define QEI_BASE                0x4002C000  // QEI
#define TIMER0_BASE             0x40030000  // Timer0
#define TIMER1_BASE             0x40031000  // Timer1
#define TIMER2_BASE             0x40032000  // Timer2
#define ADC_BASE                0x40038000  // ADC
#define COMP_BASE               0x4003C000  // Analog comparators
#define FLASH_CTRL_BASE         0x400FD000  // FLASH Controller
#define SYSCTL_BASE             0x400FE000  // System Control
#define ITM_BASE                0xE0000000  // Instrumentation Trace Macrocell
#define DWT_BASE                0xE0001000  // Data Watchpoint and Trace
#define FPB_BASE                0xE0002000  // FLASH Patch and Breakpoint
#define NVIC_BASE               0xE000E000  // Nested Vectored Interrupt Ctrl
#define TPIU_BASE               0xE0040000  // Trace Port Interface Unit





#endif