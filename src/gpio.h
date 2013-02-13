#ifndef __GPIO_H__
#define __GPIO_H__
/*******************************************************************************
 * \brief		FRDM-KL25Z GPIO functions.
 *
 * \file		gpio.h
 * \version		1.0
 * \date		2013-02-13
 * \author		rct1
 ******************************************************************************/
/*
 * functions global:
 *				GPIO_init
 *				GPIO_set
 *				GPIO_reset
 * functions local:
 *				.
 *
 ******************************************************************************/

/*----- Header-Files -------------------------------------------------------*/
#include <MKL25Z4.H>

/*----- Macros -------------------------------------------------------------*/
#define PIN_0		(1UL <<  0)
#define PIN_1		(1UL <<  1)
#define PIN_2		(1UL <<  2)
#define PIN_3		(1UL <<  3)
#define PIN_4		(1UL <<  4)
#define PIN_5		(1UL <<  5)
#define PIN_6		(1UL <<  6)
#define PIN_7		(1UL <<  7)
#define PIN_8		(1UL <<  8)
#define PIN_9		(1UL <<  9)
#define PIN_10		(1UL << 10)
#define PIN_11		(1UL << 11)
#define PIN_12		(1UL << 12)
#define PIN_13		(1UL << 13)
#define PIN_14		(1UL << 14)
#define PIN_15		(1UL << 15)
#define PIN_16		(1UL << 16)
#define PIN_17		(1UL << 17)
#define PIN_18		(1UL << 18)
#define PIN_19		(1UL << 19)
#define PIN_20		(1UL << 20)
#define PIN_21		(1UL << 21)
#define PIN_22		(1UL << 22)
#define PIN_23		(1UL << 23)
#define PIN_24		(1UL << 24)
#define PIN_25		(1UL << 25)
#define PIN_26		(1UL << 26)
#define PIN_27		(1UL << 27)
#define PIN_28		(1UL << 28)
#define PIN_29		(1UL << 29)
#define PIN_30		(1UL << 30)
#define PIN_31		(1UL << 31)

/*----- Data types ---------------------------------------------------------*/
typedef enum _PORT_NAME {
	Onboard,
	HeaderJ1,
	HeaderJ2,
	HeaderJ9,
	HeaderJ10,
	ArduinoA,
	ArduinoD
} PORT_NAME;

/*----- Function prototypes ------------------------------------------------*/
extern void GPIO_init(void);
extern void GPIO_set(PORT_NAME port, uint8_t bit);
extern void GPIO_reset(PORT_NAME port, uint8_t bit);

/*----- Data ---------------------------------------------------------------*/

#endif /* __GPIO_H__ */
