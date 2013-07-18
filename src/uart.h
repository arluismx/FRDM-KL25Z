#ifndef __UART_H__
#define __UART_H__
/*******************************************************************************
 * \brief		FRDM-KL25Z UART functions.
 *
 * \file		uart.h
 * \version		1.0
 * \date		2013-02-21
 * \author		rct1
 ******************************************************************************/
/*
 * functions global:
 *				UART_init
 *				UART_sendchar
 *				UART_receivechar
 *				UART_sendstring
 *				UART_receivestring
 * functions local:
 *				.
 *
 ******************************************************************************/

/*----- Header-Files -------------------------------------------------------*/
#include <MKL25Z4.H>

/*----- Macros -------------------------------------------------------------*/

/*----- Data types ---------------------------------------------------------*/

/*----- Function prototypes ------------------------------------------------*/
extern void UART_init(void *UARTx, uint32_t Baud);
extern void UART_sendchar(void *UARTx, char c);
extern char UART_receivechar(void *UARTx);
extern void UART_sendstring(void *UARTx, char *pc);
extern uint8_t UART_receivestring(void *UARTx, char *pc);

/*----- Data ---------------------------------------------------------------*/

#endif /* __UART_H__ */
