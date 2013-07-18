/*******************************************************************************
 * \brief		FRDM-KL25Z UART functions.
 *
 * \file		uart.c
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
#include "uart.h"

/*----- Macros -------------------------------------------------------------*/

/*----- Data types ---------------------------------------------------------*/
typedef struct _PORT_PIN_t {
	PORT_Type *PORTx;
	uint8_t Bit;
	uint32_t Alt;
} PORT_PIN_t;

/*----- Function prototypes ------------------------------------------------*/

/*----- Data ---------------------------------------------------------------*/
PORT_PIN_t UART_Port_Pin[] = {
        { PORTA, 1, PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x2) },
        { PORTA, 2, PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x2) }
};

/*----- Implementation -----------------------------------------------------*/
/**
 *****************************************************************************
 * \fn			UART_init
 * \brief		Configure a UART to the specific baud rate and 8n1.
 *
 * \param [in]	UARTx	The UART port which will be used. Possible values are
 *						UART0, UART1 and UART2.
 * \param [in]	Baud	Selected baud rate in Hz.
 * \return		None
 *****************************************************************************
 */
void UART_init(void *UARTx, uint32_t Baud) {
	uint16_t tmp;

	if ((UARTLP_Type *) UARTx == UART0) {
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;			/* Enable GPIOA clock	*/
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;			/* Enable UART0 clock	*/

		/* Configure the GPIOs */
		UART_Port_Pin[0].PORTx->PCR[UART_Port_Pin[0].Bit] =
		        UART_Port_Pin[0].Alt;
		UART_Port_Pin[1].PORTx->PCR[UART_Port_Pin[1].Bit] =
		        UART_Port_Pin[1].Alt;

		/**
		 * Configuration register C1:
		 *	- Nothing
		 * Configuration register C2:
		 *	- Enable transmitter
		 *	- Enable receiver
		 * Configuration register C3:
		 *	- Nothing
		 * Configuration register C4:
		 *	- Nothing
		 * Configuration register C5:
		 *	- Nothing
		 * Clock source for UART0:
		 *	- MCGFLLCLK
		 */
		((UARTLP_Type *) UARTx)->C1 = 0x00;
		((UARTLP_Type *) UARTx)->C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;
		((UARTLP_Type *) UARTx)->C3 = 0x00;
		((UARTLP_Type *) UARTx)->C4 = 0x00;
		((UARTLP_Type *) UARTx)->C5 = 0x00;
		SIM->SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK);	/* MCGFLLCLK			*/
		SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);		/* Using MCGFLLPLL		*/

		tmp = SystemCoreClock / Baud;
		((UARTLP_Type *) UARTx)->BDH &= ~UARTLP_BDH_SBR_MASK;
		((UARTLP_Type *) UARTx)->BDH |= UARTLP_BDH_SBR(tmp);
		((UARTLP_Type *) UARTx)->BDL &= ~UARTLP_BDL_SBR_MASK;
		((UARTLP_Type *) UARTx)->BDL |= UARTLP_BDL_SBR(tmp);
	}
}

/**
 *****************************************************************************
 * \fn			UART_sendchar
 * \brief		Send a char to a uart port.
 *
 * \param [in]	UARTx	The UART port which will be used. Possible values are
 *						UART0, UART1 and UART2.
 * \param [in]	c		Character to send.
 * \return		None
 *****************************************************************************
 */
void UART_sendchar(void *UARTx, char c) {
	if ((UARTLP_Type *) UARTx == UART0) {
		/* Check if transmit data register is empty */
		while (((UARTLP_Type *) UARTx)->S1 & UARTLP_S1_TDRE_MASK)
			;
		/* Send the data */
		((UARTLP_Type *) UARTx)->D = c;
	}
	else {
		/* Check if transmit data register is empty */
		while (((UART_Type *) UARTx)->S1 & UARTLP_S1_TDRE_MASK)
			;
		/* Send the data */
		((UART_Type *) UARTx)->D = c;
	}
}

/**
 *****************************************************************************
 * \fn			UART_receivechar
 * \brief		Receive a char from a uart port.
 *
 * \param [in]	UARTx	The UART port which will be used. Possible values are
 *						UART0, UART1 and UART2.
 * \return		Received character.
 *****************************************************************************
 */
char UART_receivechar(void *UARTx) {
	char c;

	if ((UARTLP_Type *) UARTx == UART0) {
		/* Wait while receive data register is empty */
		while ((((UARTLP_Type *) UARTx)->S1 & UARTLP_S1_RDRF_MASK) == 0)
			;
		/* receive the data */
		c = ((UARTLP_Type *) UARTx)->D;
	}
	else {
		/* Wait while receive data register is empty */
		while ((((UART_Type *) UARTx)->S1 & UARTLP_S1_RDRF_MASK) == 0)
			;
		/* receive the data */
		c = ((UART_Type *) UARTx)->D;
	}

	return c;
}

/**
 *****************************************************************************
 * \fn			UART_sendstring
 * \brief		Send a string to a uart port. This function sends chars
 *				until a \0 is received.
 *
 * \param [in]	UARTx	The UART port which will be used. Possible values are
 *						UART0, UART1 and UART2.
 * \param [in]	pc		Pointer to the buffer to read the string from.
 * \return		None
 *****************************************************************************
 */
void UART_sendstring(void *UARTx, char *pc) {
	while (*pc != '\0') {
		UART_sendchar(UARTx, *pc);
		pc++;
	}
}

/**
 *****************************************************************************
 * \fn			UART_receivestring
 * \brief		Receive a string from a uart port. This function read chars
 *				until a \0 is received.
 *
 * \param [in]	UARTx	The UART port which will be used. Possible values are
 *						UART0, UART1 and UART2.
 * \param [out]	pc		Pointer to the buffer to write the string into.
 * \return		Number of characters are received.
 *****************************************************************************
 */
uint8_t UART_receivestring(void *UARTx, char *pc) {
	uint8_t num = 0;

	do {
		*pc = UART_receivechar(UARTx);
		pc++;
		num++;
	} while (*(pc - 1) != '\0');

	return num;
}
