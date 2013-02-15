/*******************************************************************************
 * \brief		FRDM-KL25Z blinky
 *
 * \file		main.c
 * \version		1.0
 * \date		2013-02-12
 * \author		rct1
 ******************************************************************************/
/*
 * functions global:
 *				main
 *				SysTick_Handler
 * functions local:
 *				delay_ms
 *
 ******************************************************************************/

/*----- Header-Files -------------------------------------------------------*/
#include <MKL25Z4.H>
#include "gpio.h"

/*----- Macros -------------------------------------------------------------*/

/*----- Data types ---------------------------------------------------------*/

/*----- Function prototypes ------------------------------------------------*/

/*----- Data ---------------------------------------------------------------*/
volatile uint32_t msTicks = 0;	/* counts 1ms timeTicks	*/

/*----- Implementation -----------------------------------------------------*/
/**
 *****************************************************************************
 * \fn			SysTick_Handler
 *****************************************************************************
 */
void SysTick_Handler(void) {
	msTicks++;
}

/**
 *****************************************************************************
 * \fn			Delay
 * \brief		Delays number of tick Systicks (happens every 1 ms)
 *
 * \param[in]	dlyTicks: Tick number
 *****************************************************************************
 */
static void delay_ms(uint32_t dlyTicks) {
	uint32_t curTicks;

	curTicks = msTicks;
	while ((msTicks - curTicks) < dlyTicks)
		;
}

/**
 *****************************************************************************
 * \fn			main
 * \brief		The application starts here.
 *
 * \param[in]	None
 * \return		0
 *****************************************************************************
 */
int main(void) {
	SystemCoreClockUpdate();				/* Get Core Clock Frequency		*/
	SysTick_Config(SystemCoreClock / 1000);	/* Generate interrupt each 1 ms	*/
	GPIO_init();							/* Initialize GPIOs				*/

	for (;;) {
		GPIO_bit_reset(Onboard, 0);
		delay_ms(500);
		GPIO_bit_set(Onboard, 0);

		GPIO_bit_reset(Onboard, 1);
		delay_ms(500);
		GPIO_bit_set(Onboard, 1);

		GPIO_bit_reset(Onboard, 2);
		delay_ms(500);
		GPIO_bit_set(Onboard, 2);
	}
}
